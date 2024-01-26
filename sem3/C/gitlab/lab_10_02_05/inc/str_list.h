#ifndef STR_LIST_H__
#define STR_LIST_H__

#include <stdbool.h>
#include <stdlib.h>
#include "node_list.h"

/// @brief Вводит строку и вделяет под нее память
/// Если возвращается NULL то память освобождается автоматически
/// @return указатель на новую строку или NULL
char *input_dstr(void);

/// @brief Вводит строки в список
/// Если функция вернула код ошибки, то память освобождать не надо
/// @param [out] head - указатель на указатель на голову списка
/// @return код ошибки
int input_string_list(node_t **head);

/// @brief Преобразовывает строку в список
/// @param [in] head - указатель на голову списка-строки
/// @param [in] str - строка
/// @return код ошибки
int string_to_list(node_t **head, char *str);

/// @brief Сравнивает является ли начало строки head (начиная с индекса ind) строкой str
/// head - указатель на голову с которой надо смотреть, а не на полную оригинальную строки
/// ind < PART_LEN
/// @param [in] head - указатель на голову списка-строки начало которой сравниваем
/// @param [in] str - указатель на голову списка-строки которую ищем в head
/// @param [in] ind - индекс начиная с которого надо смотреть строку head
/// @return true - если совпадают false - если нет
bool strcmp_ind(node_t *head, node_t *str, size_t ind);

/// @brief Ищет индекс подстроки str в строке head
/// @param [in] head - указатель на голову списка-строки в которой ищем
/// @param [in] str - указатель на голову списка-подстроки 
/// @return индекс подстроки или -1,если такой подстроки нет
int search_string(node_t *head, node_t *str);

/// @brief Удаляет символ из строки-списка со смещением влево
/// При необходимости освобождает память из-под освободившегося узла
/// @param [in out] head - указатель на голову списка
/// @param [in] ind - индекс удаляемого символа
void del_char(node_t *head, size_t ind);

/// @brief Удаляет двойные пробелы в строке
/// @param [in out] head - указатель на голову списка 
void del_2spaces(node_t *head);

/// @brief Склеивает 2 списка-строки со смещением строки 2 слево в строке 1
/// list1 + list2
/// @param [in out] list1 - указатель на строку к которой приклеивают с конца
/// @param [in out] list2  - указатель на строку которую приклеивают в конец
void cat_str_list(node_t *list1, node_t *list2);

























#endif

