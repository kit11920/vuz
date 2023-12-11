#ifndef EXP_TREE_H__
#define EXP_TREE_H__

#define LEN_NUM_ARR 9

#define PLUS_EXP '+'
#define MINUS_EXP '-'
#define MULT_EXP '*'

#define MAX_LEN_ID 50

typedef enum { EXP, NUM } type_data_t;

typedef struct st_data_exp data_exp_t;
struct st_data_exp
{
    type_data_t type;
    union st_data_t
    {
        int num;
        char exp;
    } data;
};

typedef struct st_exp_tree_t enode_t;
struct st_exp_tree_t
{
    data_exp_t data_exp;
    char id[MAX_LEN_ID];

    enode_t *left;
    enode_t *right;
};


/// @brief Создает массив проходясь инфиксно по дереву LNR
/// @param root Создает массив данных из дерева
/// @param arr массив данных
/// @param i индекс последнего не заполненного элемента (Размер массива)
void make_arr_base_exp_tree(enode_t *root, int arr[], size_t *i);

/// @brief Выводит массив
/// @param arr массив
/// @param len_arr его длина
void print_arr(int arr[], size_t len_arr);

/// @brief Подчитывет узлы в дереве выражения
/// @param root дерево выражения
/// @return код ошибки
int make_counted_exp_tree(enode_t **root);

/// @brief Выделяет память под узел дерева
/// @param node - указатель на указатель на узел
/// @return код ошибки (ERR_MEM)
int make_enode_exp_tree(enode_t **node);

/// @brief Добавляет новый узел списка и выделяет под него память
/// @param node - указатель на указатель на добавляемый узел
/// @param type - тип узла
/// @param data - данные в узле
/// @param id - id данных
/// @return код ошибки  (ERR_MEM)
int add_enode_tree(enode_t **node, type_data_t type, int data, char *id);

/// @brief Освобождает память из под дерева
/// @param root - указатель на указатель на узел
void free_exp_tree(enode_t **root);

/// @brief Применяет функцию-действие к каждому элементу списка в префиксном порядке
/// @param root - корень дерева
/// @param action - функция-действие
/// @param param - параметр функции-действия
void each_nlr_exp_tree(enode_t *root, void (*action)(enode_t *root, void *param), void *param);

/// @brief Применяет функцию-действие к каждому элементу списка в инфиксном порядке
/// @param root - корень дерева
/// @param action - функция-действие
/// @param param - параметр функции-действия
void each_lnr_exp_tree(enode_t *root, void (*action)(enode_t *root, void *param), void *param);

/// @brief Применяет функцию-действие к каждому элементу списка в постфиксном порядке
/// @param root - корень дерева
/// @param action - функция-действие
/// @param param - параметр функции-действия
void each_lrn_exp_tree(enode_t *root, void (*action)(enode_t *root, void *param), void *param);

/// @brief Функция действие которая печатает узел списка
/// @param root - узел дерева
/// @param param - параметр функции-действия
void print_exp_node(enode_t *root, void *param);

/// @brief Печатает дерево в префиксном порядке
/// @param root - корень дерева
void nlr_print_exp_tree(enode_t *root);

/// @brief Вычисляет значение выражения
/// @param root - корень дерева
/// @return Результат вычисления
int calculate_tree(enode_t *root);

/// @brief Выводит отношение медлу узлами в формате dot в файл
/// @param f - файловая переменная
/// @param parant - узел-родитель
/// @param child - узел-ребенок
void print_parant_child(FILE *f, enode_t *parant, enode_t *child);

/// @brief Функция-действие выводит дерево в файл в формате dot
/// @param root - корень дерева
/// @param param - файловая переменная
void exp_to_dot(enode_t *root, void *param);

/// @brief Выводит дерево в файл в формате dot
/// @param filename - название файла
/// @param root - корень дерева
/// @return код ошибки (ERR_FILE)
int export_exp_to_dot(char *filename, enode_t *root);

/// @brief Производит работу с деревом выражением
/// @return код ошибки
int act_exp_tree(void);

/// @brief Создает дерево вырадение на основе массива чисел
/// @param root - корень дерева
/// @param arr - массив чисел
/// @return код ошибки
int make_exp_tree(enode_t **root, int *arr);




#endif


