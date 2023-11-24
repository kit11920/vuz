#ifndef TREE_H__
#define TREE_H__

// бинарное дерево поиска без повторений
// и дерево выражения
typedef struct st_tree_t node_t;

struct st_tree_t
{
    char *data;

    node_t *left;
    node_t *right;
};


int add_node_bin_search_tree(node_t **root, char *data);

void print_node(node_t *root, void *param);

void print_tree(node_t *root);

void free_tree(node_t *root);

/// @brief 
/// @param root 
/// @param data 
/// @param parant 
/// @return указатель на найденный узел
node_t *find_node_tree(node_t *root, char *data, node_t **parant);

/// @brief Удаляет узел из дерева с соответствующим data
/// @param root 
/// @param data 
/// @return указатель на узел который должен встать на место удаленного
node_t *del_node_tree(node_t *root, char *data);

node_t *find_min_tree(node_t *root, node_t **parant);

void to_dot(node_t *root, void *param);

void each_nlr_tree(node_t *root, void (*action)(node_t *root, void *param), void *param);

int export_to_dot(char *filename, node_t *root);














#endif
