#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "errs.h"
#include "list_graph.h"
#include "mtrx_graph.h"


int input_graphs(listg_t **list_graph_out, mtrxg_t **mtrx_graph_out)
{
    int rc = OK;
    int edges, count_v;
    listg_t *list_graph = NULL;
    mtrxg_t *mtrx_graph = NULL;

    printf("Введите кол-во вершин в графе (минимум 2): ");
    if (scanf("%d", &count_v) != 1 || count_v < 2)
        return ERR_COUNT_V;

    list_graph = create_list_graph(count_v);
    if (list_graph == NULL)
        return ERR_MEM;
    
    mtrx_graph = create_mtrx_graph(count_v);
    if (mtrx_graph == NULL)
    {
        free_list_graph(&list_graph);
        return ERR_MEM;
    }

    size_t len;
    ssize_t read;
    int bytes_str;
    char *str = NULL;
    while (getc(stdin) != '\n')
        ;
    printf("Введит название городов, соответствующих индексам в графе:\n");
    for (size_t i = 0; i < list_graph->count_v; i++)
    {
        printf("%zu: ", i);
        if ((read = getline(&str, &len, stdin)) <= 1)
        {
            rc = ERR_NAME;
            free(str);
            goto graphs_free;
        }
        else
            if (str[read - 1] == '\n')
                str[read - 1] = 0;

        bytes_str = asprintf(&list_graph->names[i], "%s", str);
        if (bytes_str == -1)
        {
            rc = ERR_MEM;
            free(str);
            goto graphs_free;
        }
        bytes_str = asprintf(&mtrx_graph->names[i], "%s", str);
        if (bytes_str == -1)
        {
            rc = ERR_MEM;
            free(str);
            goto graphs_free;
        }
        DBG_PRINT("STR \"%s\": len - %zu, bytes - %d\n", mtrx_graph->names[i], strlen(mtrx_graph->names[i]), bytes_str);
    }
    free(str);

    printf("Введите кол-во ребер в графе (минимум 1): ");
    if (scanf("%d", &edges) != 1 || edges < 1 || edges > count_v * (count_v - 1) / 2)
        return ERR_COUNT_EDGE;

    int v1, v2;
    printf("Введите %d ребер графа, в виде 'v1 v2', где v1, v2 узлы графа\n", edges);
    for (size_t i = 0; i < (size_t) edges; i++)
    {
        if (scanf("%d%d", &v1, &v2) != 2 || v1 < 0 || v2 < 0 || v1 == v2)
        {
            rc = ERR_EDGE;
            goto graphs_free;
        }
        rc = add_edge_list_graph(list_graph, (size_t) v1, (size_t) v2);
        if (rc != OK)
            goto graphs_free;
        rc = add_edge_mtrx_graph(mtrx_graph, v1, v2);
        if (rc != OK)
            goto graphs_free;
    }

    if (rc != OK)
    {
        graphs_free:
        free_list_graph(&list_graph);
        free_mtrx_graph(&mtrx_graph);
    }
    else
    {
        *list_graph_out = list_graph;
        *mtrx_graph_out = mtrx_graph;
    }
    
    return rc;
}

int act_mtrx_graph(mtrxg_t *mtrx_graph)
{
    int rc = OK;
    bool connected_lg;

    rc = print_mtrx_graph(mtrx_graph, "graph/graph.gv");
    if (rc != OK)
        return rc;
    printf("\n");

    rc = connected_mtrx_graph(mtrx_graph, &connected_lg);
    if (rc != OK)
        return rc;
    
    if (connected_lg)
        printf("Граф связный!");
    else
        return ERR_NOT_CONNECTED;
    printf("\n");

    if (!euler_path_exist_mtrx_graph(mtrx_graph))
        return ERR_NO_EULER_PATH;

    int *epath = NULL;
    size_t len_epath;
    rc = find_euler_path_mtrx_graph(mtrx_graph, &epath, &len_epath);
    if (rc != OK)
        return rc;
    print_euler_path_mtrx_graph(mtrx_graph, epath, len_epath);

    free(epath);
    return rc;
}


int act_list_graph(listg_t *list_graph)
{
    int rc = OK;
    bool connected_lg;

    rc = print_list_graph(list_graph, "graph/graph.gv");
    if (rc != OK)
        return rc;
    printf("\n");

    rc = connected_list_graph(list_graph, &connected_lg);
    if (rc != OK)
        return rc;
    
    if (connected_lg)
        printf("Граф связный!");
    else
        return ERR_NOT_CONNECTED;
    printf("\n");

    if (!euler_path_exist_list_graph(list_graph))
        return ERR_NO_EULER_PATH;

    int *epath = NULL;
    size_t len_epath;
    rc = find_euler_path_list_graph(list_graph, &epath, &len_epath);
    if (rc != OK)
        return rc;
    print_euler_path_list_graph(list_graph, epath, len_epath);

    free(epath);
    return rc;
}





























