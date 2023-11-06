#ifndef LIST_STACK_H__
#define LIST_STACK_H__

#include <stdlib.h>

#define MAX_LEN_LIST_STACK 50000

struct list_stack
{
    struct list_stack *value; // адрес самой структуры
    struct list_stack *next;
};

struct free_adresses
{
    void **a;
    size_t count_elems;
    size_t len_a;
};

/// @brief Добавляет элемент в списковый стек
/// @param stack - структура стека (указатель на указатель на голову списка)
/// @return код ошибки
int add_elem_list_stack(struct list_stack **stack);

/// @brief Добавляет элемент в списковый стек и 
/// удаляет адресс из массива свободных адресов если он был использова
/// @param stack - структура стека (указатель на указатель на голову списка)
/// @param len_list_stack - длина стека
/// @param arr - структура массива свободных адресов (указатель)
/// @return код ошибки
int act_add_elem_list_stack(struct list_stack **stack, size_t *len_list_stack, struct free_adresses *arr);

/// @brief Удаляет элемент из спискового стек
/// @param stack - структура стека (указатель на указатель на голову списка)
/// @param prev - указатель на удаленную структуру стека
void del_elem_list_stack(struct list_stack **stack, struct list_stack *prev);

/// @brief Удаляет элемент из спискового стек и заностит освобожденный адрес с массив свободных адресов
/// @param stack - структура стека (указатель на указатель на голову списка)
/// @param len_list_stack - длина стека
/// @param arr - структура массива свободных адресов (указатель)
/// @return код ошибки
int act_del_elem_list_stack(struct list_stack **stack, size_t *len_list_stack, struct free_adresses *arr);

/// @brief Выводит состояние спискового стека
/// @param stack - структура стека (указатель)
void print_list_stack(struct list_stack *stack);

/// @brief Очищает стек
/// @param stack - структура стека (указатель на указатель на голову списка)
void just_clear_list_stack(struct list_stack **stack);

/// @brief Очищает стек и заносит удаленные элементы в массив свободных адресов
/// @param stack - структура стека (указатель на указатель на голову списка)
/// @param len_list_stack - длина стека
/// @param arr - структура массива свободных адресов (указатель)
void clear_list_stack(struct list_stack **stack, size_t *len_list_stack, struct free_adresses *arr);

/// @brief Выделяет память под массив свободных адресов и инициализирует его размером в 1 элемент
/// @param arr - структура массива свободных адресов (указатель)
/// @return код ошибки
int init_free_adresses_arr(struct free_adresses *arr);

/// @brief Перевыделяет память под массив свободных адресов (увеличивает его размер в 2 раза)
/// @param arr - структура массива свободных адресов (указатель)
/// @return код ошибки
int resize_free_adresses_arr(struct free_adresses *arr);

/// @brief Добавляет элемент в массив свободных адресов и увлеичивает его если надо
/// @param arr - структура массива свободных адресов (указатель)
/// @param p - укзатель (новый элемент)
/// @return код ошибки
int add_elem_free_adresses_arr(struct free_adresses *arr, void *p);


void del_elem_free_adresses_arr(struct free_adresses *arr, void *p);

/// @brief Выводит массив свободных адресов
/// @param arr - структура массива свободных адресов (указатель)
void print_free_adresses_arr(struct free_adresses *arr);






#endif
