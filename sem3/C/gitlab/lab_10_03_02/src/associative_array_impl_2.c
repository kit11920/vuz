#include <stdlib.h>
#include <string.h>

#include "associative_array.h"
#include "impl_2_plus.h"



assoc_array_t assoc_array_create(void)
{
    assoc_array_t tree = malloc(sizeof(struct assoc_array_type));
    if (tree != NULL)
        tree->root = NULL;
    
    return tree;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL || *arr == NULL)
        return;
    if ((*arr)->root != NULL)
        tree_destroy(&(*arr)->root);
    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    int *tmp_num = NULL;
    if (assoc_array_find(arr, key, &tmp_num) == ASSOC_ARRAY_OK)
        return ASSOC_ARRAY_KEY_EXISTS;

    node_t *new_node = tree_node_create(key, num);
    if (new_node == NULL)
        return ASSOC_ARRAY_MEM;

    arr->root = tree_add(arr->root, new_node);
    
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (arr == NULL || key == NULL || strlen(key) == 0 || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->root == NULL)
        return ASSOC_ARRAY_NOT_FOUND;
    
    node_t *node, *parant;
    node = tree_find(arr->root, key, &parant);
    
    if (node == NULL)
        return ASSOC_ARRAY_NOT_FOUND;
    
    *num = &node->num;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->root == NULL)
        return ASSOC_ARRAY_NOT_FOUND;
    
    node_t *node, *parant;
    node = tree_find(arr->root, key, &parant);
    if (node == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    if (parant == NULL)
        arr->root = tree_remove(node);
    else if (parant->left == node)
        parant->left = tree_remove(node);
    else
        parant->right = tree_remove(node);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    tree_destroy(&arr->root);
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || action == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    tree_action(arr->root, action, param);
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->root == NULL)
        return ASSOC_ARRAY_NOT_FOUND;
    
    node_t *parant;
    node_t *min_node = tree_find_min(arr->root, &parant);
    *num = &min_node->num;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->root == NULL)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *parant;
    node_t *max_node = tree_find_max(arr->root, &parant);
    *num = &max_node->num;

    return ASSOC_ARRAY_OK;
}



