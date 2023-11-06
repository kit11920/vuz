#ifndef WORK_STACK_H__
#define WORK_STACK_H__

#include "static_stack.h"
#include "list_stack.h"

/// @brief Вводит действие со стеком
/// @param act - перемання определяющая работу со стеком списком или массивом
/// @return код действия
int choose_work_stack(int act);

/// @brief Осуществляет работу со стеком в виде статического массива
/// @param stack - структура стека (указатель)
void working_static_stack(struct static_stack *stack);

/// @brief Осуществляет работу со стеком в виде односвязного линейсного списка
/// @param stack - структура стека (указатель)
/// @param len_list_stack - длина стека
/// @param arr - структура массива свободных адресов (указатель)
void working_list_stack(struct list_stack **stack, size_t *len_list_stack, struct free_adresses *arr);


#endif
