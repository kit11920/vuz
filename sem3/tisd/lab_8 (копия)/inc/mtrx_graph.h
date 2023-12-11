#ifndef MTRX_GRAPH_H__
#define MTRX_GRAPH_H__

#include <stdlib.h>

typedef struct st_mtrxg_t mtrxg_t;
struct st_mtrxg_t
{
    int **arr;
    char **names;
    size_t count_v;
};




/// @brief Создает граф в виде матрицы
/// @param count_v - кол-во вершин
/// @return граф
mtrxg_t *create_mtrx_graph(size_t count_v);

/// @brief Добавляет ребра в граф в виде матрицы
/// @param graph граф в виде матрицы
/// @param v1 узел ребра
/// @param v2 узел ребра
/// @return код ошибки
int add_edge_mtrx_graph(mtrxg_t *graph, size_t v1, size_t v2);

/// @brief Освобождает память из под графа в виде матрицы
/// @param graph граф в виде матрицы
void free_mtrx_graph(mtrxg_t **graph);

/// @brief Экспортирует граф в .gv формат для graphviz
/// @param filename название файла куда записывать
/// @param graph граф в виде матрицы
/// @return код ошикби
int export_to_dot_mtrx_graph(char *filename, mtrxg_t *graph);

/// @brief Выводит графа в виде матрицы
/// @param graph граф в виде матрицы
/// @param filename название файла куда запишуть граф
/// @return код ошиюки
int print_mtrx_graph(mtrxg_t *graph, char *filename);

/// @brief Создает копию графа
/// @param src графа в виде матрицы
/// @return копия
mtrxg_t *copy_mtrx_graph(mtrxg_t *src);

/// @brief Глубинный поиск в граф в виде матрицы
/// @param graph граф в виде матрицы
/// @param used булевый массив использованыых узлов
/// @param v узел графа
void dfs_mtrx_graph(mtrxg_t *graph, bool used[], size_t v);

/// @brief Определяет является ли гра связным
/// @param graph граф в виде матрицы
/// @param connected связность
/// @return код ошибки
int connected_mtrx_graph(mtrxg_t *graph, bool *connected);

// /// @brief n - число вершин в данном графе; если степень 
// /// каждой вершины не меньше, чем целое от n / 2, то граф
// /// называется графом Дирака.
// /// @param graph граф в виде матрицы
// /// @return да/нет
// bool dirk_condition_mtrx_graph(mtrxg_t *graph);

// /// @brief сумма степеней несмежных вершин >= числу вершин графа
// /// @param graph граф в виде матрицы
// /// @return да/нет
// bool ore_condition_mtrx_graph(mtrxg_t *graph);

// /// @brief Ищет гамильтонов путь в граф в виде матрицы
// /// @param graph граф в виде матрицы
// /// @param ham_path гамильтонов путь
// /// @return код ошибки
// int find_ham_path_mtrx_graph(mtrxg_t *graph, int **ham_path);

// /// @brief Выводит гамильтонов путь
// /// @param graph граф в виде матрицы
// /// @param ham_path гамильтонов путь
// void print_ham_path_mtrx_graph(mtrxg_t *graph, int *ham_path);

/// @brief Вычисляет размер графа в виде матрицы
/// @param graph граф в виде матрицы
/// @return байт
size_t bytes_mtrx_graph(mtrxg_t *graph);

size_t count_edges(mtrxg_t *graph);



























#endif

