#include <stdlib.h>
#include <stdio.h>

#include "errs.h"
#include "act.h"
#include "list_graph.h"
#include "mtrx_graph.h"
#include "efficiency_list_mtrx_graph.h"

#define TYPE_GRAPH 0

int main(void)
{
    int rc = OK;
    listg_t *list_graph = NULL;
    mtrxg_t *mtrx_graph = NULL;

    rc = input_graphs(&list_graph, &mtrx_graph);
    if (rc != OK)
        return print_err(rc);

    if (TYPE_GRAPH == 0)
    {
        rc = act_list_graph(list_graph);
        if (rc != OK)
            goto graph_free;
    }
    else
    {
        rc = act_mtrx_graph(mtrx_graph);
        if (rc != OK)
            goto graph_free;
    }

#ifndef DEBUG
    printf("\n");
    make_compare_table_list_mtrx_graph(list_graph, mtrx_graph);
#endif

    graph_free:
    free_list_graph(&list_graph);
    free_mtrx_graph(&mtrx_graph);

    return print_err(rc);
}


























