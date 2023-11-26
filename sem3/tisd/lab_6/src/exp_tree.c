#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "exp_tree.h"
#include "errs.h"
#include "efficiency_stack_tree.h"
#include "stack.h"


int act_exp_tree(void)
{
    int arr[LEN_NUM_ARR] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    enode_t *root = NULL;
    int rc = OK;

    printf("Введите целые числа соответствующие выражению A + (B * (C + (D * (E + F) - (G - H)) + I))\n");
    printf("A B C D E F G H I:\n");
    for (size_t i = 0; i < LEN_NUM_ARR; i++)
        if (scanf("%d", &arr[i]) != 1)
            return ERR_DATA;

    rc = make_exp_tree(&root, arr);
    if (rc != OK)
        return rc;
    
    printf("Значение выражения:\t");
    printf("%d + (%d * (%d + (%d * (%d + %d) - (%d - %d)) + %d)) = %d", 
    arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], calculate_tree(root));
    printf("\n");

    printf("Выражение в префиксной форме (NLR):\t");
    each_nlr_exp_tree(root, print_exp_node, NULL);
    printf("\n");

    printf("Выражение в инфиксной форме (LNR):\t");
    each_lnr_exp_tree(root, print_exp_node, NULL);
    printf("\n");

    printf("Выражение в постфиксной форме (LRN):\t");
    each_lrn_exp_tree(root, print_exp_node, NULL);
    printf("\n");

    char filename[] = "graph/exp_graph.gv";
    rc = export_exp_to_dot(filename, root);
    if (rc != OK)
    {
        free_exp_tree(&root);
        return rc;
    }
    printf("Данные о дереве записаны в файл %s\n", filename);
    printf("\n");
    
    lnode_t *list_exp = NULL;
    rc = exp_tree_to_list(root, &list_exp);
    if (rc != OK)
    {
        free_exp_tree(&root);
        return rc;
    }
    // printf("Выражение поступающее в стек: ");
    // print_list(list_exp);

    // int res = calculate_stack(list_exp);
    // printf("res stack = %d\n", res);
    make_compare_table_stack_tree(root, list_exp);

    free_list(&list_exp);
    free_exp_tree(&root);

    printf("\n");
    return OK;
}

int make_enode_exp_tree(enode_t **node)
{
    enode_t *tmp = malloc(sizeof(enode_t));
    if (tmp == NULL)
        return ERR_MEM;
    tmp->left = tmp->right = NULL;
    *node = tmp;
    return OK;
}

int add_enode_tree(enode_t **node, type_data_t type, int data, char *id)
{
    int rc = OK;
    enode_t *tmp;
    rc = make_enode_exp_tree(&tmp);
    if (rc != OK)
        return rc;
    if (type == EXP)
    {
        tmp->type = EXP;
        tmp->data.exp = (char) data;
    }
    else
    {
        tmp->type = NUM;
        tmp->data.num = data;
    }
    strcpy(tmp->id, id);
    
    *node = tmp;
    return OK;
}

void free_exp_tree(enode_t **root)
{
    if ((*root) == NULL)
        return;
    
    free_exp_tree(&((*root)->left));
    free_exp_tree(&((*root)->right));
    free(*root);
    *root = NULL;
}

void each_nlr_exp_tree(enode_t *root, void (*action)(enode_t *root, void *param), void *param)
{
    assert(action != NULL);

    if (root == NULL)
        return;

    action(root, param);
    each_nlr_exp_tree(root->left, action, param);
    each_nlr_exp_tree(root->right, action, param);
}

void each_lnr_exp_tree(enode_t *root, void (*action)(enode_t *root, void *param), void *param)
{
    assert(action != NULL);

    if (root == NULL)
        return;

    each_lnr_exp_tree(root->left, action, param);
    action(root, param);
    each_lnr_exp_tree(root->right, action, param);
}

void each_lrn_exp_tree(enode_t *root, void (*action)(enode_t *root, void *param), void *param)
{
    assert(action != NULL);

    if (root == NULL)
        return;
    each_lrn_exp_tree(root->left, action, param);
    each_lrn_exp_tree(root->right, action, param);
    action(root, param);
}

void print_exp_node(enode_t *root, void *param)
{
    (void) param;
    if (root->type == EXP)
        printf("%c ", root->data.exp);
    else
        printf("%d ", root->data.num);
}

void nlr_print_exp_tree(enode_t *root)
{
    each_nlr_exp_tree(root, print_exp_node, NULL);
    printf("\n");
}

int calculate_tree(enode_t *root)
{
    if (root->type == NUM)
        return root->data.num;
    
    int left = calculate_tree(root->left);
    int right = calculate_tree(root->right);
    int out;

    if (root->data.exp == PLUS_EXP)
        out = left + right;
    else if (root->data.exp == MINUS_EXP)
        out = left - right;
    else // (root->data.exp == MULT_EXP)
        out = left * right;
    
    // printf("%d _ %d = %d\n", left, right, out);

    return out;
}

void print_parant_child(FILE *f, enode_t *parant, enode_t *child)
{
    if (parant->type == EXP && child->type == EXP)
        fprintf(f, "\"%c\\n(%s)\" -> \"%c\\n(%s)\"\n", parant->data.exp, parant->id, child->data.exp, child->id);
    else if (parant->type == NUM && child->type == EXP)
        fprintf(f, "\"%d\\n(%s)\" -> \"%c\\n(%s)\"\n", parant->data.num, parant->id, child->data.exp, child->id);
    else if (parant->type == EXP && child->type == NUM)
        fprintf(f, "\"%c\\n(%s)\" -> \"%d\\n(%s)\"\n", parant->data.exp, parant->id, child->data.num, child->id);
    else
        fprintf(f, "\"%d\\n(%s)\" -> \"%d\\n(%s)\"\n", parant->data.num, parant->id, child->data.num, child->id);
}

void exp_to_dot(enode_t *root, void *param)
{
    FILE *f = param;
    assert(f != NULL && root != NULL);

    if (root->left)
        print_parant_child(f, root, root->left);
    if (root->right)
        print_parant_child(f, root, root->right);
}

int export_exp_to_dot(char *filename, enode_t *root)
{
    FILE *f;
    f = fopen(filename, "w");
    if (f == NULL)
        return ERR_FILE;
    
    fprintf(f, "digraph graph_ {\n");

    each_nlr_exp_tree(root, exp_to_dot, f);

    fprintf(f, "}\n");
    fclose(f);

    return OK;
}

int make_exp_tree(enode_t **root, int *arr)
{
    int rc = OK;
    enode_t *node = NULL;

    rc = add_enode_tree(root, EXP, PLUS_EXP, "1");
    if (rc != OK)
        return rc;
    
    node = *root;
    rc = add_enode_tree(&node->left, NUM, arr[0], "A");
    if (rc != OK)
        return rc;
    rc = add_enode_tree(&node->right, EXP, MULT_EXP, "1");
    if (rc != OK)
        return rc;

    node = node->right;
    rc = add_enode_tree(&node->left, NUM, arr[1], "B");
    if (rc != OK)
        return rc;
    rc = add_enode_tree(&node->right, EXP, PLUS_EXP, "2");
    if (rc != OK)
        return rc;

    node = node->right;
    rc = add_enode_tree(&node->left, NUM, arr[2], "C");
    if (rc != OK)
        return rc;
    rc = add_enode_tree(&node->right, EXP, PLUS_EXP, "3");
    if (rc != OK)
        return rc;

    node = node->right;
    rc = add_enode_tree(&node->left, EXP, MINUS_EXP, "1");
    if (rc != OK)
        return rc;
    rc = add_enode_tree(&node->right, NUM, arr[8], "I");
    if (rc != OK)
        return rc;

    node = node->left;
    rc = add_enode_tree(&node->left, EXP, MULT_EXP, "2");
    if (rc != OK)
        return rc;
    rc = add_enode_tree(&node->right, EXP, MINUS_EXP, "2");
    if (rc != OK)
        return rc;

    rc = add_enode_tree(&node->right->left, NUM, arr[6], "G");
    if (rc != OK)
        return rc;
    rc = add_enode_tree(&node->right->right, NUM, arr[7], "H");
    if (rc != OK)
        return rc;
    
    node = node->left;
    rc = add_enode_tree(&node->left, NUM, arr[3], "D");
    if (rc != OK)
        return rc;
    rc = add_enode_tree(&node->right, EXP, PLUS_EXP, "4");
    if (rc != OK)
        return rc;

    node = node->right;
    rc = add_enode_tree(&node->left, NUM, arr[4], "E");
    if (rc != OK)
        return rc;
    rc = add_enode_tree(&node->right, NUM, arr[5], "F");
    if (rc != OK)
        return rc;
    
    return OK;
}





























