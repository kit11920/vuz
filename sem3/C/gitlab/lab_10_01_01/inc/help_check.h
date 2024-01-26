#ifndef HELP_CHECK_H__
#define HELP_CHECK_H__

#include "data.h"
#include "errs.h"

/// @brief Создает список на основе данных которые хранятся в массиве
/// @param [out] head - указатель на указатель на голову созданного списка
/// @param [in] arr - массив с данными
/// @param [in] len_arr - длина массива arr
void create_list_based_arr(node_t **head, country_t arr[], size_t len_arr);

/// @brief Сравнивает структуры стран
/// @param [in] l - структура страны (указатель)
/// @param [in] r - структура страны (указатель)
/// @return 0 - если они одинаковые, 1 - есди разные
int cmp_country_all(void *l, void *r);

/// @brief Сравнивает списки
/// @param [in] l - список
/// @param [in] r - список
/// @return 0 - если они одинаковые, 1 - есди разные
int cmp_list(node_t *l, node_t *r);

#endif
