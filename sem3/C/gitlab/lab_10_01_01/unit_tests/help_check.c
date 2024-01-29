#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "data.h"
#include "errs.h"
#include "node_list.h"
#include "list.h"

void create_list_based_arr(node_t **head, country_t arr[], size_t len_arr)
{
    assert(len_arr != 0);

    *head = NULL;
    node_t *node = NULL;

    for (size_t i = 0; i < len_arr; i++)
    {
        node = create_node(&arr[i]);
        *head = add_tail_list(*head, node);
    }
}

int cmp_country_all(void *l, void *r)
{
    const int same = 0, diff = 1;
    country_t *cl = l, *cr = r;
    
    if (strcmp(cl->name, cr->name) == 0 && strcmp(cl->capital, cr->capital) == 0 &&
        cl->visa == cr->visa && cl->time == cr->time && cl->cost_min == cr->cost_min)
        return same;
    else
        return diff;
}

int cmp_list(node_t *l, node_t *r)
{
    const int same = 0, diff = 1;

    while (l != NULL && r != NULL)
    {
        if (cmp_country_all(l->data, r->data) != same)
            return diff;
        l = l->next;
        r = r->next;
    }
    if (l != NULL || r != NULL)
        return diff;
    
    return same;
}

