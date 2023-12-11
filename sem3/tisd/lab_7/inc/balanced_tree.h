#ifndef BALANCED_TREE_H__
#define BALANCED_TREE_H__

#include <stdlib.h>

#include "exp_tree.h"
#include "tree.h"

#define LEN_ARR_TREE 17

typedef struct balance_tree_struct bnode_t;

struct balance_tree_struct
{
    int data;
    int height;

    bnode_t *left;
    bnode_t *right;
};



/// @brief Заполняет сбалансированное дерево по данным из массива
/// @param root сбалансированное дерево
/// @param arr массив данных
/// @param len_arr длина массива
/// @return код ошибки
int fill_btree_based_data_arr(bnode_t **root, int *arr, size_t len_arr);

/// @brief Считает высоту узла
/// @param node сбалансированное дерево узел
/// @return высота
int height(bnode_t *node);

/// @brief Считает параметр балансироваки
/// @param node сбалансированное дерево узел
/// @return параметр балансироваки
int bfactor(bnode_t *node);

/// @brief Обноляет высоту дерева
/// @param node сбалансированное дерево узел
void update_height(bnode_t *node);

/// @brief Поворот дерева по часовой стрелке
/// @param root сбалансированное дерево
/// @return измененное дерево
bnode_t *rotate_right(bnode_t *root);

/// @brief Поворот дерева против часовой стрелке
/// @param root сбалансированное дерево
/// @return измененное дерево
bnode_t *rotate_left(bnode_t *root);

/// @brief Балансирует дерево
/// @param root сбалансированное дерево
/// @return измененное дерево
bnode_t *balance_btree(bnode_t *root);

/// @brief Выделяет память под новый узел
/// @param data данные в узле
/// @return новый узел
bnode_t *new_bnode(int data);

/// @brief Добавляет узел в сбалансированное дерево
/// @param root сбалансированное дерево
/// @param data данные узла
/// @return голова нового дерева
bnode_t *add_btree(bnode_t *root, int data);

/// @brief Ищет узел в сбалансированное дерево
/// @param root сбалансированное дерево
/// @param data искомые данные
/// @param parant родитель найденного узла, если найденные узел горень то NULL
/// @return найденные узел
bnode_t *find_btree(bnode_t *root, int data, bnode_t **parant);

/// @brief Освобождает память из под дерева
/// @param root - указатель на корень дерева
void free_btree(bnode_t **root);

void print_bnode(bnode_t *root, void *param);

void print_btree(bnode_t *root);

/// @brief Функция-действие выводит в файл в формате dot данные об узле
/// @param root - указатель на узел
/// @param param - файловая переменная
void to_dot_btree(bnode_t *root, void *param);

/// @brief Применяет ко всем узлам дерева действие в порядке сверху-вниз (префиксном)
/// @param root - указатель на корень дерева
/// @param action - указатель на функцию-действие
/// @param param - параметр функции-действия
void each_nlr_btree(bnode_t *root, void (*action)(bnode_t *root, void *param), void *param);

/// @brief Записывает в файл дерево в формате dot
/// @param filename - имя файла
/// @param root - указатель на корень дерева
/// @return код ошибки (ERR_FILE)
int export_to_dot_btree(char *filename, bnode_t *root);

/// @brief Считает среднее кол-во сравнений в сбалансированном дереве
/// @param root сбалансированное дерево
/// @return ср кол-во сравнения
double mid_cmp_btree(bnode_t *root);

/// @brief Считает кол-во узлов в дереве
/// @param root сбалансированное дерево
/// @param param кол-во узлов
void act_count_elems_btree(bnode_t *root, void *param);

/// @brief Считает кол-во узлов в дереве
/// @param root сбалансированное дерево
/// @return кол-во узлов
size_t count_elems_btree(bnode_t *root);

/// @brief Считает кол-во сравнений в дереве
/// @param root сбалансированное дерево
/// @param height_now - уровень 
/// @return кол-во сравнений в дереве
size_t count_comparison_btree(bnode_t *root, size_t height_now);

/// @brief Считает высоту дерева
/// @param root сбалансированное дерево
/// @return высота
int max_height_btree(bnode_t *root);

/// @brief Считает размер сбалансированного дерева в байтах
/// @param root сбалансированное дерево
/// @return байт
size_t mem_bytes_btree(bnode_t *root);






















#endif


