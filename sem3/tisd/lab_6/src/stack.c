#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "exp_tree.h"
#include "errs.h"
#include "stack.h"


int create_stnode(lnode_t **node, type_data_t type, int data)
{
    lnode_t *tmp = malloc(sizeof(lnode_t));
    if (tmp == NULL)
        return ERR_MEM;
    tmp->data_exp.type = type;
    if (type == NUM)
        tmp->data_exp.data.num = data;
    else
        tmp->data_exp.data.exp = (char) data;
    tmp->next = NULL;

    *node = tmp;
    return OK;
}

int push_end_lnode_list(lnode_t **head, type_data_t type, int data)
{
    lnode_t *node;
    int rc = create_stnode(&node, type, data);
    if (rc != OK)
        return rc;

    if (*head == NULL)
        *head = node;
    else
    {
        lnode_t *tmp = *head;
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = node;
    }
    return OK;
}

int push_beg_lnode_list(lnode_t **head, type_data_t type, int data)
{
    lnode_t *node;
    int rc = create_stnode(&node, type, data);
    if (rc != OK)
        return rc;

    if (*head == NULL)
        *head = node;
    else
    {
        lnode_t *tmp = *head;
       *head = node;
       node->next = tmp;
    }
    return OK;
}

lnode_t *pop_list(lnode_t **head)
{
    lnode_t *tmp = *head;
    if (tmp != NULL)
        *head = (*head)->next;

    return tmp;
}

void free_list(lnode_t **head)
{
    lnode_t *tmp;
    while (*head != NULL)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

void print_list(lnode_t *head)
{
    lnode_t *tmp = head;
    if (tmp == NULL)
        printf("Список пуст\n");
    while (tmp != NULL)
    {
        if (tmp->data_exp.type == NUM)
            printf("%d ", tmp->data_exp.data.num);
        else
            printf("%c ", tmp->data_exp.data.exp);
        tmp = tmp->next;
    }
    printf("\n");
}

void exp_tree_to_list_action(enode_t *root, void *param)
{
    if (param != NULL)
    {
        lnode_t **head = param;
        int rc = OK;
        if (root->data_exp.type == NUM)
            rc = push_end_lnode_list(head, root->data_exp.type, root->data_exp.data.num);
        else
            rc = push_end_lnode_list(head, root->data_exp.type, root->data_exp.data.exp);
        
        if (rc != OK)
            free_list(head);
    }
}

int exp_tree_to_list(enode_t *root, lnode_t **head)
{
    assert(root != NULL);
    each_lrn_exp_tree(root, exp_tree_to_list_action, head);
    if (head == NULL)
        return ERR_MEM;
    return OK;
}

int calculate_stack(lnode_t *exp)
{
    lnode_t *stack = NULL;
    lnode_t *tmp = pop_list(&exp);
    lnode_t *left, *right;
    int res;

    while (tmp != NULL)
    {
        if (tmp->data_exp.type == NUM)
            push_beg_lnode_list(&stack, tmp->data_exp.type, tmp->data_exp.data.num);
        else
        {
            right = pop_list(&stack);
            left = pop_list(&stack);
            if (tmp->data_exp.data.exp == PLUS_EXP)
                res = left->data_exp.data.num + right->data_exp.data.num;
            else if (tmp->data_exp.data.exp == MINUS_EXP)
                res = left->data_exp.data.num - right->data_exp.data.num;
            else
                res = left->data_exp.data.num * right->data_exp.data.num;
            
            push_beg_lnode_list(&stack, NUM, res);
            free(left);
            free(right);
        }
        tmp = pop_list(&exp);
        // print_list(stack);
    }
    tmp = pop_list(&stack);
    assert(pop_list(&exp) == NULL && tmp->data_exp.type == NUM && stack == NULL);
    res = tmp->data_exp.data.num;

    free(tmp);
    return res;
}










