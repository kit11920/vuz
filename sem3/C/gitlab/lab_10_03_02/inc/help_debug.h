#ifndef HELP_DEBUG_H__
#define HELP_DEBUG_H__

#include "associative_array.h"
#include "impl_2_plus.h"

/// @brief Печатает ключ и номер
/// @param [in] key - ключ
/// @param [in] num - значение ключа
/// @param [in] param - строка-формата вывода
void action_print(const char *key, int *num, void *param);

/// @brief Применяет к каждому узлу действие
/// @param [in] node - корень дерева
/// @param [in] action - действие
/// @param [in] param - параметры функции действия
void tree_each(node_t *node, void (*action)(node_t *node, void *param), void *param);

/// @brief Выводит в файле соотношения узлов 
/// @param [in] node - узез дерева
/// @param [in] param - файловая переменная
void to_dot(node_t *node, void *param);

/// @brief Создает файл .gv с зависимостями между узлами дерева
/// @param [in] filename - название файла
/// @param [in] node - корень дерева
void export_to_dot(char *filename, node_t *node);





#endif

