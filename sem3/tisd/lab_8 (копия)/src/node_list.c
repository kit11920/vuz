#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "node_list.h"


node_t *create_node_list(int v)
{
    node_t *node = malloc(sizeof(node_t));
    if (node != NULL)
    {
        node->v = v;
        node->next = NULL;
    }
    return node;
}

void free_node_list(node_t **node)
{
    free(*node);
    *node = NULL;
}

node_t *add_sort_node_list(node_t *head, node_t *node)
{
    if (head == NULL)
        return node;
    if (node->v < head->v)
    {
        node->next = head;
        return node;
    }
    
    node_t *tmp = head;
    while (tmp->next != NULL && node->v > tmp->next->v)
        tmp = tmp->next;
    if (tmp->next == NULL)
        tmp->next = node;
    else
    {
        node->next = tmp->next;
        tmp->next = node;
    }

    return head;
}

node_t *find_list(node_t *head, size_t v)
{
    if (head == NULL)
        return NULL;

    if (head->v == v)
        return head;

    while (head->next != NULL && head->next->v != v)
        head = head->next;

    if (head->next == NULL)
        return NULL;
    else
        return head->next;
}

node_t *del_list(node_t *head, size_t v)
{
    assert(head != NULL);

    node_t *node = head;
    if (head->v == v)
    {
        node = head->next;
        free(head);
        return node;
    }
    while (node->next != NULL && node->next->v != v)
        node = node->next;
    assert(node->next->v == v);

    node_t *tmp = node->next->next;
    free(node->next);
    node->next = tmp;
    return head;    
}

void free_list(node_t **head)
{
    node_t *next;
    while (*head != NULL)
    {
        next = (*head)->next;
        free((*head));
        (*head) = next;
    }
}

node_t *copy_list(node_t *head)
{
    node_t *copy = NULL, *src_node, *dst_node;

    copy = create_node_list(head->v);
    if (copy == NULL)
        return NULL;

    src_node = head->next;
    dst_node = copy;
    while (src_node != NULL)
    {
        dst_node->next = create_node_list(src_node->v);
        if (dst_node->next == NULL)
        {
            free_list(&copy);
            return NULL;
        }
        dst_node = dst_node->next;
        src_node = src_node->next;
    }
    return copy;
}

size_t len_list(node_t *head)
{
    size_t count = 0;
    while (head != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

void print_list(node_t *head)
{
    if (head == NULL)
        printf("list NULL");
    while (head != NULL)
    {
        printf("%zu ", head->v);
        head = head->next;
    }
    printf("\n");
}
















