#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "errs.h"
#include "list_graph.h"
#include "node_list.h"
#include "stack.h"


listg_t *create_list_graph(size_t count_v)
{
    listg_t *graph = malloc(sizeof(listg_t));
    if (graph == NULL)
        return NULL;

    graph->count_v = count_v;
    graph->arr = malloc(graph->count_v * sizeof(node_t *));
    if (graph->arr == NULL)
    {
        free(graph);
        graph->count_v = 0;
        return NULL;
    }

    graph->names = malloc(graph->count_v * sizeof(char *));
    if (graph->names == NULL)
    {
        free(graph->arr);
        free(graph);
        graph->count_v = 0;
        return NULL;
    }

    for (size_t i = 0; i < graph->count_v; i++)
    {
        graph->arr[i] = NULL;
        graph->names[i] = NULL;
    }
    
    return graph;
}

int add_edge_list_graph(listg_t *graph, size_t v1, size_t v2)
{
    assert(graph != NULL);
    if (v1 >= graph->count_v || v2 >= graph->count_v)
        return ERR_EDGE;

    if (find_list(graph->arr[v1], v2) != NULL || find_list(graph->arr[v2], v1) != NULL)
        return ERR_EXIST_EDGE;
        
    node_t *tmp1, *tmp2;
    tmp2 = create_node_list(v2);
    if (tmp2 == NULL)
        return ERR_MEM; 
    tmp1 = create_node_list(v1);
    if (tmp1 == NULL)
    {
        free(tmp2);
        return ERR_MEM; 
    }
    
    graph->arr[v1] = add_sort_node_list(graph->arr[v1], tmp2);
    graph->arr[v2] = add_sort_node_list(graph->arr[v2], tmp1);
    
    return OK;
}

void free_list_graph(listg_t **graph)
{
    for (size_t i = 0; i < (*graph)->count_v; i++)
    {
        if ((*graph)->arr[i] != NULL)
            free_list(&(*graph)->arr[i]);
        free((*graph)->names[i]);
    }
    free((*graph)->arr);
    free((*graph)->names);
    free(*graph);
    *graph = NULL;
}

int export_to_dot_list_graph(char *filename, listg_t *graph)
{
    FILE *f;
    f = fopen(filename, "w");
    if (f == NULL)
        return ERR_FILE;
    
    fprintf(f, "graph graph_ {\nrankdir=LR;\nnode [shape = box];\n");
    node_t *bind;
    for (size_t i = 0; i < graph->count_v; i++)
    {
        bind = graph->arr[i];
        while (bind != NULL)
        {
            if (bind->v > i)
                fprintf(f, "\"%s\\n(%zu)\" -- \"%s\\n(%zu)\";\n", graph->names[i], i, graph->names[bind->v], bind->v);
            bind = bind->next;
        }
    }

    fprintf(f, "}\n");
    fclose(f);

    return OK;
}

int print_list_graph(listg_t *graph, char *filename)
{
    // bool no_lonely_v = false;
    // printf("Узлы без связей: ");
    // for (size_t i = 0; i < graph->count_v; i++)
    // {
    //     if (graph->arr[i] == NULL)
    //         printf("%zu ", graph->arr[i]->v);
    //     else
    //         no_lonely_v = true;
    // }
    // if (no_lonely_v)
    //     printf("-");
    // printf("\n");
    printf("Граф:\n");
    for (size_t i = 0; i < graph->count_v; i++)
    {
        printf("%zu: ", i);
        print_list(graph->arr[i]);
    }

    // char *filename = "graph/graph.gv";
    int rc = export_to_dot_list_graph(filename, graph);
    if (rc != OK)
        return rc;
    printf("Данные о графе записаны в файл %s\n", filename);
    return OK;
}

listg_t *copy_list_graph(listg_t *src)
{
    listg_t *dst = create_list_graph(src->count_v);

    for (size_t i = 0; i < src->count_v; i++)
    {
        dst->arr[i] = copy_list(src->arr[i]);
        if (dst->arr[i] == NULL)
        {
            free_list_graph(&dst);
            return NULL;
        }
    }
    return dst;
}

void dfs_list_graph(listg_t *graph, bool used[], size_t v)
{
    used[v] = true;
    node_t *node = graph->arr[v];
    while (node != NULL)
    {
        if (!used[node->v])
            dfs_list_graph(graph, used, node->v);
        node = node->next;
    }
}

int connected_list_graph(listg_t *graph, bool *connected)
{
    bool *used = malloc(sizeof(bool) * graph->count_v);
    if (used == NULL)
        return ERR_MEM;
    for (size_t i = 0; i < graph->count_v; i++)
        used[i] = false;
    
    dfs_list_graph(graph, used, 0);

    *connected = true;
    for (size_t i = 0; i < graph->count_v && *connected; i++)
    {
        DBG_PRINT("connection: %zu - %d\n",i,  used[i]);
        if (!used[i])
            *connected = false;
    }

    free(used);
    return OK;
}

// bool dirk_condition_list_graph(listg_t *graph)
// {
//     for (size_t i = 0; i < graph->count_v; i++)
//         if (len_list(graph->arr[i]) < graph->count_v / 2)
//             return false;
//     return true;
// }

// bool ore_condition_list_graph(listg_t *graph)
// {
//     for (size_t i = 0; i < graph->count_v - 1; i++)
//         for (size_t j = i + 1; j < graph->count_v; j++)
//             if (find_list(graph->arr[i], j) == NULL && 
//             (len_list(graph->arr[i]) + len_list(graph->arr[j])) < graph->count_v)
//                 return false;
//     return true;
// }

// static void ham_list_graph(size_t ind, listg_t *graph, bool *can_go, int *path, bool *find)
// {
//     for (size_t i = 0; i < ind; i++)
//         DBG_PRINT("%d ", path[i]);
//     DBG_PRINT("%c", '\n');

//     if (ind == graph->count_v)
//     {
//         *find = true;
//         return;
//     }

//     node_t *node = graph->arr[path[ind - 1]];
//     while (node != NULL)
//     {
//         if (can_go[node->v])
//         {
//             path[ind] = node->v;
//             can_go[node->v] = false;
//             if (ind <= graph->count_v)
//                 ham_list_graph(ind + 1, graph, can_go, path, find);
//             else
//                 can_go[node->v] = true;
//         }
//         node = node->next;
//     }
// }

// int find_ham_path_list_graph(listg_t *graph, int **ham_path)
// {
//     *ham_path = NULL;
    
//     bool *can_go = malloc(sizeof(bool) * graph->count_v);
//     if (can_go == NULL)
//         return ERR_MEM;

//     int *path = malloc(sizeof(int) * graph->count_v);
//     if (path == NULL)
//     {
//         free(can_go);
//         return ERR_MEM;
//     }

//     bool find = false;
//     for (size_t i = 0; i < graph->count_v && !find; i++)
//     {
//         for (size_t j = 0; j < graph->count_v; j++)
//             can_go[j] = true;
//         can_go[i] = false;

//         path[0] = i;
//         ham_list_graph(1, graph, can_go, path, &find);
//     }

//     int rc = OK;
//     if (!find)
//     {
//         free(path);
//         rc = ERR_NO_HAM_PATH;
//     }
//     else
//         *ham_path = path;

//     free(can_go);
//     return rc;
// }

// void print_ham_path_list_graph(listg_t *graph, int *ham_path)
// {
//     printf("Гамильтонов путь: ");
//     for (size_t i = 0; i < graph->count_v; i++)
//         printf("%d ", ham_path[i]);
//     printf("\n( %s", graph->names[0]);
//     for (size_t i = 1; i < graph->count_v; i++)
//         printf(" -> %s", graph->names[i]);
//     printf(")\n");
// }

size_t bytes_list_graph(listg_t *graph)
{
    size_t bytes = 0;
    for (size_t i = 0; i < graph->count_v; i++)
    {
        bytes += len_list(graph->arr[i]) * sizeof(node_t);
        bytes += (strlen(graph->names[i]) + 1) * sizeof(char);
    }
    bytes += graph->count_v * sizeof(char *);
    bytes += graph->count_v * sizeof(node_t *);
    bytes += sizeof(listg_t);

    return bytes;
}


bool euler_path_exist_list_graph(listg_t *graph)
{
    int count_odd_v = 0;
    for (size_t i = 0; i < graph->count_v; i++)
        if (len_list(graph->arr[i]) % 2 != 0)
            count_odd_v++;
    if (count_odd_v <= 2)
        return true;
    else
        return false;
}

int find_less_connected_odd_v(listg_t *graph)
{
    int less_connected_odd_v = -1;
    size_t len;
    int min_len = -1;
    for (size_t i = 0; i < graph->count_v; i++)
    {
        len = len_list(graph->arr[i]);
        if (len % 2 != 0 && ((long int) len < min_len || min_len == -1))
        {
            min_len = len;
            less_connected_odd_v = i;
        }
    }
    DBG_PRINT("les connected: %d\n", less_connected_odd_v);
    return less_connected_odd_v;
}

int find_euler_path_list_graph(listg_t *graph, int **epath, size_t *len_epath)
{
    listg_t *copy_graph = copy_list_graph(graph);
    if (copy_graph == NULL)
        return ERR_MEM;
    
    stack_t *path = create_stack(graph->count_v * (graph->count_v - 1) / 2 + 1);
    if (path == NULL)
    {
        free(copy_graph);
        return ERR_MEM;
    }
    stack_t *st = create_stack(graph->count_v * (graph->count_v - 1) / 2 + 1);
    if (st == NULL)
    {
        free(copy_graph);
        free(path);
        return ERR_MEM;
    }

    int start_id = find_less_connected_odd_v(copy_graph);
    if (start_id == -1)
        start_id = 0;
    
    int x, y;
#ifdef DEBUG
    printf("st: ");
    print_stack(st);
#endif
    push_stack(st, start_id);
    while (!is_empty_stack(st))
    {
        x = *st->ps;
        if (copy_graph->arr[x] != NULL)
        {
            y = copy_graph->arr[x]->v;
            copy_graph->arr[x] = del_list(copy_graph->arr[x], y);
            copy_graph->arr[y] = del_list(copy_graph->arr[y], x);
#ifdef DEBUG
            printf("st: ");
            print_stack(st);
#endif
            push_stack(st, y);
        }
        else
        {
#ifdef DEBUG
            print_list_graph(copy_graph, "graph/tmp.gv");
            printf("path: ");
            print_stack(path);
            printf("st: ");
            print_stack(st);
#endif
            push_stack(path, x);
            pop_stack(st);
        }
    }

    *epath = path->arr;
    *len_epath = path->ps - path->arr + 1;
    free_stack(&st);
    free(path);
    free_list_graph(&copy_graph);
    
    return OK;
}

void print_euler_path_list_graph(listg_t *graph, int *epath, size_t len_epath)
{
    printf("Эйлеров путь: ");
    for (size_t i = 0; i < len_epath; i++)
        printf("%d ", epath[i]);
    printf("\n( \"%s\"", graph->names[epath[0]]);
    for (size_t i = 1; i < len_epath; i++)
        printf(" -> \"%s\"", graph->names[epath[i]]);
    printf(" )\n");
}






























