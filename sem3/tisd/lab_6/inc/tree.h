#ifndef TREE_H__
#define TREE_H__

// бинарное дерево поиска без повторений
// и дерево выражения
typedef struct st_tree_t node_t;

struct st_tree_t
{
    int data;

    node_t *left;
    node_t *right;
};

/// @brief Добавляет узел в бинарное дерево поиска
/// @param root - указатель на указатель на корень дерева 
/// @param data - данные нового узла
/// @return код ошибки (ERR_MEM, ERR_NODE_EXIST)
int add_node_bin_search_tree(node_t **root, int data);

/// @brief Функция-действие для вывод данных узла
/// @param root - указатель на корень дерева
/// @param param - строка формата вывод для printf
void print_node(node_t *root, void *param);

/// @brief Выводит дерево в префиксной форме
/// @param root - указатель на корень дерева
void print_tree(node_t *root);

/// @brief Освобождает память из под дерева
/// @param root - указатель на корень дерева
void free_tree(node_t **root);

/// @brief Ищет узел дерева по данным
/// @param root - указатель на корень дерева
/// @param data - данные по которым ищем
/// @param parant - указатель на указатель на родителя искомых данных
/// @return указатель на найденный узел
node_t *find_node_tree(node_t *root, int data, node_t **parant);

/// @brief Ищет минимальный узел
/// @param root - указатель на корень дерева
/// @param parant - указатель на указатель на родителя искомых данных
/// @return указатель на найденный узел
node_t *find_min_tree(node_t *root, node_t **parant);

/// @brief Функция-действие выводит в файл в формате dot данные об узле
/// @param root - указатель на узел
/// @param param - файловая переменная
void to_dot(node_t *root, void *param);

/// @brief Применяет ко всем узлам дерева действие в порядке сверху-вниз (префиксном)
/// @param root - указатель на корень дерева
/// @param action - указатель на функцию-действие
/// @param param - параметр функции-действия
void each_nlr_tree(node_t *root, void (*action)(node_t *root, void *param), void *param);

/// @brief Записывает в файл дерево в формате dot
/// @param filename - имя файла
/// @param root - указатель на корень дерева
/// @return код ошибки (ERR_FILE)
int export_to_dot(char *filename, node_t *root);

/// @brief Удаляет узел из дерева с соответствующим data
/// @param node - указатель на узел который надо удалить
/// @return указатель на узел который должен встать на место удаленного
node_t *del_node_tree(node_t *node);

/// @brief Удаляет узел из дерева с соответствующим data
/// @param root - указатель на указатель на корень дерева
/// @param data - даные в соответствие с которыми должен быть удален узел
/// @return OK - если узел найден и удале или ERR_NOT_FOUND
int del_node_by_data_tree(node_t **root, int data);













#endif
