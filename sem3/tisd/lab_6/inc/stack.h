#ifndef STACK_H__
#define STACK_H__

#include <stdlib.h>
#include <stdio.h>

#include "exp_tree.h"
#include "errs.h"

typedef struct st_list_node_t lnode_t;

struct st_list_node_t
{
    type_data_t type;
    union st_data_t
    {
        int num;
        char exp;
    } data;

    lnode_t *next;
};

/// @brief Создает узел списка
/// @param node указатель на указатель на созданный узел списка
/// @param type тип данных в узле
/// @param data данные в узле
/// @return код ошибки
int create_stnode(lnode_t **node, type_data_t type, int data);

/// @brief Добавляет узел в конец списка
/// @param head указатель на указатель на голову списка
/// @param type тип данных в узле
/// @param data данные в узле
/// @return код ошибки
int push_end_lnode_list(lnode_t **head, type_data_t type, int data);

/// @brief Добавляет узел в начало списка
/// @param head указатель на указатель на голову списка
/// @param type тип данных в узле
/// @param data данные в узле
/// @return код ошибки
int push_beg_lnode_list(lnode_t **head, type_data_t type, int data);

/// @brief Удаляет элемент из головы списка и возвращает его
/// @param head указатель на указатель на голову списка
/// @return удаленный элемент
lnode_t *pop_list(lnode_t **head);

/// @brief Очищает память из-под списка
/// @param head указатель на указатель на голову списка
void free_list(lnode_t **head);

/// @brief 
/// @param head 
void print_list(lnode_t *head);

/// @brief Функция-действие добавляет узел дерева в список
/// @param root узел дерева
/// @param param указатель на указатель на голову списка
void exp_tree_to_list_action(enode_t *root, void *param);

/// @brief создает список выражения на основе дерева в постфиксной форме
/// @param root указатель на корень дерева
/// @param head указатель на указатель на голову списка
/// @return код ошибки
int exp_tree_to_list(enode_t *root, lnode_t **head);

/// @brief Вычисляет выражение используя стек, записанное в списке
/// @param exp указатель на список выражения
/// @return код ошибки
int calculate_stack(lnode_t *exp);






















#endif

