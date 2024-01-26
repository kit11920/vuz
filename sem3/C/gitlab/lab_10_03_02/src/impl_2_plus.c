#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "associative_array.h"
#include "impl_2_plus.h"


node_t *tree_node_create(const char *key, int num)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (new_node != NULL)
    {
        new_node->key = key;
        new_node->num = num;
        new_node->left = NULL;
        new_node->right = NULL;
    }
    return new_node;
}

void tree_node_free(node_t **node)
{
    free(*node);
    *node = NULL;
}

void tree_destroy(node_t **node)
{
    if ((*node) == NULL)
        return;
    
    tree_destroy(&(*node)->left);
    tree_destroy(&(*node)->right);
    tree_node_free(node);
}

node_t *tree_add(node_t *root, node_t *new_node)
{
    if (root == NULL)
        return new_node;
    
    node_t *node = root;
    while (node->left != new_node && node->right != new_node)
    {
        if (strcmp(new_node->key, node->key) < 0)
        {
            if (node->left != NULL)
                node = node->left;
            else
                node->left = new_node;
        }
        else
        {
            if (node->right != NULL)
                node = node->right;
            else
                node->right = new_node;
        }
    }
    return root;
}

void tree_action(node_t *node, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (node == NULL)
        return;

    action(node->key, &node->num, param);
    tree_action(node->left, action, param);
    tree_action(node->right, action, param);
}

node_t *tree_find(node_t *root, const char *key, node_t **parant)
{
    assert(root != NULL);
    *parant = NULL;

    node_t *node = root;
    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
            return node;
        else if (strcmp(key, node->key) < 0)
        {
            *parant = node;
            node = node->left;
        }
        else
        {
            *parant = node;
            node = node->right;
        }
    }
    return NULL;
}

node_t *tree_remove(node_t *node)
{
    assert(node != NULL);

    if (node->left == NULL && node->right == NULL)
    {
        free(node);
        return NULL;
    }
    else if (node->left != NULL && node->right != NULL)
    {
        node_t *parant, *min;
        min = tree_find_min(node->right, &parant);
        if (parant == NULL)
            parant = node;

        node->key = min->key;
        node->num = min->num;
        if (parant->left == min)
            parant->left = tree_remove(min);
        else
            parant->right = tree_remove(min);
        return node;
    }
    else 
    {
        node_t *replace;
        if (node->left != NULL)
            replace = node->left;
        else if (node->right != NULL)
            replace = node->right;

        node->left = replace->left;
        node->right = replace->right;
        node->key = replace->key;
        node->num = replace->num;
        free(replace);
        return node;
    }
}

node_t *tree_find_min(node_t *node, node_t **parant)
{
    assert(node != NULL);
    *parant = NULL;

    while (node->left)
    {
        *parant = node;
        node = node->left;
    }
    return node;
}

node_t *tree_find_max(node_t *node, node_t **parant)
{
    assert(node != NULL);
    *parant = NULL;

    while (node->right)
    {
        *parant = node;
        node = node->right;
    }
    return node;
}



