#ifndef EFFICIENCY_H__
#define EFFICIENCY_H__

#include <stdlib.h>

#include "country_struct.h"

/// @brief Переписывает время полета дл стран на рандомное
/// @param [in out] table - массив стран
/// @param [in] len_table - длина массива table
void rewrite_rand_country_time(struct country_t table[], const size_t len_table);

/// @brief Возвращает время в мс в момент вызова функции
/// @return Время в мс в момент вызова функции
unsigned long long ms_now(void);

/// @brief Возвращает время в мс работы сортировки пузырьком на исходной таблице
/// @param [in] table - массив стран
/// @param [in] len_table - длина массива table
/// @return Время в мс
unsigned long long gettime_bubble_sort_orig_table(struct country_t table[], const size_t len_table);

/// @brief Возвращает время в мс работы сортировки слиянием на исходной таблице
/// @param [in] table - массив стран
/// @param [in] len_table - длина массива table
/// @return Время в мс
unsigned long long gettime_merge_sort_orig_table(struct country_t table[], const size_t len_table);

/// @brief Возвращает время в мс работы сортировки пузырьком на таблице ключей
/// @param [in] table - массив стран
/// @param [in] len_table - длина массива table
/// @return Время в мс
unsigned long long gettime_bubble_sort_key_table(struct country_t table[], const size_t len_table);

/// @brief Возвращает время в мс работы сортировки слиянием на таблице ключей
/// @param [in] table - массив стран
/// @param [in] len_table - длина массива table
/// @return Время в мс
unsigned long long gettime_merge_sort_key_table(struct country_t table[], const size_t len_table);

/// @brief Выводит таблицу сравнения времени работы сортировок пузырьком и слиянием для массивов стран и ключей
/// @param [in] data_filename - имя файла большой таблицы стран
/// @return код ошибки
int make_compare_table(char *data_filename);















#endif
