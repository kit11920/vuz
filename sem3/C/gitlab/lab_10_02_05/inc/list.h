#ifndef LIST_H__
#define LIST_H__

#include <stdlib.h>
#include "node_list.h"

/// @brief Добавляет узел в конец списка
/// @param [in] head - указатель на голову списка
/// @param [in] node - указатель на узел
/// @return новая голова списка
node_t *add_tail_list(node_t *head, node_t *node);

/// @brief Освобождает память из под списка и обнуляет указатель на голову
/// @param [in] head - указатель на голову списка
void free_list(node_t **head);

/// @brief Выводит содержимое списка
/// @param [in] head - указатель на голову списка
void print_list(node_t *head);






#endif
