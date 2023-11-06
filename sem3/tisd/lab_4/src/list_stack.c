#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "list_stack.h"
#include "errs.h"

#define BEG_SIZE_FREE_ADRESSES_ARR 100


int add_elem_list_stack(struct list_stack **stack)
{
    struct list_stack *tmp;
    tmp = malloc(sizeof(struct list_stack));
    if (tmp == NULL)
        return ERR_MEM;
    
    tmp->value = tmp;

    if (*stack == NULL)
        tmp->next = NULL;
    else
        tmp->next = *stack;
    *stack = tmp;

    return OK;
}

int act_add_elem_list_stack(struct list_stack **stack, size_t *len_list_stack, struct free_adresses *arr)
{
    if (*len_list_stack == MAX_LEN_LIST_STACK)
        return ERR_RANGE_LONG;

    int rc = add_elem_list_stack(stack);
    if (rc == OK)
    {
        printf("Добавлен элемент %p\n", (void *) (*stack)->value);
        del_elem_free_adresses_arr(arr, (*stack)->value);
        (*len_list_stack)++;
    }
    
    return rc;
}

void del_elem_list_stack(struct list_stack **stack, struct list_stack *prev)
{
    prev = *stack;
    *stack = prev->next;
    free(prev);
}

int act_del_elem_list_stack(struct list_stack **stack, size_t *len_list_stack, struct free_adresses *arr)
{
    if (*stack == NULL)
        return ERR_RANGE_EMPTY;

    struct list_stack *prev = *stack;
    *stack = prev->next;

    if (*stack == NULL)
        printf("Элемент %p был удален, теперь стек пуст\n", (void *) prev->value);
    else
        printf("Элемент %p был удален, теперь верхний элемент стека: %p\n", (void *) prev->value, (void *) (*stack)->value);
    (*len_list_stack)--;
    
    add_elem_free_adresses_arr(arr, prev);
    free(prev);

    return OK;
}


void print_list_stack(struct list_stack *stack)
{
    printf("Стек в виде списка: \n");
    if (stack == NULL)
    {
        printf("Стек пуст\n");
        return;
    }

    struct list_stack *stcur = stack;
    printf(" %p", (void *) stcur->value);
    while (stcur->next != NULL)
    {
        stcur = stcur->next;
        printf(" %p", (void *) stcur->value);
    }
    printf("\n");
}


void just_clear_list_stack(struct list_stack **stack)
{
    struct list_stack prev;
    while (*stack != NULL)
        del_elem_list_stack(stack, &prev);
}

void clear_list_stack(struct list_stack **stack, size_t *len_list_stack, struct free_adresses *arr)
{
    while (*stack != NULL)
        act_del_elem_list_stack(stack, len_list_stack, arr);
    printf("Стек пуст\n");
}


int init_free_adresses_arr(struct free_adresses *arr)
{
    struct free_adresses tmp;
    tmp.a = malloc(sizeof(void *) * BEG_SIZE_FREE_ADRESSES_ARR);
    if (tmp.a == NULL)
        return ERR_MEM;
    tmp.count_elems = 0;
    tmp.len_a = BEG_SIZE_FREE_ADRESSES_ARR;
    *arr = tmp;

    // printf("inited: %p - %p", (void *) arr->a, (void *) (arr->a + sizeof(void *) * BEG_SIZE_FREE_ADRESSES_ARR));

    return OK;
}

int resize_free_adresses_arr(struct free_adresses *arr)
{
    size_t bigger = 2;
    // printf("NEW_SIZE:           %zu", arr->len_a * bigger);
    void **tmp = realloc(arr->a, sizeof(void *) * arr->len_a * bigger);
    if (tmp == NULL)
        return ERR_MEM;
    else
    {
        // memmove(tmp, arr->a, sizeof(void *) * arr->count_elems);
        // printf("realloc\n");
        // for (size_t i = 0; i < arr->count_elems; i++)
        //     printf(" %p", tmp[i]);
        // printf("\n");
        printf("REALLOC:  %p\n", (void *) tmp);
        arr->a = tmp;
        arr->len_a *= bigger;
    }

    return OK;
}

int add_elem_free_adresses_arr(struct free_adresses *arr, void *p)
{
    assert(p != NULL);

    int rc = OK;
    // printf("COUNT:        %zu", arr->count_elems);
    if (arr->count_elems == arr->len_a)
        rc = resize_free_adresses_arr(arr);
    
    if (rc == OK)
    {
        size_t ind_last = arr->count_elems;
        arr->a[ind_last] = p;
        while (ind_last > 0 && arr->a[ind_last - 1] >= arr->a[ind_last])
        {
            if (arr->a[ind_last - 1] == arr->a[ind_last])
                return OK;
            void *tmp = arr->a[ind_last];
            arr->a[ind_last] = arr->a[ind_last - 1];
            arr->a[ind_last - 1] = tmp;
            ind_last--;
        }
        arr->count_elems++;
    }

    return rc;
}

void del_elem_free_adresses_arr(struct free_adresses *arr, void *p)
{
    assert(p != NULL);

    size_t ind = 0;
    while (ind < arr->count_elems && arr->a[ind] != p)
        ind++;
    
    if (ind != arr->count_elems)
    {
        for (size_t i = ind; i < arr->count_elems - 1; i++)
        {
            void *tmp = arr->a[i];
            arr->a[i] = arr->a[i + 1];
            arr->a[i + 1] = tmp;
        }
        arr->count_elems--;
    }
}

void print_free_adresses_arr(struct free_adresses *arr)
{
    if (arr->count_elems == 0)
        printf("Массив освобожденных адресов пуст\n");
    else
    {
        printf("Массив освобожденных адресов: \n");
        for (size_t i = 0; i < arr->count_elems; i++)
            printf(" %p", arr->a[i]);
        printf("\n");
    }
}
















