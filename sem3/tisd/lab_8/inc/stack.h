#ifndef STACK_H__
#define STACK_H__

#include <stdlib.h>

typedef struct st_stack stack_t;
struct st_stack
{
    int *arr;
    int *ps;
    int *aub;
};

/// @brief Создает стек и выделяет под него память
/// @param len_stack - размер стека
/// @return стек
stack_t *create_stack(size_t len_stack);

/// @brief Добавляет элемент в статический стек
/// @param stack - структура стека (указатель)
/// @param elem - новый элемент
void push_stack(stack_t *stack, int elem);

/// @brief Удаляет элемент из статического стека
/// @param stack - структура стека (указатель)
/// @return удаленный элемент
int pop_stack(stack_t *stack);

/// @brief Освобождает память из под структуры стека
/// @param stack - структура стека (указатель на указатель)
void free_stack(stack_t **stack);

/// @brief Определяет является ли стек пусты
/// @param stack - структура стека (указатель)
/// @return да/нет
bool is_empty_stack(stack_t *stack);

void print_stack(stack_t *stack);


























#endif



