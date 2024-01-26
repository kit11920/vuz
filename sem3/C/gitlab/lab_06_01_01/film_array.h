#ifndef FILM_ARRAY_H__
#define FILM_ARRAY_H__

#include <stdio.h>
#include "film.h"

#define MAX_LEN_ARRAY 15


// /**
// @brief Добавляет элемент в упорядоченный по параметру param_sort массив
// и увеличивает длину фактическую длину массива (len_arr_now)
// @param [out] pfilms - указатель массив фильмов
// @param [in] max_len_arr - максимальная длина массива
// @param [in out] len_arr_now - указатель на длину массива реальную
// @param [in] film добавляемый элемент, структура фильма
// @param [in] param_sort - поле по которому сортируется массив
// @return код ошибки
// */
// int farr_input_el(struct film_t *pfilms, const size_t max_len_arr, size_t *len_arr_now, struct film_t *film, const char *param_sort);


// /**
// @brief Считывает информацию о фильмах в массив 
// таким образом чтобы он сразу был упорядочен по указанному полю
// @param [in] f - указатель на файловую переменную
// @param [out] pfilms - указатель массив фильмов
// @param [in] max_len_arr - vаксимальная длина массива
// @param [out] plen_arr - указатель на длину массива (реальную)
// @param [in] param_sort - поле по которому сортируется массив
// @return код ошибки
// */
// int farr_read_sorted(FILE *f, struct film_t *pfilms, const size_t max_len_arr, size_t *plen_arr, const char *param_sort);


/**
@brief Выводит массив фильмов
@param [out] pfilms - указатель массив фильмов
@param [out] len_arr - длина массива (реальная)
@return код ошибки
*/
int farr_print(const struct film_t *pfilms, const size_t len_arr);

// /**
// @brief Находит фильм с названием key левым бинарным поиском
// (если в массиве будут элементы с одинаковым ключем будет выбран элемент с минимальным индексом)
// Гарантируется что возвращаемый индекс будет в проделах [-1:len_arr]
// @param [in] pfilms - указатель на массив фильмов
// @param [in] len_arr - длина массива (реальная)
// @param [in] key - ключ
// @return индекс найденного фильма (если фильм не найден возвращает -1)
// */
// int find_film_by_key_title(const struct film_t *pfilms, const size_t len_arr, const char *key);

// /**
// @brief Находит фильм с именем режиссера key левым бинарным поиском
// (если в массиве будут элементы с одинаковым ключем будет выбран элемент с минимальным индексом)
// Гарантируется что возвращаемый индекс будет в проделах [-1:len_arr]
// @param [in] pfilms - указатель на массив фильмов
// @param [in] len_arr - длина массива (реальная)
// @param [in] key - ключ
// @return индекс найденного фильма (если фильм не найден возвращает -1)
// */
// int find_film_by_key_name(const struct film_t *pfilms, const size_t len_arr, const char *key);

// /**
// @brief Находит фильм выпущенный в году key левым бинарным поиском
// (если в массиве будут элементы с одинаковым ключем будет выбран элемент с минимальным индексом)
// Гарантируется что возвращаемый индекс будет в проделах [-1:len_arr]
// Предполагается что ключ будет верно заданным челым числом
// @param [in] pfilms - указатель на массив фильмов
// @param [in] len_arr - длина массива (реальная)
// @param [in] key - ключ
// @return индекс найденного фильма (если фильм не найден возвращает -1)
// */
// int find_film_by_key_year(const struct film_t *pfilms, const size_t len_arr, const int key);


/// @brief Универсальный поиск фильма 
/// @param [in] pfilms - указатель на массив фильмов 
/// @param [in] len_arr - длина массива (реальная) 
/// @param [in] film - структура с заданным параметром поиска
/// @param [in] cmp - функция сравнения по определенному параметру
/// @return 
int uni_find_film_by_key(const struct film_t *pfilms, const size_t len_arr, struct film_t *film, uni_cmp_t cmp);


/// @brief Добавляет элемент в упорядоченный по параметру заложенному в функцию сравнения
/// и увеличивает длину фактическую длину массива (len_arr_now)
/// @param [in] pfilms - указатель массив фильмов
/// @param [in] max_len_arr - vаксимальная длина массива
/// @param [in out] len_arr_now - указатель на длину массива реальную
/// @param [in] film добавляемый элемент, структура фильма 
/// @param [in] cmp - функция стравнения
/// @return 
int uni_farr_isert_el(struct film_t *pfilms, const size_t max_len_arr, size_t *len_arr_now, struct film_t *film, uni_cmp_t cmp);

/// @brief Считывает информацию о фильмах в массив 
/// таким образом чтобы он сразу был упорядочен по указанному полю
/// @param [in] f - указатель на файловую переменную
/// @param [in] pfilms - указатель массив фильмов
/// @param [in] max_len_arr - vаксимальная длина массива
/// @param [out] plen_arr - указатель на длину массива (реальную) 
/// @param in] cmp - функция стравнения 
/// @return 
int uni_farr_read_sorted(FILE *f, struct film_t *pfilms, const size_t max_len_arr, size_t *plen_arr, uni_cmp_t cmp);

#endif
