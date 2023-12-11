#ifndef ARR_STACK_H__
#define ARR_STACK_H__

#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#define MAX_LEN_STATICK_STACK 17

struct static_stack
{
    data_exp_t a[MAX_LEN_STATICK_STACK];
    data_exp_t *ps; // pointer stack
    data_exp_t *aub; // adress up bond
};

/// @brief Инициализирует стек как пустой
/// @param stack - структура стека (указатель)
void init_static_stack(struct static_stack *stack);

/// @brief Добавляет элемент в статический стек
/// @param stack - структура стека (указатель)
/// @param data данные
void push_static_stack(struct static_stack *stack, data_exp_t data);

/// @brief Удаляет элемент из статического стека
/// @param stack - структура стека (указатель)
data_exp_t pop_static_stack(struct static_stack *stack);

int calculate_arr_stack(lnode_t *exp);









#endif


