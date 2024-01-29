#ifndef FILM_ARRAY_H__
#define FILM_ARRAY_H__

#include <stdio.h>
#include "film.h"

// #define MAX_LEN_ARRAY 15


/// @brief Считает кол-во структур в файле
/// @param [in out] f - указатель на файловую переменную
/// @param [out] count - указатель на кол-во элементов в файле
/// @return код ошибки
int count_elems_farr(FILE *f, size_t *count);

/// @brief Добавляет элемент в массив упорядоченный по параметру заложенному в функцию сравнения
/// @param [in] farr - массив структур
/// @param [in] ind - индекс добавляемого элемента (кол-во элементо в массиве сейчас)
/// @param [in] film добавляемый элемент, структура фильма 
/// @param [in] cmp - функция сравнения
void uni_farr_insert_el(struct film_t *farr, size_t ind, struct film_t *film, uni_cmp_t cmp);

/// @brief Освобождает память из под массива структур
/// @param [in] farr - массив структур 
/// @param [in] len_arr - длина массива
void free_farr(struct film_t *farr, size_t len_arr);

/// @brief Считывает информацию о фильмах в массив 
/// таким образом чтобы он сразу был упорядочен по указанному полю
/// Выделяет память под массив 
/// Считает кол-во структур в файле
/// @param [in out] f - указатель на файловую переменную
/// @param [out] farr - массив структур (указатель)
/// @param [out] len_arr - длина массива (указатель)
/// @param [in] cmp - функция сравнения 
/// @return код ошибки
int uni_farr_read_sorted(FILE *f, struct film_t **farr, size_t *len_arr, uni_cmp_t cmp);

/// @brief Выводит массив фильмов
/// @param [in] pfilms - указатель массив фильмов 
/// @param [in] len_arr - длина массива
void farr_print(const struct film_t *pfilms, const size_t len_arr);

/// @brief Универсальный поиск фильма 
/// @param [in] pfilms - указатель на массив фильмов 
/// @param [in] len_arr - длина массива (реальная) 
/// @param [in] film - структура с заданным параметром поиска
/// @param [in] cmp - функция сравнения по определенному параметру
/// @return индекс искомого фильма с массиве (если такого элемента нет то возвращает -1)
int uni_find_film_by_key(const struct film_t *pfilms, const size_t len_arr, struct film_t *film, uni_cmp_t cmp);


#endif
