

#include <stdlib.h>
#include <stdio.h>

#include "node_list.h"

node_t *add_tail_list(node_t *head, node_t *node)
{
    if (head == NULL)
        return node;

    node_t *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
        
    tmp->next = node;
    return head;
}

void free_list(node_t **head)
{
    node_t *tmp;
    for (; *head; *head = tmp)
    {
        tmp = (*head)->next;
        free_node(*head);
    }
}

void print_list(node_t *head)
{
    node_t *tmp = head;

    while (tmp)
    {
        print_node(tmp);
        tmp = tmp->next;
    }
    printf("\n");
}

