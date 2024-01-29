#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node_list.h"



node_t *create_node(char *data)
{
    node_t *tmp = malloc(sizeof(node_t));

    if (tmp != NULL)
    {
        memcpy(tmp->data, data, sizeof(char) * PART_LEN);
        // memmove(tmp->data, data, sizeof(char) * PART_LEN);
        tmp->next = NULL;
    }

    return tmp;
}

void free_node(node_t *node)
{
    free(node);
}

void print_node(node_t *node)
{
    printf("%.*s", PART_LEN, node->data);
}











