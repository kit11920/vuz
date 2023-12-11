#ifndef EFFICIENCY_HASH_TREE_H__
#define EFFICIENCY_HASH_TREE_H__

#include "tree.h"
#include "balanced_tree.h"
#include "external_hashing.h"
#include "internal_hashing.h"

#define MIN_COUNT_REAPET 1000
#define COUNT_CALCS 1000



typedef unsigned long long (*measure_time_t)(void *data_struct, int *arr, size_t len_arr);

/// @brief Замеряет время работы цикла
/// @param data_struct структура данных
/// @param arr массив данных в структуре
/// @param len_arr длина массива
/// @return время работы цикла
unsigned long long measure_time_for(void *data_struct, int *arr, size_t len_arr);

/// @brief Замеряет работы функции поиска для этой структуры данных
/// @param data_struct структура данных
/// @param arr массив данных в структуре
/// @param len_arr длина массива
/// @return время работы функции поиска для этой структуры данных
unsigned long long measure_time_bs_tree(void *data_struct, int *arr, size_t len_arr);

/// @brief Замеряет работы функции поиска для этой структуры данных
/// @param data_struct структура данных
/// @param arr массив данных в структуре
/// @param len_arr длина массива
/// @return время работы функции поиска для этой структуры данных
unsigned long long measure_time_bal_tree(void *data_struct, int *arr, size_t len_arr);

/// @brief Замеряет работы функции поиска для этой структуры данных
/// @param data_struct структура данных
/// @param arr массив данных в структуре
/// @param len_arr длина массива
/// @return время работы функции поиска для этой структуры данных
unsigned long long measure_time_ex_hash(void *data_struct, int *arr, size_t len_arr);

/// @brief Замеряет работы функции поиска для этой структуры данных
/// @param data_struct структура данных
/// @param arr массив данных в структуре
/// @param len_arr длина массива
/// @return время работы функции поиска для этой структуры данных
unsigned long long measure_time_in_hash(void *data_struct, int *arr, size_t len_arr);

/// @brief Замеряет работы функции поиска для этой структуры данных при rse < 5%
/// @param measure функция замера
/// @param exp структура данных
/// @param arr массив данных
/// @param len_arr размер массива
/// @param t массив замеров
/// @param len_t длина массива замеров
/// @param time время работы функции
/// @return код ошибки
int gettime_hash_tree(measure_time_t measure, void *exp, int *arr, size_t len_arr, unsigned long long *t, size_t len_t, long long *time);

/// @brief Функция вычитаня 
/// @param time время работы
/// @param for_time время цикла
/// @return время
long long minus_for_time(long long time, long long for_time);

/// @brief Выводит таблицу сравнения сруктур данныз
/// @param tree бинарное дерево поиска
/// @param btree сбалансированное дерево
/// @param ex_htab таблица внешнего хеширования
/// @param in_htab таблица внутреннего хеширования
/// @param data_arr массив данных
/// @param len_arr длина массива
/// @return код ошибки
int make_compare_table_hash_tree(node_t *tree, bnode_t *btree, ex_hash_t *ex_htab, in_hash_t *in_htab, int *data_arr, size_t len_arr);






































#endif

