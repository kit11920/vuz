#ifndef EFFICIENCY_STACK_TREE_H__
#define EFFICIENCY_STACK_TREE_H__

#include "efficiency.h"
#include "exp_tree.h"
#include "stack.h"
#include "errs.h"

#define MIN_COUNT_REAPET 200    // Минимальное кол-во повторов замера перед вычислением rse
#define COUNT_CALCS 10000         // Кол-во вычислений в одном замере

typedef unsigned long long (*calc_measure_time_t)(void *);

/// @brief Замеряет время работы цикла for COUNT_CALCS раз
/// @param exp NULL
/// @return время
unsigned long long measure_time_for(void *exp);

/// @brief Замеряет время работы вычисления выражения деревом COUNT_CALCS раз
/// @param exp дерево
/// @return время
unsigned long long measure_time_tree(void *exp);

/// @brief Замеряет время работы вычисления выражения стеком COUNT_CALCS раз
/// @param exp спиок в котором записано выражения
/// @return время
unsigned long long measure_time_stack(void *exp);

/// @brief Уточняет время замера до rse < 5%
/// @param measure - функция замера временеи
/// @param exp - параметр функции замера в времени
/// @param t - массив замеров времени
/// @param len_t - длина массива t
/// @param time - время замера, результирующее
/// @return код ошибки
int gettime_stack_tree(calc_measure_time_t measure, void *exp, unsigned long long *t, size_t len_t, long long *time);

/// @brief Выводит таблицу сравнения времени вычисления выражения стеком и деревом
/// @param tree дерево
/// @param stack стек
/// @return код ошибки
int make_compare_table_stack_tree(enode_t *tree, lnode_t *stack);








#endif


