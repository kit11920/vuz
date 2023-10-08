#ifndef SORTS_H__
#define SORTS_H__

#include <stdlib.h>


#include "country_struct.h"
#include "work_table.h"

/// @brief Сортироваку пузырьком исходной таблицы
/// @param [in out] table - массив стран
/// @param [in] len_table - длина массива table
void bubble_sort_orig_table(struct country_t table[], const size_t len_table);

/// @brief Слияние подмассивов массива table (первы массив [l:m) и [m:r])
/// @param [in out] table - массив стран
/// @param [in] l - индекс первого элемента 
/// @param [in] m - индекс первого элемента 2го массива и запоследнего элемента первого
/// @param [in] r - индекс последнего элемента второго массивы (r - не запоследний а последний элемент)
void merge_orig_table(struct country_t table[], size_t l, size_t m, size_t r);

/// @brief Сортировка слиянием исходной таблицы
/// @param [in out] table - массив стран
/// @param [in] l - индекс первого элемента
/// @param [in] r - индекс последнего элемента
void merge_sort_orig_table(struct country_t table[], size_t l, size_t r);

/// @brief Создает таблицу ключей
/// @param [in out] table - массив стран
/// @param [in] len_table - длина массива table и key_table
/// @param [out] key_table - массив ключей
void make_key_table(const struct country_t table[], const size_t len_table, struct key_table_t key_table[]);

/// @brief Сортироваку пузырьком таблицы ключей
/// @param [in out] table  - массив ключей
/// @param [in] len_table - длина массива table
void bubble_sort_key_table(struct key_table_t table[], size_t len_table);

/// @brief Слияние подмассивов массива table (первы массив [l:m) и [m:r])
/// @param [in out] table - массив ключей
/// @param [in] l - индекс первого элемента
/// @param [in] m - индекс первого элемента 2го массива и запоследнего элемента первого
/// @param [in] r - индекс последнего элемента второго массивы (r - не запоследний а последний элемент)
void merge_key_table(struct key_table_t table[], size_t l, size_t m, size_t r);

/// @brief Сортировка слиянием таблицы ключей
/// @param [in out] table - массив ключей
/// @param [in] l - индекс первого элемента
/// @param [in] r - индекс последнего элемента
void merge_sort_key_table(struct key_table_t table[], size_t l, size_t r);




#endif
