#ifndef NODE_LIST_H__
#define NODE_LIST_H__

#include <stdio.h>

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

typedef int (*cmp_t)(const void*, const void*);

/// @brief Создает узел и выделяет под него память
/// @param [in] data - данные которые будут в узле
/// @return Указатель на новый узел
node_t *create_node(void *data);

/// @brief Освобождает память из под узла
/// @param [in] node - узел 
void free_node(node_t *node);

/// @brief Выводит данные в узле
/// @param [in out] f - файловая переменная 
/// @param [in] node - узел  
/// @param [in] print_data - функция печати данных
void print_node(FILE *f, const node_t *node, void (*print_data)(FILE *, void *));

/// @brief Вставляет элемент перед указанным элементом списка 
/// (в качестве параметров указываются адреса обоих элементов списка)
/// Предполагается: что список не пустой и что в списке есть элемент before
/// @param [in out] head - указатель на голову списка
/// @param [in] elem - вставляемый элемент
/// @param [in] before - элемент перед которым вставляется elem
void insert(node_t **head, node_t *elem, node_t *before);

/// @brief Функция поиска элемента в списке
/// @param [in] head - указатель на голову списка
/// @param [in] data - данные по которым происходит поиск 
/// @param [in] cmp - функция сравнения элементов  
/// @return Указатель на искомый элемент
node_t *find(node_t *head, const void *data, cmp_t cmp);

#endif
