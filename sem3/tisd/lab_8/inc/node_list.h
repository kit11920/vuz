#ifndef NODE_LIST_H__
#define NODE_LIST_H__

#include "stdlib.h"

typedef struct st_node_t node_t;
struct st_node_t
{
    size_t v;  
    node_t *next;
};


node_t *create_node_list(int v);

void free_node_list(node_t **node);

node_t *add_sort_node_list(node_t *head, node_t *node);

node_t *find_list(node_t *head, size_t v);

node_t *del_list(node_t *head, size_t v);

void free_list(node_t **head);

node_t *copy_list(node_t *head);

size_t len_list(node_t *head);

void print_list(node_t *head);







#endif

