#ifndef DATA_H__
#define DATA_H__

#include <stdbool.h>
#include <stdio.h>

#include "node_list.h"
#include "errs.h"

typedef struct struct_country country_t;

struct struct_country
{
    char *name;     // Название страны
    char *capital;  // Название столица 
    bool visa;      // нужна ли виза
    int time;       // время полета до страны из России
    int cost_min;   // минимальная стоимость отдыха в стране
};


/// @brief Вводит строку
/// Если функция завершилась с ошибкой, память из под нее очищать не надо
/// @param [in out] f - файловая переменная
/// @param [out] str - строка (указатель)
/// @return код ошибки
int input_str(FILE *f, char **str);

// /// @brief Ввводит данные о стране (элементы структуры)
// /// И выделяет под элементы память
// /// Если функция завершилась с ошибкой, память из под нее очищать не надо
// /// @param [in out] f - файловая переменная 
// /// @param [out] country - структура страны (указатель)
// /// @return код ошибки
// int input_country(FILE *f, country_t *country);

// /// @brief Выделяет память под структуру страны (но не под ее элементы)
// /// @param [in] country - структура страны (указатель на указатель)
// /// @return код ошибки
// int alloc_country(country_t **country);

/// @brief Выделяет память под структуру страны и заполняет ее, выделяя память под ее элементы
/// Если функция завершилась с ошибкой, память из под нее очищать не надо
/// @param [in out] f - файловая переменная 
/// @param [out] country - структура страны (указатель на указатель)
/// @return код ошибки
int create_country(FILE *f, country_t **country);

/// @brief Выводит данные о стране
/// @param [in out] f - файловая переменная 
/// @param [in] country - структура страны (указатель) 
void print_country(FILE *f, void *country);

/// @brief Освобождает память из под структуры страны
/// @param [in] country - структура страны (указатель) 
void free_country(void *country);

/// @brief Ищет в списке элемент по названию страны
/// @param [in] name - название страны
/// @param [in] head - указатель на голову списка
/// @param [out] node - указатель на указатель на найденный элемент
/// @return код ошибки
int find_by_country_name(char *name, node_t *head, node_t **node);

/// @brief Сравнивает названия стран, записанные в узлах
/// @param [in] l - указатель на узел списка
/// @param [in] r - указатель на узел списка
/// @return такой же как у strcmp
int cmp_name(const void *l, const void *r);

/// @brief Считывает список из файла 
/// @param [in] filename - название файла
/// @param [out] head - указатель на указатель на голову списка
/// @return код ошибки
int read_file_list(char *filename, node_t **head);


#endif
