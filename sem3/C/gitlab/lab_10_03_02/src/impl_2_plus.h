#ifndef IMPL_2_PLUS_H__
#define IMPL_2_PLUS_H__

#include "associative_array.h"


typedef struct tree_node node_t;

struct tree_node
{
    const char *key;
    int num;

    node_t *left;
    node_t *right;
};

struct assoc_array_type
{
    node_t *root;
};


/// @brief Создает узел дерева и выделяет под него память
/// @param [in] key - ключ 
/// @param [in] num - значение 
/// @return указатель на новый узел дерева или NULL в случае ошибки выделения памяти
node_t *tree_node_create(const char *key, int num);

/// @brief Освобождает память из под узла дерева и обращает указатель в NULL;
/// @param [in out] node - указатель на указатель на освобождаемый узел 
void tree_node_free(node_t **node);

/// @brief Рекурсивно освобождает память из-под дерева
/// @param [in out] node - указатель на указатель на освобождаемый узел
void tree_destroy(node_t **node);

/// @brief Добавляет узел, под который уже выделена память в список
/// @param [in] root - корень дерева (указатель) 
/// @param [in] new_node - добавляемый узел
/// @return новый корень дерева (указатель) 
node_t *tree_add(node_t *root, node_t *new_node);

/// @brief Рекурсивно применяет функцию в каждому узлы списка
/// @param [in] node - указатель на узел дерева
/// @param [in] action - функция
/// @param [in] param до параметры функции
void tree_action(node_t *node, void (*action)(const char *key, int *num, void *param), void *param);

/// @brief Ищет элемент с соответствующим ключом
/// @param [in] root - корень дерева (указатель)
/// @param [in] key - ключ который ищем
/// @param [out] parant - указатель на указатель на родителя найденного элемента 
/// (если искомый элемент - корень parant == NULL)
/// @return указатель на найденный элемент
node_t *tree_find(node_t *root, const char *key, node_t **parant);

/// @brief Удаляет узел
/// @param [in] node - удаляемый узел
/// @return указатель на узел который должен встать на место удаляемого узла
node_t *tree_remove(node_t *node);

/// @brief Ищет минимальный элемент
/// @param [in] node - указатель на узел дерева
/// @param [out] parant - указатель на указатель на родителя найденного элемента 
/// (если искомый элемент - корень parant == NULL)
/// @return Указатель на узел минимального элемента
node_t *tree_find_min(node_t *node, node_t **parant);

/// @brief Ищет максимальный элемент
/// @param [in] node - указатель на узел дерева
/// @param [out] parant - указатель на указатель на родителя найденного элемента 
/// (если искомый элемент - корень parant == NULL)
/// @return Указатель на узел максимального элемента
node_t *tree_find_max(node_t *node, node_t **parant);



#endif

