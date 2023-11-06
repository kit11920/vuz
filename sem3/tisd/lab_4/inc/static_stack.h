#ifndef STATIC_STACK_H__
#define STATIC_STACK_H__


#define MAX_LEN_STATICK_STACK 50000

struct static_stack
{
    void *a[MAX_LEN_STATICK_STACK];
    void **ps; // pointer stack
    void **aub; // adress up bond
};


/// @brief Инициализирует стек как пустой
/// @param stack - структура стека (указатель)
void init_static_stack(struct static_stack *stack);

/// @brief Добавляет элемент в статический стек
/// @param stack - структура стека (указатель)
/// @param p - адресс который будет добвлен в стек
void add_elem_static_stack(struct static_stack *stack, void *p);

/// @brief Вводит адрес и добавляет его в статический стек
/// @param stack - структура стека (указатель)
/// @return код ошибки
int act_add_elem_static_stack(struct static_stack *stack);

/// @brief Удаляет элемент из статического стека
/// @param stack - структура стека (указатель)
void del_elem_static_stack(struct static_stack *stack);

/// @brief Удаляет элемент из статического стека и выводит информацию об этом
/// @param stack - структура стека (указатель)
/// @return код ошибки
int act_del_elem_static_stack(struct static_stack *stack);

/// @brief Выводит состояние статического стека
/// @param stack - структура стека (указатель)
void print_static_stack(struct static_stack *stack);

/// @brief Очищает стек
/// @param stack - структура стека (указатель)
void clear_static_stack(struct static_stack *stack);








#endif

