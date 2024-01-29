#ifndef FILM_H__
#define FILM_H__

#include <stdio.h>

// #define TITLE_MAX_LEN  25
// #define NAME_MAX_LEN 25

#define TITLE "title"
#define NAME "name"
#define YEAR "year"

struct film_t
{
    char *title;
    char *name;
    int year;
};

typedef int (*uni_cmp_t)(const struct film_t *l, const struct film_t *r);

/// @brief Инициализирует структуру нулями
/// @param [out] film - структура фильма (указатель) 
void film_init_null(struct film_t *film);

/// @brief Инициализирует строки новым значением
/// Освобождает строку из под старого значения и выделяет память под новое
/// @param dst - указатель на строку, которой присваиваем значение
/// @param src - строки значение которой присваиваем
/// @return код ошибки
int init_str(char **dst, char *src);

/// @brief Инициализирует поля структуры фильма, данными значениями
/// @param [out] film - структура фильма (указатель)
/// @param [in] title - название фильма 
/// @param [in] name - имя режиссера
/// @param [in] year - год создания
/// @return код ошибки
int film_init_content(struct film_t *film, char *title, char *name, int year);

/// @brief Копирует структуры
/// @param [out] dst - структура в которую копируют (указатель)
/// @param [in] src - структура из которой копируют (указатель)
/// @return код ошибки
int film_copy(struct film_t *dst, struct film_t *src);

/// @brief Освобождает поля структуры фильма
/// @param [in] film - структура фильма (указатель)
void free_film(struct film_t *film);

/// @brief Обрабатывает ввод динамической строки
/// @param [in] f - указатель на файл 
/// @param [out] str - строка в которую запишем введенные данные 
/// @return код ошибки 
int input_str(FILE *f, char **str);

/// @brief Считывает структуру фильма из файла
/// @param [in] f - указатель на файл
/// @param [out] pfilm - указатель на фильм 
/// @return код ошибки
int film_read(FILE *f, struct film_t *pfilm);

/// @brief Выводит данные о фильме
/// @param [in] pfilm - указатель на фильм 
void film_print(const struct film_t *pfilm);

/// @brief Сравнивает фильмы по названию
/// @param [in] pl - указатель на фильм 1 
/// @param [in] pr - указатель на фильм 2 
/// @return как у функции strcmp
int film_cmp_by_title(const struct film_t *pl, const struct film_t *pr);

/// @brief Сравнивает фильмы по мени режиссера
/// @param [in] pl - указатель на фильм 1 
/// @param [in] pr - указатель на фильм 2 
/// @return как у функции strcmp
int film_cmp_by_name(const struct film_t *pl, const struct film_t *pr);

/// @brief Сравнивает фильмы по году выхода
/// @param [in] pl - указатель на фильм 1 
/// @param [in] pr - указатель на фильм 2 
/// @return как у функции strcmp
int film_cmp_by_year(const struct film_t *pl, const struct film_t *pr);


#endif
