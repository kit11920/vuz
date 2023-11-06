#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "free_adresses_arr.h"
#include "errs.h"


int init_free_adresses_arr(free_adresses_t *arr)
{
    free_adresses_t tmp;
    tmp.a = malloc(sizeof(void *) * INCREASE_SIZE_FREE_ADRESSES_ARR);
    if (tmp.a == NULL)
        return ERR_MEM;
    tmp.count_elems = 0;
    tmp.len_a = INCREASE_SIZE_FREE_ADRESSES_ARR;
    *arr = tmp;

    // printf("inited: %p - %p", (void *) arr->a, (void *) (arr->a + sizeof(void *) * BEG_SIZE_FREE_ADRESSES_ARR));

    return OK;
}

int resize_free_adresses_arr(free_adresses_t *arr)
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
        // printf("REALLOC:  %p\n", (void *) tmp);
        arr->a = tmp;
        arr->len_a *= bigger;
    }

    return OK;
}

int add_elem_free_adresses_arr(free_adresses_t *arr, void *p)
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

void del_elem_free_adresses_arr(free_adresses_t *arr, void *p)
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

void print_free_adresses_arr(free_adresses_t *arr)
{
    if (arr->count_elems == 0)
        printf("Массив освобожденных адресов пуст\n");
    else
    {
        printf("Массив освобожденных адресов (длина - %zu): \n", arr->count_elems);
        size_t end_print = arr->count_elems;
        if (end_print > MAX_PRINT_ARR)
            end_print = MAX_PRINT_ARR;

        for (size_t i = 0; i < end_print; i++)
            printf(" %p", arr->a[i]);
        
        if (arr->count_elems > MAX_PRINT_ARR)
            printf(" . . .");
        printf("\n");
    }
}



