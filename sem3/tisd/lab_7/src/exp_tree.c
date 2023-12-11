#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "exp_tree.h"
#include "errs.h"
// #include "balanced_tree.h"

bool if_num_in_arr(int arr[], size_t len_arr, int num)
{
    for (size_t i = 0; i < len_arr; i++)
        if (num == arr[i])
            return true;
    return false;
}

void make_arr_base_exp_tree(enode_t *root, int arr[], size_t *i)
{
    if (root->left == NULL && root->right == NULL)
    {
        if (!if_num_in_arr(arr, *i, root->data_exp.data.num))
        {
            arr[*i] = root->data_exp.data.num;
            (*i)++;
        }
        return;
    }
    make_arr_base_exp_tree(root->left, arr, i);
    if (!if_num_in_arr(arr, *i, root->data_exp.data.num))
    {
        arr[*i] = root->data_exp.data.num;
        (*i)++;
    }
    make_arr_base_exp_tree(root->right, arr, i);
}

void print_arr(int arr[], size_t len_arr)
{
    for (size_t i = 0; i < len_arr; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int make_counted_exp_tree(enode_t **root)
{
    if ((*root)->data_exp.type == NUM)
        return (*root)->data_exp.data.num;
    
    int left, right, res;
    left = make_counted_exp_tree(&(*root)->left);
    right = make_counted_exp_tree(&(*root)->right);

    char new_id[MAX_LEN_ID];
    strcpy(new_id, "(");
    strcat(new_id, (*root)->left->id);

    if ((*root)->data_exp.data.exp == PLUS_EXP)
    {
        res = left + right;
        strcat(new_id, "+");
    }
    else if ((*root)->data_exp.data.exp == MINUS_EXP)
    {
        res = left - right;
        strcat(new_id, "-");
    }
    else
    {
        res = left * right;
        strcat(new_id, "*");
    }
    
    strcat(new_id, (*root)->right->id);
    strcat(new_id, ")");
    (*root)->data_exp.type = NUM;
    (*root)->data_exp.data.num = res;
    strcpy((*root)->id, new_id);

    return res;
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
        tmp->data_exp.type = EXP;
        tmp->data_exp.data.exp = (char) data;
    }
    else
    {
        tmp->data_exp.type = NUM;
        tmp->data_exp.data.num = data;
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
    if (root->data_exp.type == EXP)
        printf("%c ", root->data_exp.data.exp);
    else
        printf("%d ", root->data_exp.data.num);
}

void nlr_print_exp_tree(enode_t *root)
{
    each_nlr_exp_tree(root, print_exp_node, NULL);
    printf("\n");
}

int calculate_tree(enode_t *root)
{
    if (root->data_exp.type == NUM)
        return root->data_exp.data.num;
    
    int left = calculate_tree(root->left);
    int right = calculate_tree(root->right);
    int out;

    if (root->data_exp.data.exp == PLUS_EXP)
        out = left + right;
    else if (root->data_exp.data.exp == MINUS_EXP)
        out = left - right;
    else // (root->data.exp == MULT_EXP)
        out = left * right;
    
    // printf("%d _ %d = %d\n", left, right, out);

    return out;
}

void print_parant_child(FILE *f, enode_t *parant, enode_t *child)
{
    if (parant->data_exp.type == EXP && child->data_exp.type == EXP)
        fprintf(f, "\"%c\\n%s\" -> \"%c\\n%s\"\n", parant->data_exp.data.exp, parant->id, child->data_exp.data.exp, child->id);
    else if (parant->data_exp.type == NUM && child->data_exp.type == EXP)
        fprintf(f, "\"%d\\n%s\" -> \"%c\\n%s\"\n", parant->data_exp.data.num, parant->id, child->data_exp.data.exp, child->id);
    else if (parant->data_exp.type == EXP && child->data_exp.type == NUM)
        fprintf(f, "\"%c\\n%s\" -> \"%d\\n%s\"\n", parant->data_exp.data.exp, parant->id, child->data_exp.data.num, child->id);
    else
        fprintf(f, "\"%d\\n%s\" -> \"%d\\n%s\"\n", parant->data_exp.data.num, parant->id, child->data_exp.data.num, child->id);
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





























