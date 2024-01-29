#include <stdlib.h>
#include <string.h>

#include "node_list.h"
#include "list.h"
#include "str_list.h"


int cmp_list(node_t *l, node_t *r)
{
    int rc = 0;
    // node_t *node_l = l, *node_r = r;

    while (l != NULL && r != NULL)
    {
        rc = strncmp(l->data, r->data, PART_LEN);
        if (rc != 0)
            return rc;
        l = l->next;
        r = r->next;
    }

    return rc;
}


















