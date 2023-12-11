#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"
#include "exp_tree.h"
#include "errs.h"
#include "balanced_tree.h"

int fill_btree_based_data_arr(bnode_t **root, int *arr, size_t len_arr)
{
    for (size_t i = 0; i < len_arr; i++)
    {
        // printf("%d ", arr[i]);
        bnode_t *tmp = add_btree(*root, arr[i]);
        if (tmp == NULL)
        {
            free_btree(root);
            return ERR_MEM;
        }
        *root = tmp;
    }
    return OK;
}

int height(bnode_t *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

// int min_height(bnode_t *node)
// {
//     if (node == NULL)
//         return 0;
    
//     int hl = 0, hr = 0;
//     hl = min_height(node->left);
//     hr = min_height(node->right);
//     if (hl < hr)
//         return hl + 1;
//     else
//         return hr + 1;
// }

int bfactor(bnode_t *node)
{
    // assert(node != NULL);
    // // if (height(node->right) - min_height(node->left) == 2)
    // //     return 2;
    // // else if (min_height(node->left) - height(node->right) == -2)
    // //     return -2;
    // // return height(node->right) - height(node->left);

    // // int hl = 0, hr = 0;
    // int max_h = height(node);
    // int min_h = min_height(node);
    // printf("max - %d, min - %d\n", max_h, min_h);
    // printf("min_left - %d\n", min_height(node->left));
    // if (max_h == height(node->right) + 1 && min_h == min_height(node->left) + 1)
    //     return max_h - min_h;
    // else
    //     return min_h - max_h;
    return height(node->right) - height(node->left);
}

void update_height(bnode_t *node)
{
    // if (node->left == NULL && node->right == NULL)
    //     node->height = 0;
    // else
    // {
    //     int hl = height(node->left);
    //     int hr = height(node->right);
    //     if (hl > hr)
    //         node->height =  hl + 1;
    //     else
    //         node->height =  hr + 1;
    // }
    int hl = height(node->left);
    int hr = height(node->right);
    if (hl > hr)
        node->height =  hl + 1;
    else
        node->height =  hr + 1;
}

bnode_t *rotate_right(bnode_t *root)
{
    bnode_t *left = root->left;
    root->left = left->right;
    left->right = root;
    update_height(root);
    update_height(left);
    return left;
}

bnode_t *rotate_left(bnode_t *root)
{
    bnode_t *right = root->right;
    root->right = right->left;
    right->left = root;
    update_height(root);
    update_height(right);
    return right;
}

bnode_t *balance_btree(bnode_t *root)
{
    assert(root != NULL);
    update_height(root);

    if (bfactor(root) == 2)
    {
        if (bfactor(root->right) < 0)
            root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    if (bfactor(root) == -2)
    {
        if (bfactor(root->left) > 0)
            root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    return root;
}

bnode_t *new_bnode(int data)
{
    bnode_t *tmp = malloc(sizeof(bnode_t));
    if (tmp == NULL)
        return NULL;
    tmp->data = data;
    tmp->left = tmp->right = NULL;
    tmp->height = 1;
    return tmp;
}

bnode_t *add_btree(bnode_t *root, int data)
{
    if (root == NULL)
        return new_bnode(data);

    if (root->data < data)
    {
        root->right = add_btree(root->right, data);
        if (root->right == NULL)
            return NULL;
        
    }
    else if (root->data > data)
    {
        root->left = add_btree(root->left, data);
        if (root->left == NULL)
            return NULL;
    }
    
    return balance_btree(root);
}

bnode_t *find_btree(bnode_t *root, int data, bnode_t **parant)
{
    if (root == NULL)
        return NULL;

    *parant = NULL;
    bnode_t *node = root;
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

void free_btree(bnode_t **root)
{
    if ((*root) == NULL)
        return;
    
    free_btree(&((*root)->left));
    free_btree(&((*root)->right));
    free(*root);
    *root = NULL;
}

void print_bnode(bnode_t *root, void *param)
{
    char *spec = param;
    printf(spec, root->data, root->height);
}

void print_btree(bnode_t *root)
{
    each_nlr_btree(root, print_bnode, "%d (%d)\n");
    printf("\n");
}

void each_nlr_btree(bnode_t *root, void (*action)(bnode_t *root, void *param), void *param)
{
    assert(action != NULL);

    if (root == NULL)
        return;

    action(root, param);
    each_nlr_btree(root->left, action, param);
    each_nlr_btree(root->right, action, param);
}

void to_dot_btree(bnode_t *root, void *param)
{
    FILE *f = param;
    assert(f != NULL && root != NULL);

    if (root->left)
        fprintf(f, "\"%d\\nbal = %d\\nh = %d\" -> \"%d\\nbal = %d\\nh = %d\"\n", root->data, bfactor(root), height(root), root->left->data, bfactor(root->left), height(root->left));
        
    if (root->right)
        fprintf(f, "\"%d\\nbal = %d\\nh = %d\" -> \"%d\\nbal = %d\\nh = %d\"\n", root->data, bfactor(root), height(root), root->right->data, bfactor(root->right), height(root->right));
}

int export_to_dot_btree(char *filename, bnode_t *root)
{
    FILE *f;
    f = fopen(filename, "w");
    if (f == NULL)
        return ERR_FILE;
    
    fprintf(f, "digraph graph_ {\n");

    each_nlr_btree(root, to_dot_btree, f);

    fprintf(f, "}\n");
    fclose(f);

    return OK;
}


double mid_cmp_btree(bnode_t *root)
{
    size_t elems, cmps;
    elems = count_elems_btree(root);
    cmps = count_comparison_btree(root, 1);

    return cmps / (double) elems;
}

void act_count_elems_btree(bnode_t *root, void *param)
{
    size_t *count = param;
    if (root != NULL)
        (*count)++;
}

size_t count_elems_btree(bnode_t *root)
{
    size_t count = 0;
    each_nlr_btree(root, act_count_elems_btree, &count);
    return count;
}

size_t count_comparison_btree(bnode_t *root, size_t height_now)
{
    if (root == NULL)
        return 0;
    
    size_t lh, rh;
    lh = count_comparison_btree(root->left, height_now + 1);
    rh = count_comparison_btree(root->right, height_now + 1);
    
    if (lh + rh == 0)
        return height_now;
    else
        return lh + rh + height_now;
}

int max_height_btree(bnode_t *root)
{
    if (root == NULL)
        return -1;
    
    int lh, rh;
    lh = max_height_btree(root->left) + 1;
    rh = max_height_btree(root->right) + 1;
    if (lh > rh)
        return lh;
    else
        return rh;
}

size_t mem_bytes_btree(bnode_t *root)
{
    size_t elems = count_elems_btree(root);

    return sizeof(bnode_t) * elems;
}


