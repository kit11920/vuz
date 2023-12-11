#ifndef EX_HASHING_H__
#define EX_HASHING_H__

#include "stdlib.h"

#define MAX_MID_CMPS 3.0

// #define MAX_LEN_LIST_HASH 3

typedef struct list_node_st lnode_t;
struct list_node_st
{
    int data;
    lnode_t *next;
};

// метод  деления, внешнее хеширования (метод цепочек)
typedef struct st_ex_hash ex_hash_t;
struct st_ex_hash
{
    size_t m;      // simple N < M, len_arr == m
    lnode_t **arr;
};

/// @brief Ищет наименьшее простое число которое >= n
/// @param n - число
/// @return наименьшее простое число которое >= n
size_t find_simple_bigger_n(size_t n);

/// @brief Создает и производит началюную инициализацию таблицы внешнего хеширования
/// @return таблица внешнего хеширования
ex_hash_t create_ex_hash_table(void);

/// @brief Создает узел списка
/// @param data - данные в узле
/// @return узел списка
lnode_t *create_list_node(int data);

/// @brief Освобождает память из под списка
/// @param head - голова списка
void free_list(lnode_t **head);

/// @brief Освобождает память из под таблицы внешнего хеширования
/// @param htable - талица внешнего хеширования
void free_ex_hash_tab(ex_hash_t *htable);

/// @brief Заполняет таблицу внешнего хеширования по массиву
/// @param htable - талица внешнего хеширования
/// @param arr - массив данных
/// @param len_arr - длина массива
/// @return код ошибки
int fill_ex_hash_table(ex_hash_t *htable, int arr[], size_t len_arr);

/// @brief Заполняет хт внешнего хеширования с определенным размером
/// @param htable хт внешнего хеширования
/// @param arr массив данных
/// @param m размер хт
/// @param len_arr длина массива
/// @return код ошибки
int fill_ex_hash_table_with_m(ex_hash_t *htable, int arr[], size_t len_arr, size_t m);

/// @brief Переводит список в строку
/// @param head - указатель на голову списка
/// @return строка
char *list_to_str(lnode_t *head);

/// @brief Выводит таблицу внешнего хеширования
/// @param htable - талица внешнего хеширования
void print_ex_hash_table(ex_hash_t *htable);

/// @brief Считает сколько сравнения надо для поиска
/// @param htable - талица внешнего хеширования
/// @return кол-во сравнений
size_t count_comparison_ex_hash_table(ex_hash_t *htable);

double mid_cmp_ex_hash_table(ex_hash_t *htable);

/// @brief Считает сколько байт занимает таблица 
/// @param htable - талица внешнего хеширования
/// @return кол-во байт
size_t mem_bytes_ex_hash_table(ex_hash_t *htable);

/// @brief Ищет данные в таблице хеширования
/// @param htable - талица внешнего хеширования
/// @param data - данные
/// @return указатель на найденные данные
int *find_ex_hash_table(ex_hash_t *htable, int data);
























#endif


