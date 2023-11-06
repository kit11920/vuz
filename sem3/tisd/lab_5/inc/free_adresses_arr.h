#ifndef FREE_ADRESSES_ARR_H__
#define FREE_ADRESSES_ARR_H__


#define INCREASE_SIZE_FREE_ADRESSES_ARR 100
#define MAX_PRINT_ARR 10

typedef struct struct_free_adresses
{
    void **a;
    size_t count_elems;
    size_t len_a;
} free_adresses_t;

/// @brief Выделяет память под массив свободных адресов и инициализирует его размером в 1 элемент
/// @param arr - структура массива свободных адресов (указатель)
/// @return код ошибки
int init_free_adresses_arr(free_adresses_t *arr);

/// @brief Перевыделяет память под массив свободных адресов (увеличивает его размер в 2 раза)
/// @param arr - структура массива свободных адресов (указатель)
/// @return код ошибки
int resize_free_adresses_arr(free_adresses_t *arr);

/// @brief Добавляет элемент в массив свободных адресов и увлеичивает его если надо
/// @param arr - структура массива свободных адресов (указатель)
/// @param p - укзатель (новый элемент)
/// @return код ошибки
int add_elem_free_adresses_arr(free_adresses_t *arr, void *p);

/// @brief Удаляет адресс из массива если он там есть
/// @param arr - структура массива свободных адресов (указатель)
/// @param p - укзатель (удаляемый элемент)
void del_elem_free_adresses_arr(free_adresses_t *arr, void *p);

/// @brief Выводит массив свободных адресов
/// @param arr - структура массива свободных адресов (указатель)
void print_free_adresses_arr(free_adresses_t *arr);



#endif
