#include <stdlib.h>
#include <stdio.h>

#include "errs.h"
#include "act.h"
#include "interface.h"
#include "list_graph.h"
#include "mtrx_graph.h"
#include "efficiency_list_mtrx_graph.h"

int main(void)
{
    int rc = OK, type = -1;
    listg_t *list_graph = NULL;
    mtrxg_t *mtrx_graph = NULL;

    printf(INTRANCE);
    printf(CHOSE_TYPE);
    while (scanf("%d", &type) != 1 || !(type == LIST_GRAPH || type == MTRX_GRAPH) ||
        getchar() != '\n')
    {
        printf("\n");
        print_err(ERR_TYPE_GRAPH);
        printf(CHOSE_TYPE);

        while(getchar() != '\n')
            ;
    }

    rc = input_graphs(&list_graph, &mtrx_graph);
    if (rc != OK)
        return print_err(rc);

    if (type == LIST_GRAPH)
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


























