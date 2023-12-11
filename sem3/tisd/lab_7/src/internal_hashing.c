#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "external_hashing.h"
#include "errs.h"
#include "fort.h"
#include "internal_hashing.h"


in_hash_t create_in_hash_table(void)
{
    in_hash_t htable;
    htable.m = 0;
    htable.arr = NULL;
    return htable;
}

void free_in_hash_tab(in_hash_t *htable)
{
    for (size_t i = 0; i < htable->m; i++)
        free(htable->arr[i]);
    free(htable->arr);
    htable->arr = NULL;
    htable->m = 0;
}

ihdata_t *create_data_in_hash_table(int data)
{
    ihdata_t *tmp = malloc(sizeof(ihdata_t));
    if (tmp != NULL)
        tmp->data = data;
    return tmp;
}

int fill_in_hash_table(in_hash_t *htable, int arr[], size_t len_arr)
{
    double mid_cmp = 0;
    // size_t m = find_simple_bigger_n((size_t) ((double) len_arr * 1.2));
    size_t m = find_simple_bigger_n(len_arr);

    int rc = fill_in_hash_table_with_m(htable, arr, len_arr, m);
    if (rc == OK)
    {
        mid_cmp = mid_cmp_in_hash_table(htable);
        // printf("mid_cmp: %lf\n", mid_cmp);
    }
    while (rc == ERR_OVERFLOW_IN_HASH_TABLE || mid_cmp > MAX_MID_CMPS)
    {
        m = find_simple_bigger_n(m + 1);
        rc = fill_in_hash_table_with_m(htable, arr, len_arr, m);
        if (rc == OK)
        {
            mid_cmp = mid_cmp_in_hash_table(htable);
            // printf("mid_cmp: %lf\n", mid_cmp);
        }
    }
    return rc;
}

int fill_in_hash_table_with_m(in_hash_t *htable, int arr[], size_t len_arr, size_t m)
{
    htable->m = m;

    htable->arr = calloc(htable->m, sizeof(int *));
    if (htable->arr == NULL)
        return ERR_MEM;
    for (size_t i = 0; i < htable->m; i++)
        htable->arr[i] = NULL;

    size_t k;
    for (size_t i = 0; i < len_arr; i++)
    {
        k = abs(arr[i]) % htable->m;

        if (htable->arr[k] == NULL)
        {
            htable->arr[k] = create_data_in_hash_table(arr[i]);
            if (htable->arr[k] == NULL)
            {
                free_in_hash_tab(htable);
                return ERR_MEM;
            }
        }
        else
        {
            size_t next_k = k;
            while (htable->arr[next_k] != NULL)
            {
                if (next_k + 1 == htable->m)
                    next_k = 0;
                else
                    next_k++;
                if (next_k == k)
                {
                    free_in_hash_tab(htable);
                    return ERR_OVERFLOW_IN_HASH_TABLE;
                }
            }
            htable->arr[next_k] = create_data_in_hash_table(arr[i]);
            if (htable->arr[next_k] == NULL)
            {
                free_in_hash_tab(htable);
                return ERR_MEM;
            }
        }
    }
    return OK;
}

void print_in_hash_table(in_hash_t *htable)
{
    printf("Таблица внутреннего хеширования (линейная адресация):\n");
    printf("M = %zu\n", htable->m);
    ft_table_t *tab = ft_create_table();
    ft_set_border_style(tab, FT_SOLID_STYLE);
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_printf_ln(tab, "key|data|real\nkey");

    for (size_t i = 0; i < htable->m; i++)
    {
        if (htable->arr[i] == NULL)
            ft_printf_ln(tab, "%zu|-|-", i);
        else
            ft_printf_ln(tab, "%zu|%d|%zu", i, htable->arr[i]->data, abs(htable->arr[i]->data) % htable->m);
    }
    printf("%s", ft_to_string(tab));
    ft_destroy_table(tab);
}

size_t count_comparison_in_hash_table(in_hash_t *htable)
{
    size_t count = 0;
    for (size_t i = 0; i < htable->m; i++)
        if (htable->arr[i] != NULL)
        {
            size_t key = abs(htable->arr[i]->data) % htable->m;
            if (key == i)
                count++;
            else
            {
                if (key < i)
                    count += i - key + 1;
                else
                    count += htable->m - key + i + 1;
            }
        }
    return count;
}

double mid_cmp_in_hash_table(in_hash_t *htable)
{
    size_t cmps = 0, elems = 0;
    for (size_t i = 0; i < htable->m; i++)
        if (htable->arr[i] != NULL)
        {
            elems++;
            size_t key = abs(htable->arr[i]->data) % htable->m;
            if (key == i)
                cmps++;
            else
            {
                if (key < i)
                    cmps += i - key + 1;
                else
                    cmps += htable->m - key + i + 1;
            }
        }
    return cmps / (double) elems;
}

size_t mem_bytes_in_hash_table(in_hash_t *htable)
{
    size_t bytes = sizeof(in_hash_t) + htable->m * sizeof(ihdata_t *);
    for (size_t i = 0; i < htable->m; i++)
        if (htable->arr[i] != NULL)
            bytes += sizeof(ihdata_t);
    return bytes;
}

int *find_in_hash_table(in_hash_t *htable, int data)
{
    size_t real_key = abs(data) % htable->m;
    size_t key = real_key;
    while (htable->arr[key]->data != data)
    {
        key++;
        if (key == htable->m)
            key = 0;
        if (key == real_key)
            return NULL;
    }
    return &htable->arr[key]->data;
}










