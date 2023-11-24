#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "tree.h"
#include "errs.h"


int add_node_bin_search_tree(node_t **root, char *data)
{
    assert(data != NULL || strlen(data) != 0);

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
        int cmp;

        while (next_node != tmp)
        {
            node = next_node;
            cmp = strcmp(node->data, data);
            if (cmp == 0)
            {
                free(data);
                return ERR_NODE_EXIST;
            }
            else if (cmp < 0)
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

void free_tree(node_t *root)
{
    if (root == NULL)
        return;
    
    free_tree(root->left);
    free_tree(root->right);
    // free(root->data);
    free(root);
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
    each_nlr_tree(root, print_node, "%s\n");
}

void to_dot(node_t *root, void *param)
{
    FILE *f = param;
    assert(f != NULL && root != NULL);

    if (root->left)
        fprintf(f, "%s -> %s\n", root->data, root->left->data);
    if (root->right)
        fprintf(f, "%s -> %s\n", root->data, root->right->data);
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

    return OK;
}

node_t *find_node_tree(node_t *root, char *data, node_t **parant)
{
    if (root == NULL)
        return NULL;

    *parant = NULL;
    node_t *node = root;
    int cmp;
    while (node != NULL)
    {
        cmp = strcmp(data, node->data);
        if (cmp == 0)
            return node;
        else if (cmp > 0)
        {
            parant = node;
            node = node->right;
        }
        else
        {
            parant = node;
            node = node->left;
        }
    }
    return NULL;
}





