#ifndef ACTION_H__
#define ACTION_H__

#include "country_struct.h"
#include "work_table.h"

/// @brief Вводит поле по которому будет проходить сравнение
/// @param [out] searching - структура страны в которой заполнено только искомое поле
/// @param [out] cmp - функция сравнения по искомому полю
/// @return 
int get_field_and_cmp(struct country_t *searching, cmp_country_t *cmp);

/// @brief Ищет и выводит страну по введенному искомому полю
/// @param [in] table - массив стран
/// @param [in] len_table - длина массива table
/// @return 
int act_find_and_print_countries(const struct country_t table[], const size_t len_table);

/// @brief Добавляет страну в конец массива стран и в конец файла
/// @param [in] filename filename - имя файла
/// @param [in out] table - массив стран
/// @param [in out] len_table - длина массива table (указатель)
/// @return код ошибки
int act_add_country(char *filename, struct country_t table[], size_t *len_table);

/// @brief Удаляет страну по введенному искомому полю из массива и из файла
/// Обновляет массив стран
/// @param [in] filename - имя файла
/// @param [in out] table - массив стран
/// @param [in out] len_table - длина массива table (указатель)
/// @return код ошибки
int act_del_country(char *filename, struct country_t table[], size_t *len_table);

/// @brief Выводит список стран на выбранном материке, со стоимостью ниже указанной, где
/// можно заняться указанным видом спорта
/// @param [in] table - массив стран
/// @param [in] len_table - длина массива table 
/// @return код ошибки
int act_find_and_print_special_country(const struct country_t table[], const size_t len_table);

#endif

