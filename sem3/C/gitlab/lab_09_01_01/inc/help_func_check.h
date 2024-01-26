#ifndef HELP_FUNC_CHECK_H__
#define HELP_FUNC_CHECK_H__

#include <stdlib.h>

#include "film.h"


/// @brief Сравнивает фильмы по всем полям (для check)
/// @param [in] pl - указатель на фильм 1 
/// @param [in] pr - указатель на фильм 2 
/// @return 0 - если функции одинаковые, 1 - если нет
int film_cmp_films(const struct film_t *pl, const struct film_t *pr);

// /// @brief Сортируем массив классическим пузырьком, отдельной проверки не требует (для check)
// /// @param [out] farr - массив структур (указатель)
// /// @param [in] len_arr - длина массива (указатель)
// /// @param [in] cmp - функция сравнения 
// void farr_sort(struct film_t *farr, const size_t len_arr, uni_cmp_t cmp);

/// @brief 
/// @param farr 
/// @param len_arr 
/// @param cmp 
/// @return 
int if_arr_sorted(struct film_t *farr, size_t len_arr, uni_cmp_t cmp);


/// @brief Создает массив структур из массивов элементов структуры
/// В каждом из массивов индекс элеменььтов соответствует индексу образованного элемента в массиве структур
/// @param arr - созданные массив структур
/// @param titles - массив названий фильмов
/// @param names - массив имен режиссеров
/// @param years - массив годов выпуска
/// @param len_arr - длина массива
/// @return код ошибки
int create_arr_by_data(struct film_t **arr, char *titles[], char *names[], int years[], const size_t len_arr);






#endif
