#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "errs.h"
#include "array.h"


// void print_arr(void *arr, size_t len_arr)
// {
//     int *parr = arr;
//     printf("Array: ");
//     for (int *pcur = parr; pcur < parr + len_arr; pcur++)
//         printf("%d ", *pcur);
//     printf("\n");
// }


int find_last_elem_filter(const int *pb_src, const int *pe_src, const int **pp_last_minus_el)
{
    const int *p_last_minus_el = *pp_last_minus_el;
    size_t len_new_arr = pe_src - pb_src;
    p_last_minus_el = pe_src - 1;

    while (p_last_minus_el >= pb_src && *p_last_minus_el >= 0)
    {
        len_new_arr--;
        p_last_minus_el--;
    }

    if (p_last_minus_el == pb_src)
        return ERR_EMPTY_FILTER_ARRAY;
        
    if (len_new_arr == 0)
    {
        len_new_arr = pe_src - pb_src;
        p_last_minus_el = pe_src;
    }

    *pp_last_minus_el = p_last_minus_el;
    return OK;
}

// вместо нее стандартную memcpy memmove
void copy_elems_arr(const int *pb_src, const int *pe_src, int *const pb_dst, int **pe_dst)
{
    assert(pe_src - pb_src > 0);

    int *pcur_new = pb_dst;
    for (const int *pcur_src = pb_src; pcur_src < pe_src; pcur_src++)
    {
        *pcur_new = *pcur_src;
        pcur_new++;
    }
    *pe_dst = pcur_new;
}

// защита
// void copy_elems_arr(const int *pb_src, const int *pe_src, int *const pb_dst, int **pe_dst)
// {
//     assert(pe_src - pb_src > 0);
//     memmove(pb_dst, pb_src, (pe_src - pb_src) * sizeof(int));

//     // printf("%d %d\n", *pb_src, *pb_dst);
//     // printf("%d %d\n", *(pb_src + 1), *(pb_dst + 1));
//     // printf("\n");
//     *pe_dst = pb_dst + (pe_src - pb_src);
// }


int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    int rc = OK;

    if (pe_src - pb_src == 0)
        return ERR_EMPTY_ARRAY;
    if (pe_src - pb_src < 0)
        return ERR_POINTERS;


    // определяем кол-во элементов удовлетворяющих условию
    size_t len_new_arr;
    const int *p_last_minus_el = NULL;
    rc = find_last_elem_filter(pb_src, pe_src, &p_last_minus_el);
    if (rc != OK)
        return rc;
    len_new_arr = p_last_minus_el - pb_src;
    //

    // Выделяем память под новый массив
    int *new_arr = NULL;
    new_arr = malloc(len_new_arr * sizeof(int));
    if (new_arr == NULL)
        return ERR_DYNAMIC_MEMORY;
    *pb_dst = new_arr;
    //

    // Копируем эелемнты удовлетворяющие условию из старого массива в новый
    copy_elems_arr(pb_src, p_last_minus_el, *pb_dst, pe_dst);
    // for (const int *pcur_src = *pb_dst; pcur_src < *pe_dst; pcur_src++)
    // {
    //     printf("%d ", *pcur_src);
    // }
    // printf("\n");
    //

    return OK;
}


int cmp_int(const void *l, const void *r)
{
    const int *pl = l, *pr = r;
    // printf("cmp:   %d %d\n", *pl, *pr);
    return *pl - *pr;
}

int cmp_str(const void *l, const void *r)
{
    const char *pl = l, *pr = r;
    return strcmp(pl, pr);
}


void swap(void *l, void *r, size_t elem_size)
{
    char tmp;
    char *pl = l, *pr = r;

    for (size_t i = 0; i < elem_size; i++)
    {
        tmp = *pl;
        *pl = *pr;
        *pr = tmp;
        pl++;
        pr++;
    }
}


// // поиск минимума для защиты
// char *find_min(char *pb, char *pe, size_t elem_size, uni_cmp_t cmp)
// {
//     char *pmin = pb;
//     for (char *pcur = pb + elem_size; pcur < pe; pcur += elem_size)
//         if (cmp(pmin, pcur) > 0)
//             pmin = pcur;

//     return pmin;
// }

// // сортировка выбором для защиты
// void mysort(void *arr, size_t len_arr, size_t elem_size, uni_cmp_t cmp)
// {
//     if (!len_arr)
//         return;

//     char *parr = arr;
//     char *pe_arr = parr + len_arr * elem_size;

//     char *pmin;
//     for (char *pcur = parr; pcur < pe_arr; pcur += elem_size)
//     {
//         pmin = find_min(pcur, pe_arr, elem_size, cmp);
//         swap(pmin, pcur, elem_size);
//     }
// }

// сортировка пузырьком по заданию
void mysort(void *arr, size_t len_arr, size_t elem_size, uni_cmp_t cmp)
{
    if (!len_arr)
        return;

    char *parr = arr;
    char *bottom = parr;
    char *top = parr + (len_arr - 1) * elem_size;
    char *new_bottom, *new_top;
    bool swapped = true;

    while (bottom < parr + (len_arr - 1) * elem_size && top > parr && bottom < top && swapped)
    {
        new_top = top;
        for (char *pcur = bottom; pcur < top; pcur += elem_size)
            if (cmp(pcur, pcur + elem_size) > 0)
            {
                swap(pcur, pcur + elem_size, elem_size);
                new_top = pcur;
            }
        
        // if (new_top == top)
        //     new_top -= elem_size;
        // top = new_top;
        if (new_top != top)
            top = new_top;
        else
            swapped = false;

        new_bottom = bottom;
        for (char *pcur = top; pcur > bottom; pcur -= elem_size)
            if (cmp(pcur - elem_size, pcur) > 0)
            {
                swap(pcur - elem_size, pcur, elem_size);
                new_bottom = pcur;
            }
        
        // if (new_bottom == bottom)
        //     new_bottom += elem_size;
        // bottom = new_bottom;
        if (new_bottom != bottom)
            bottom = new_bottom;
        else
            swapped = false;
    }
}

/* алгоритм сортировки на питоне
def bubble_sort(a):
    top = len(a) - 1
    bottom = 0

    while top > 0 and bottom < len(a) - 1 and bottom < top:
        new_top = top
        for j in range(bottom, top):
            if a[j] > a[j + 1]:
                a[j], a[j + 1] = a[j + 1], a[j]
                new_top = j

        if new_top == top:
            new_top -= 1
        top = new_top

        new_bottom = bottom
        for j in range(top, bottom, -1):
            if a[j - 1] > a[j]:
                a[j - 1], a[j] = a[j], a[j - 1]
                new_bottom = j

        if new_bottom == bottom:
            new_bottom += 1
        bottom = new_bottom
*/
