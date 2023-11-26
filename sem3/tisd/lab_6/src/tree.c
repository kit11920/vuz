#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "errs.h"


int add_node_bin_search_tree(node_t **root, int data)
{
    node_t *tmp = malloc(sizeof(node_t));
    if (tmp == NULL)
        return ERR_MEM;
    tmp->data = data;
    tmp->left = tmp->right = NULL;
    
    if (*root == NULL)
        *root = tmp;
    else
    {
        node_t *node, *next_node = *root;

        while (next_node != tmp)
        {
            node = next_node;
            if (node->data == data)
            {
                free(tmp);
                return ERR_NODE_EXIST;
            }
            else if (node->data < data)
            {
                if (node->right == NULL)
                    node->right = tmp;
                next_node = node->right;
            }
            else
            {
                if (node->left == NULL)
                    node->left = tmp;
                next_node = node->left;
            }
        }
    }

    return OK;
}

void free_tree(node_t **root)
{
    if ((*root) == NULL)
        return;
    
    free_tree(&((*root)->left));
    free_tree(&((*root)->right));
    free(*root);
    *root = NULL;
}

void each_nlr_tree(node_t *root, void (*action)(node_t *root, void *param), void *param)
{
    assert(action != NULL);

    if (root == NULL)
        return;

    action(root, param);
    each_nlr_tree(root->left, action, param);
    each_nlr_tree(root->right, action, param);
}

void print_node(node_t *root, void *param)
{
    char *spec = param;
    printf(spec, root->data);
}

void print_tree(node_t *root)
{
    each_nlr_tree(root, print_node, "%d ");
    printf("\n");
}

void to_dot(node_t *root, void *param)
{
    FILE *f = param;
    assert(f != NULL && root != NULL);

    if (root->left)
        fprintf(f, "%d -> %d\n", root->data, root->left->data);
        
    if (root->right)
        fprintf(f, "%d -> %d\n", root->data, root->right->data);
}

int export_to_dot(char *filename, node_t *root)
{
    FILE *f;
    f = fopen(filename, "w");
    if (f == NULL)
        return ERR_FILE;
    
    fprintf(f, "digraph graph_ {\n");

    each_nlr_tree(root, to_dot, f);

    fprintf(f, "}\n");
    fclose(f);

    return OK;
}

node_t *find_node_tree(node_t *root, int data, node_t **parant)
{
    if (root == NULL)
        return NULL;

    *parant = NULL;
    node_t *node = root;
    while (node != NULL)
    {
        if (data == node->data)
            return node;
        else if (data > node->data)
        {
            *parant = node;
            node = node->right;
        }
        else
        {
            *parant = node;
            node = node->left;
        }
    }
    return NULL;
}

node_t *find_min_tree(node_t *root, node_t **parant)
{
    *parant = NULL;
    if (root == NULL)
        return NULL;
    
    node_t *node = root;
    while (node->left != NULL)
    {
        *parant = node;
        node = node->left;
    }
    return node;
}

// принимает узел который надо удалить
// возвращает узел который должен встать на место удаленного
node_t *del_node_tree(node_t *node)
{
    if (node->left == NULL && node->right == NULL)
    {
        free(node);
        return NULL;
    }
    else if (node->left != NULL && node->right != NULL)
    {
        node_t *min, *min_parant;
        min = find_min_tree(node->right, &min_parant);
        if (min_parant == NULL)
            min_parant = node;

        node->data = min->data;
        if (min_parant->left == min)
            min_parant->left = del_node_tree(min);
        else
            min_parant->right = del_node_tree(min);
        return node;
    }
    else
    {
        node_t *replace;
        if (node->left != NULL)
            replace = node->left;
        else
            replace = node->right;
        
        node->data = replace->data;
        node->left = replace->left;
        node->right = replace->right;
        free(replace);
        return node;
    }
}


int del_node_by_data_tree(node_t **root, int data)
{
    if (*root == NULL)
        return ERR_NOT_FOUND;
    
    node_t *node, *parant;
    node = find_node_tree(*root, data, &parant);
    if (node == NULL)
        return ERR_NOT_FOUND;
    
    if (parant == NULL)
        *root = del_node_tree(node);
    else if (parant->left == node)
        parant->left = del_node_tree(node);
    else
        parant->right = del_node_tree(node);
    
    return OK;
}

