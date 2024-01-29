#ifndef NODE_LIST_H__
#define NODE_LIST_H__

#define PART_LEN 4

typedef struct st_node_t node_t;

struct st_node_t
{
    char data[PART_LEN];

    node_t *next;
};

/// @brief Создает узел списка и выделяет под него память
/// @param [in] data - данные которые заносятся в узел
/// @return указатель на созданный узел
node_t *create_node(char *data);

/// @brief Освобождает память из-под узла списка
/// @param [in] node - указатель на узел списка
void free_node(node_t *node);

/// @brief Выводит содержимое узла
/// @param [in] node - указатель на узел списка
void print_node(node_t *node);





#endif
