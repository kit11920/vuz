#ifndef INTERNAL_HASHING_H__
#define INTERNAL_HASHING_H__

#include <stdlib.h>

typedef struct st_ihdata_t ihdata_t;

struct st_ihdata_t
{
    int data;
};

// метод  деления, внутреннее хеширования (линейная адресация)
typedef struct st_in_hash in_hash_t;
struct st_in_hash
{
    size_t m;      // simple M >= 1.2N, len_arr == m
    ihdata_t **arr;
};

/// @brief Создает хеш таблицу внутреннего хеширования
/// @return зеш таблица
in_hash_t create_in_hash_table(void);

/// @brief Освобождает память из под хеш таблицы внутреннего хеширования
/// @param htable хеш таблица внутреннего хеширования
void free_in_hash_tab(in_hash_t *htable);

/// @brief Выделяет память под данные хт внутреннего хеширования
/// @param data данные 
/// @return структура данных
ihdata_t *create_data_in_hash_table(int data);

/// @brief Заполняет хт внутреннего хеширования с оптимальным размером
/// @param htable хт внутреннего хеширования
/// @param arr массив данных
/// @param len_arr длина массива
/// @return код ошибки
int fill_in_hash_table(in_hash_t *htable, int arr[], size_t len_arr);

/// @brief Заполняет хт внутреннего хеширования с определенным размером
/// @param htable хт внутреннего хеширования
/// @param arr массив данных
/// @param m размер хт
/// @param len_arr длина массива
/// @return код ошибки
int fill_in_hash_table_with_m(in_hash_t *htable, int arr[], size_t len_arr, size_t m);

/// @brief Выводит хт внутреннего хеширования
/// @param htable хт внутреннего хеширования
void print_in_hash_table(in_hash_t *htable);

/// @brief Считает кол-во сравнения в хт внутреннего хеширования
/// @param htable хт внутреннего хеширования
/// @return кол-во сравнения в хт внутреннего хеширования
size_t count_comparison_in_hash_table(in_hash_t *htable);

/// @brief Считает среднее кол-во сравнения в хт внутреннего хеширования
/// @param htable хт внутреннего хеширования
/// @return ср кол-во сравнения в хт внутреннего хеширования
double mid_cmp_in_hash_table(in_hash_t *htable);

/// @brief Считает сколько байт занимает хт внутреннего хеширования
/// @param htable хт внутреннего хеширования
/// @return байт
size_t mem_bytes_in_hash_table(in_hash_t *htable);

/// @brief ищет данные в хт внутреннего хеширования
/// @param htable хт внутреннего хеширования
/// @param data данные
/// @return указатель на найденные данные
int *find_in_hash_table(in_hash_t *htable, int data);




























#endif

