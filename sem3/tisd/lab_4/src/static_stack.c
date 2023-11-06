#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "errs.h"
#include "static_stack.h"

void init_static_stack(struct static_stack *stack)
{
    stack->ps = NULL;
    stack->aub = stack->a + MAX_LEN_STATICK_STACK - 1;
}

void add_elem_static_stack(struct static_stack *stack, void *p)
{
    assert(stack->ps != stack->aub);

    if (stack->ps == NULL)
        stack->ps = stack->a;
    else
        stack->ps++;
    *(stack->ps) = p;
}

int act_add_elem_static_stack(struct static_stack *stack)
{
    void *tmp;

    if (stack->ps == stack->aub)
        return ERR_RANGE_LONG;
    
    if (stack->ps == NULL)
    {
        int a;
        printf("Введите новый элемент стека (адресс, например %p ): ", (void *) &a);
    }
    else
        printf("Введите новый элемент стека (адресс, например %p ): ", (void *) stack->ps);
    
    if (scanf("%p", &tmp) != 1)
    {
        char c = getchar();
        while (c != '\n')
            c = getchar();
        return ERR_IO;
    }

    add_elem_static_stack(stack, tmp);

    printf("Добавлен элемент %p\n", *(stack->ps));

    return OK;
}

void del_elem_static_stack(struct static_stack *stack)
{
    assert(stack->ps != NULL);

    if (stack->ps == stack->a)
        stack->ps = NULL;
    else
        stack->ps--;
}

int act_del_elem_static_stack(struct static_stack *stack)
{
    if (stack->ps == NULL)
        return ERR_RANGE_EMPTY;
    
    if (stack->ps == stack->a)
    {
        printf("Элемент %p был удален, теперь стек пуст\n", *(stack->ps));
        stack->ps = NULL;
    }
    else
    {
        printf("Элемент %p был удален, теперь верхний элемент стека: %p\n", *(stack->ps), *(stack->ps - 1));
        stack->ps--;
    }

    return OK;
}

void print_static_stack(struct static_stack *stack)
{
    printf("Стек в виде статического массива (Максималььная длина стека %zu): \n", stack->aub - stack->a + 1);
    if (stack->ps == NULL)
        printf("Стек пуст\n");
    else
    {
        for (void **pcur = stack->ps; pcur >= stack->a; pcur--)
            printf(" %p", *pcur);
        printf("\n");
    }
}


void clear_static_stack(struct static_stack *stack)
{
    while (stack->ps != NULL)
        act_del_elem_static_stack(stack);
    printf("Стек пуст\n");
}
