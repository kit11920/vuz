#ifndef LIST_GRAPH_H__
#define LIST_GRAPH_H__

#include <stdlib.h>
#include <stdbool.h>

#include "node_list.h"

typedef struct st_listg_t listg_t;
struct st_listg_t
{
    node_t **arr;
    char **names;
    size_t count_v;
};


/// @brief Создает граф в виде списка
/// @param count_v - кол-во вершин
/// @return граф
listg_t *create_list_graph(size_t count_v);

/// @brief Добавляет ребра в граф в виде списка
/// @param graph граф в виде списка
/// @param v1 узел ребра
/// @param v2 узел ребра
/// @return код ошибки
int add_edge_list_graph(listg_t *graph, size_t v1, size_t v2);

/// @brief Освобождает память из под графа в виде списка
/// @param graph граф в виде списка
void free_list_graph(listg_t **graph);

/// @brief Экспортирует граф в .gv формат для graphviz
/// @param filename название файла куда записывать
/// @param graph граф в виде списка
/// @return код ошикби
int export_to_dot_list_graph(char *filename, listg_t *graph);

/// @brief Выводит графа в виде списка
/// @param graph граф в виде списка
/// @param filename название файла куда запишуть граф
/// @return код ошиюки
int print_list_graph(listg_t *graph, char *filename);

/// @brief Создает копию графа
/// @param src графа в виде списка
/// @return копия
listg_t *copy_list_graph(listg_t *src);

/// @brief Глубинный поиск в граф в виде списка
/// @param graph граф в виде списка
/// @param used булевый массив использованыых узлов
/// @param v узел графа
void dfs_list_graph(listg_t *graph, bool used[], size_t v);

/// @brief Определяет является ли гра связным
/// @param graph граф в виде списка
/// @param connected связность
/// @return код ошибки
int connected_list_graph(listg_t *graph, bool *connected);

// /// @brief n - число вершин в данном графе; если степень 
// /// каждой вершины не меньше, чем целое от n / 2, то граф
// /// называется графом Дирака.
// /// @param graph граф в виде списка
// /// @return да/нет
// bool dirk_condition_list_graph(listg_t *graph);

// /// @brief сумма степеней несмежных вершин >= числу вершин графа
// /// @param graph граф в виде списка
// /// @return да/нет
// bool ore_condition_list_graph(listg_t *graph);

// /// @brief Ищет гамильтонов путь в граф в виде списка
// /// @param graph граф в виде списка
// /// @param ham_path гамильтонов путь
// /// @return код ошибки
// int find_ham_path_list_graph(listg_t *graph, int **ham_path);

// /// @brief Выводит гамильтонов путь
// /// @param graph граф в виде списка
// /// @param ham_path гамильтонов путь
// void print_ham_path_list_graph(listg_t *graph, int *ham_path);

/// @brief Вычисляет размер графа в виде списка
/// @param graph граф в виде списка
/// @return байт
size_t bytes_list_graph(listg_t *graph);

// bool euler_path_exist_list_graph(listg_t *graph);

// int find_euler_path_list_graph(listg_t *graph, int **epath);







#endif

