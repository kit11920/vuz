#ifndef WORK_TABLE_H__
#define WORK_TABLE_H__



#include <stdio.h>

#include "country_struct.h"

typedef int (*cmp_country_t)(const struct country_t *l, const struct country_t *r);


/// @brief Функция стравнения структур по названию страны
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_name(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур по столице страны
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_capital(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур по континенту страны
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_continent(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур по надобности визы
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_visa(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур по времени полета до страны
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_time(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур минимальной стоимости отдыха в стране
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_cost_min(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур по количеству достопримечательностей в стране
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_exrsn_trsm_count_sights(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур по виду достопримечательностей в страненазванию страны
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_exrsn_trsm_type_sights(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур по сезону пляжного туризма
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_beach_trsm_season(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур по температуре воздуха
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_beach_trsm_air_tempr(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур по температуре воды
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_beach_trsm_water_tempr(const struct country_t *l, const struct country_t *r);

/// @brief Функция стравнения структур по виду спорта в стране
/// @param [in] l - левая структура сравнения
/// @param [in] r - правая структура сравнения
/// @return как в функции strcmp
int cmp_country_sport_trsm_sport_type(const struct country_t *l, const struct country_t *r);


/// @brief Ищет страны по полю, 
/// искомое поле записано в структуре searching и по нему идет сравнение в функции cmp
/// Индексы подходящих стран записываются в массив ind_arr (индексы в массиве а не в таблице)
/// @param [in] table - массив стран
/// @param [in] len_table - длина массива стран
/// @param [in] searching - структура с искомым полем
/// @param [in] cmp - функция сравнения структур по искомому полю
/// @param [out] ind_arr - массив индексов подходящих стран
/// @param [out] len_ind_arr - указатель на длину массива ind_arr
void find_country(const struct country_t table[], const size_t len_table, 
                const struct country_t *searching, cmp_country_t cmp, int ind_arr[], size_t *len_ind_arr);

/// @brief Записывает страну в файл
/// @param [in out] f - файловая переменная
/// @param [in] country - структура страны (указатель)
void file_write_country(FILE *f, const struct country_t *country);

/// @brief Перезаписывает таблицу стран в файл
/// @param [in] filename - имя файла
/// @param [in] table - массив стран
/// @param [in] len_table - длина массива table
/// @return код ошибки
int file_write_table(char *filename, const struct country_t table[], const size_t len_table);

/// @brief Удаляет страну с индексом ind_searching(инекс в массиве) из массива стран 
/// предполагается что индексы в таблице идут по возрастанию
/// @param [out] table - массив стран
/// @param [out] len_table - длина массива table
/// @param [in] ind_searching - индекс удаляемой страны
/// @return код ошибки
int del_country(struct country_t table[], size_t *len_table, const int ind_searching);

#endif




