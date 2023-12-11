#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "errs.h"
#include "mtrx_graph.h"
#include "stack.h"

mtrxg_t *create_mtrx_graph(size_t count_v)
{
    mtrxg_t *graph = malloc(sizeof(mtrxg_t));
    if (graph == NULL)
        return NULL;

    graph->count_v = count_v;
    graph->arr = malloc(graph->count_v * sizeof(int *) + graph->count_v * graph->count_v * sizeof(int));
    if (graph->arr == NULL)
    {
        free(graph);
        graph->count_v = 0;
        return NULL;
    }
    int *data = (int *) (graph->arr + graph->count_v);
    for (size_t i = 0; i < graph->count_v; i++)
        graph->arr[i] = data + i * graph->count_v;

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
        graph->names[i] = NULL;
        for (size_t j = 0; j < graph->count_v; j++)
            graph->arr[i][j] = 0;
    }
    
    return graph;
}

int add_edge_mtrx_graph(mtrxg_t *graph, size_t v1, size_t v2)
{
    assert(graph != NULL);
    if (v1 >= graph->count_v || v2 >= graph->count_v)
        return ERR_EDGE;

    if (graph->arr[v1][v2] == 1 || graph->arr[v2][v1] == 1)
        return ERR_EXIST_EDGE;

    graph->arr[v1][v2] = 1;
    graph->arr[v2][v1] = 1;
    return OK;
}

void free_mtrx_graph(mtrxg_t **graph)
{
    free((*graph)->arr);
    for (size_t i = 0; i < (*graph)->count_v; i++)
        free((*graph)->names[i]);
    free((*graph)->names);
    free(*graph);
    *graph = NULL;
}

int export_to_dot_mtrx_graph(char *filename, mtrxg_t *graph)
{
    FILE *f;
    f = fopen(filename, "w");
    if (f == NULL)
        return ERR_FILE;
    
    fprintf(f, "graph graph_ {\nrankdir=LR;\nnode [shape = box];\n");
    for (size_t i = 0; i < graph->count_v; i++)
        for (size_t j = i + 1; j < graph->count_v; j++)
            if (graph->arr[i][j] == 1)
                fprintf(f, "\"%s\\n(%zu)\" -- \"%s\\n(%zu)\";\n", graph->names[i], i, graph->names[j], j);

    fprintf(f, "}\n");
    fclose(f);

    return OK;
}

int print_mtrx_graph(mtrxg_t *graph, char *filename)
{
    printf("Граф:\n");
    printf("  №  | ");
    for (size_t i = 0; i < graph->count_v; i++)
        printf("%5zu ", i);
    printf("\n");
    printf("------\n");
    for (size_t i = 0; i < graph->count_v; i++)
    {
        printf("%5zu: ", i);
        for (size_t j = 0; j < graph->count_v; j++)
            printf("%5d ", graph->arr[i][j]);
        printf("\n");
    }
    printf("\n");

    // char *filename = "graph/graph.gv";
    int rc = export_to_dot_mtrx_graph(filename, graph);
    if (rc != OK)
        return rc;
    printf("Данные о графе записаны в файл %s\n", filename);
    return OK;
}

void dfs_mtrx_graph(mtrxg_t *graph, bool used[], size_t v)
{
    used[v] = true;
    for (size_t i = 0; i < graph->count_v; i++)
        if (graph->arr[v][i] == 1 && !used[i])
            dfs_mtrx_graph(graph, used, i);
}

int connected_mtrx_graph(mtrxg_t *graph, bool *connected)
{
    bool *used = malloc(sizeof(bool) * graph->count_v);
    if (used == NULL)
        return ERR_MEM;
    for (size_t i = 0; i < graph->count_v; i++)
        used[i] = false;
    
    dfs_mtrx_graph(graph, used, 0);

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

static size_t degree_v_mtrx_graph(mtrxg_t *graph, size_t v)
{
    int degree = 0;
    for (size_t i = 0; i < graph->count_v; i++)
        degree += graph->arr[v][i];
    return degree;
}

// bool dirk_condition_mtrx_graph(mtrxg_t *graph)
// {
//     for (size_t i = 0; i < graph->count_v; i++)
//         if (degree_v_mtrx_graph(graph, i) < graph->count_v / 2)
//             return false;
//     return true;
// }

// bool ore_condition_mtrx_graph(mtrxg_t *graph)
// {
//     for (size_t i = 0; i < graph->count_v - 1; i++)
//         for (size_t j = i + 1; j < graph->count_v; j++)
//             if (graph->arr[i][j] == 0 && 
//             degree_v_mtrx_graph(graph, i) + degree_v_mtrx_graph(graph, j) < graph->count_v)
//                 return false;
//     return true;
// }

// static void ham_mtrx_graph(size_t ind, mtrxg_t *graph, bool *can_go, int *path, bool *find)
// {
//     for (size_t i = 0; i < ind; i++)
//         DBG_PRINT("%d ", path[i]);
//     DBG_PRINT("%c", '\n');

//     if (ind == graph->count_v)
//     {
//         *find = true;
//         return;
//     }

//     for (size_t i = 0; i < graph->count_v; i++)
//         if (graph->arr[path[ind - 1]][i] == 1 && can_go[i])
//         {
//             path[ind] = i;
//             can_go[i] = false;
//             if (ind <= graph->count_v)
//                 ham_mtrx_graph(ind + 1, graph, can_go, path, find);
//             else
//                 can_go[i] = true;
//         }
// }

// int find_ham_path_mtrx_graph(mtrxg_t *graph, int **ham_path)
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
//         ham_mtrx_graph(1, graph, can_go, path, &find);
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

// void print_ham_path_mtrx_graph(mtrxg_t *graph, int *ham_path)
// {
//     printf("Гамильтонов путь: ");
//     for (size_t i = 0; i < graph->count_v; i++)
//         printf("%d ", ham_path[i]);
//     printf("\n( %s", graph->names[0]);
//     for (size_t i = 1; i < graph->count_v; i++)
//         printf(" -> %s", graph->names[i]);
//     printf(")\n");
// }

size_t bytes_mtrx_graph(mtrxg_t *graph)
{
    size_t bytes = graph->count_v * sizeof(int *) + graph->count_v * graph->count_v * sizeof(int);
    for (size_t i = 0; i < graph->count_v; i++)
        bytes += (strlen(graph->names[i]) + 1) * sizeof(char);
    bytes += sizeof(char *) * graph->count_v;
    bytes += sizeof(mtrxg_t);

    return bytes;
}

size_t count_edges(mtrxg_t *graph)
{
    size_t count = 0;
    for (size_t i = 0; i < graph->count_v - 1; i++)
        for (size_t j = i + 1; j < graph->count_v; j++)
            count += graph->arr[i][j];
    return count;
}

mtrxg_t *copy_mtrx_graph(mtrxg_t *src)
{
    mtrxg_t *dst = create_mtrx_graph(src->count_v);
    memmove(dst->arr[0], src->arr[0], src->count_v * src->count_v * sizeof(int));
    return dst;
}

bool euler_path_exist_mtrx_graph(mtrxg_t *graph)
{
    int count_odd_v = 0;
    for (size_t i = 0; i < graph->count_v; i++)
        if (degree_v_mtrx_graph(graph, i) % 2 != 0)
            count_odd_v++;
    if (count_odd_v <= 2)
        return true;
    else
        return false;
}

static int find_less_connected_odd_v(mtrxg_t *graph)
{
    int less_connected_odd_v = -1;
    size_t len;
    int min_len = -1;
    for (size_t i = 0; i < graph->count_v; i++)
    {
        len = degree_v_mtrx_graph(graph, i);
        if (len % 2 != 0 && ((long int) len < min_len || min_len == -1))
        {
            min_len = len;
            less_connected_odd_v = i;
        }
    }
    return less_connected_odd_v;
}

int find_euler_path_mtrx_graph(mtrxg_t *graph, int **epath, size_t *len_epath)
{
    mtrxg_t *copy_graph = copy_mtrx_graph(graph);
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
        y = -1;
        for (size_t i = 0; i < copy_graph->count_v && y == -1; i++)
            if (copy_graph->arr[x][i] == 1)
                y = i;
        if (y != -1)
        {
            copy_graph->arr[x][y] = 0;
            copy_graph->arr[y][x] = 0;
#ifdef DEBUG
            printf("st: ");
            print_stack(st);
#endif
            push_stack(st, y);
        }
        else
        {
#ifdef DEBUG
            printf("path: ");
            print_stack(path);
#endif
            push_stack(path, x);
            pop_stack(st);
        }
    }

    *epath = path->arr;
    *len_epath = path->ps - path->arr + 1;
    free_stack(&st);
    free(path);
    free_mtrx_graph(&copy_graph);
    
    return OK;
}

void print_euler_path_mtrx_graph(mtrxg_t *graph, int *epath, size_t len_epath)
{
    printf("Эйлеров путь: ");
    for (size_t i = 0; i < len_epath; i++)
        printf("%d ", epath[i]);
    printf("\n( \"%s\"", graph->names[epath[0]]);
    for (size_t i = 1; i < len_epath; i++)
        printf(" -> \"%s\"", graph->names[epath[i]]);
    printf(" )\n");
}


