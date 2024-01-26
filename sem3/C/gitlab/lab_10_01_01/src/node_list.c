#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "node_list.h"
#include "errs.h"


node_t *create_node(void *data)
{
    node_t *tmp = malloc(sizeof(node_t));
    
    if (tmp == NULL)
        return NULL;
    tmp->data = data;
    tmp->next = NULL;

    return tmp;
}

void free_node(node_t *node)
{
    free(node);
}
// передать указатель на печать данных 
void print_node(FILE *f, const node_t *node, void (*print_data)(FILE *, void *))
{
    print_data(f, node->data);
}

void insert(node_t **head, node_t *elem, node_t *before)
{
    // assert(*head != NULL);
    if (*head == NULL || elem == NULL || before == NULL)
        return;

    if (before == *head)
    {
        elem->next = *head;
        *head = elem;
    }
    else
    {
        node_t *node = *head;
        while (node->next != NULL && node->next != before)
            node = node->next;
        // assert(node->next == before);
        if (node->next == before)
        {
            node->next = elem;
            elem->next = before;
        }
    }
}

node_t *find(node_t *head, const void *data, cmp_t cmp)
{
    node_t *node = head, *out = NULL;

    while (node != NULL && out == NULL)
    {
        if (cmp(data, node->data) == 0)
            out = node;
        else
            node = node->next;
    }

    return out;
}


