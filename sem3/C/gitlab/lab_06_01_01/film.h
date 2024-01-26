#ifndef FILM_H__
#define FILM_H__

#include <stdio.h>

#define TITLE_MAX_LEN  25
#define NAME_MAX_LEN 25

#define TITLE "title"
#define NAME "name"
#define YEAR "year"

struct film_t
{
    char title[TITLE_MAX_LEN + 1];
    char name[NAME_MAX_LEN + 1];
    int year;
};

typedef int (*uni_cmp_t)(const struct film_t *l, const struct film_t *r);


/**
@brief Обрабатывает ввод строки
@param [in] f - указатель на файл
@param [out] str - строка в которую запишем введенные данные
@param [in] size_str - размер вводимой строик (если строка вводится с запасом)
@param [in] max_len_str - максимальная длина строки, которая положена
@return код ошибки
*/
int input_str(FILE *f, char *str, size_t size_str, int max_len_str);

/**
@brief Считывает структуру фильма из файла
@param [in] f - указатель на файл
@param [out] pfilm - указатель на фильм
@return код ошибки
*/
int film_read(FILE *f, struct film_t *pfilm);

/**
@brief Выводит данные о фильме
@param [in] pfilm - указатель на фильм
@return код ошибки
*/
int film_print(const struct film_t *pfilm);

/**
@brief Сравнивает фильмы по названию
@param [in] pl - указатель на фильм 1 
@param [in] pr - указатель на фильм 2
@return код ошибки
*/
int film_cmp_by_title(const struct film_t *pl, const struct film_t *pr);

/**
@brief Сравнивает фильмы по имени режиссера
@param [in] pl - указатель на фильм 1 
@param [in] pr - указатель на фильм 2
@return код ошибки
*/
int film_cmp_by_name(const struct film_t *pl, const struct film_t *pr);

/**
@brief Сравнивает фильмы по году выхода
@param [in] pl - указатель на фильм 1 
@param [in] pr - указатель на фильм 2
@return код ошибки
*/
int film_cmp_by_year(const struct film_t *pl, const struct film_t *pr);

// /**
// @brief Сравнивает фильмы по параметру param_sort
// Предполагается что параметр будет задан верно
// @param [in] param_sort - поле по которому сортируется массив
// @param [in] pl - указатель на фильм 1 
// @param [in] pr - указатель на фильм 2
// @return код ошибки
// */
// int film_cmp_by_param(const char param_sort[], const struct film_t *pl, const struct film_t *pr);

#endif
