#ifndef EFFICIENCY_FIND_FILL_H__
#define EFFICIENCY_FIND_FILL_H__

#include <stdlib.h>

#include "errs.h"

#define MIN_COUNT_REAPET 5

typedef unsigned long long (* measure_time_t)(size_t);

/// @brief Заполняет массива данных для заполнения дерева
/// @param l данные не меньше
/// @param r данные не больше
/// @param arr массив
/// @param len_arr длина массива
/// @param max_len_arr максимальная длина массива
void full_arr_data_to_add(int l, int r, int *arr, size_t *len_arr, size_t max_len_arr);

/// @brief Выделяет память и заполняет массива данных для заполнения дерева
/// @param arr массива
/// @param height высота дерева для заполнения
/// @param len_arr длина массива
/// @return код ошибки
int make_arr_data_to_add(int **arr, size_t height, size_t *len_arr);

/// @brief Заполняет дерево на основе данных из массива
/// @param root указатель на указатель на корень дерева
/// @param arr массив
/// @param len_arr  длина массива
/// @return код ошибки
int fill_tree_based_data_arr(node_t **root, int *arr, size_t len_arr);

/// @brief Создает полность заполненое дерева
/// @param root указатель на указатель на корень дерева
/// @param height высота дерева
/// @return код ошибки
int make_full_tree(node_t **root, size_t height);

/// @brief Создает левостороннее дерево
/// @param root указатель на указатель на корень дерева
/// @param height высота дерева
/// @return код ошибки
int make_left_tree(node_t **root, size_t height);

/// @brief Замеряет время работы функции заполнения левостороннего дерева
/// @param height высота дерева
/// @return код ошибки
unsigned long long fill_left_tree_measure_time(size_t height);

/// @brief Замеряет время работы функции полного заполнения дерева
/// @param height высота дерева
/// @return код ошибки
unsigned long long fill_full_tree_measure_time(size_t height);

/// @brief Замеряет время работы функции поиска в левостороннем дереве
/// @param height высота дерева
/// @return код ошибки
unsigned long long find_left_tree_measure_time(size_t height);

/// @brief Замеряет время работы функции поиска в полностью заполненном дереве
/// @param height высота дерева
/// @return код ошибки
unsigned long long find_full_tree_measure_time(size_t height);

/// @brief Уточняет время замера до rse < 5%
/// @param measure - функция замера временеи
/// @param height - высота дерева
/// @param t - массив замеров времени
/// @param len_t - длина массива t
/// @param time - время замера, результирующее
/// @return код ошибки
int gettime(measure_time_t measure, size_t height, unsigned long long *t, size_t len_t, long long *time);

/// @brief Создает таблицу сравнения алгоритмов заполнения дерева и поиска в нем от высоты дерева и ветвистости 
/// @return код ошибки
int make_compare_table_fill_find(void);







#endif

