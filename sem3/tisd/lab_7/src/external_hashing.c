#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "external_hashing.h"
#include "errs.h"
#include "fort.h"

size_t find_simple_bigger_n(size_t n)
{
    size_t m = n;
    bool is_simple = false;

    while (!is_simple)
    {
        is_simple = true;
        for (size_t i = 2; i < m / 2 + 1 && is_simple; i++)
            if (m % i == 0)
                is_simple = false;
        if (!is_simple)
            m++;
    }
    return m;
}

ex_hash_t create_ex_hash_table(void)
{
    ex_hash_t htable;
    htable.m = 0;
    htable.arr = NULL;
    return htable;
}

lnode_t *create_list_node(int data)
{
    lnode_t *tmp = malloc(sizeof(lnode_t));
    if (tmp != NULL)
    {
        tmp->data = data;
        tmp->next = NULL;
    }
    return tmp;
}

void free_list(lnode_t **head)
{
    lnode_t *tmp;
    while (*head != NULL)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
}

void free_ex_hash_tab(ex_hash_t *htable)
{
    for (size_t i = 0; i < htable->m; i++)
        free_list(&htable->arr[i]);
    free(htable->arr);
    htable->arr = NULL;
    htable->m = 0;
}

int fill_ex_hash_table(ex_hash_t *htable, int arr[], size_t len_arr)
{
    double mid_cmp = 0;
    size_t m = find_simple_bigger_n(len_arr);

    int rc = fill_ex_hash_table_with_m(htable, arr, len_arr, m);
    if (rc == OK)
    {
        mid_cmp = mid_cmp_ex_hash_table(htable);
        // printf("mid_cmp: %lf\n", mid_cmp);
    }
    while (rc == OK && mid_cmp > MAX_MID_CMPS)
    {
        m = find_simple_bigger_n(m + 1);
        rc = fill_ex_hash_table_with_m(htable, arr, len_arr, m);
        if (rc == OK)
        {
            mid_cmp = mid_cmp_ex_hash_table(htable);
            // printf("mid_cmp: %lf\n", mid_cmp);
        }
    }
    return rc;
}

int fill_ex_hash_table_with_m(ex_hash_t *htable, int arr[], size_t len_arr, size_t m)
{
    htable->m = m;

    htable->arr = calloc(htable->m, sizeof(lnode_t *));
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
            htable->arr[k] = create_list_node(arr[i]);
            if (htable->arr[k] == NULL)
            {
                free_ex_hash_tab(htable);
                return ERR_MEM;
            }
        }
        else
        {
            size_t len_list = 2;
            lnode_t *last = htable->arr[k];
            while (last->next != NULL)
            {
                len_list++;
                last = last->next;
            }
            
            // if (len_list > MAX_LEN_LIST_HASH)
            // {
            //     free_ex_hash_tab(htable);
            //     return ERR_LEN_LIST_HASH_TABLE;
            // }

            last->next = create_list_node(arr[i]);
            if (last->next == NULL)
            {
                free_ex_hash_tab(htable);
                return ERR_MEM;
            }
        }
    }
    return OK;
}

char *list_to_str(lnode_t *head)
{
    char *str = NULL, *new_str = NULL;
    if (head == NULL)
        return NULL;

    if (asprintf(&str, "%d", head->data) < 0)
        return NULL;

    lnode_t *tmp = head->next;
    while (tmp != NULL)
    {
        if (asprintf(&new_str, "%s -> %d", str, tmp->data) < 0)
        {
            free(str);
            return NULL;
        }
        free(str);
        str = new_str;
        new_str = NULL;
        tmp = tmp->next;
    }
    return str;
}

void print_ex_hash_table(ex_hash_t *htable)
{
    printf("Таблица внешнего хеширования (метод цепочек):\n");
    printf("M = %zu\n", htable->m);
    ft_table_t *tab = ft_create_table();
    ft_set_border_style(tab, FT_SOLID_STYLE);
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_printf_ln(tab, "key|data");

    char *str = NULL;
    for (size_t i = 0; i < htable->m; i++)
    {
        if (htable->arr[i] == NULL)
            ft_printf_ln(tab, "%zu|-", i);
        else
        {
            str = list_to_str(htable->arr[i]);
            if (str == NULL)
            {
                print_err(ERR_MEM);
                ft_destroy_table(tab);
                return;
            }
            ft_printf_ln(tab, "%zu|%s", i, str);
            free(str);
            str = NULL;
        }
    }
    printf("%s", ft_to_string(tab));
    ft_destroy_table(tab);
}

size_t count_comparison_ex_hash_table(ex_hash_t *htable)
{
    size_t count = 0, height;
    lnode_t *tmp;
    for (size_t i = 0; i < htable->m; i++)
        if (htable->arr[i] != NULL)
        {
            tmp = htable->arr[i];
            height = 1;
            while (tmp != NULL)
            {
                count += height;
                height++;
                tmp = tmp->next;
            }
        }
    return count;
}

double mid_cmp_ex_hash_table(ex_hash_t *htable)
{
    size_t cmps = 0, elems = 0, height;
    lnode_t *tmp;
    for (size_t i = 0; i < htable->m; i++)
        if (htable->arr[i] != NULL)
        {
            tmp = htable->arr[i];
            height = 1;
            while (tmp != NULL)
            {
                elems++;
                cmps += height;
                height++;
                tmp = tmp->next;
            }
        }
    return cmps / (double) elems;
}

size_t mem_bytes_ex_hash_table(ex_hash_t *htable)
{
    size_t bytes = sizeof(*htable) + htable->m * sizeof(lnode_t *);

    lnode_t *tmp;
    for (size_t i = 0; i < htable->m; i++)
        if (htable->arr[i] != NULL)
        {
            tmp = htable->arr[i];
            while (tmp != NULL)
            {
                bytes += sizeof(lnode_t);
                tmp = tmp->next;
            }
        }
    return bytes;   
}

int *find_ex_hash_table(ex_hash_t *htable, int data)
{
    size_t key = abs(data) % htable->m;
    lnode_t *tmp = htable->arr[key];

    while (tmp != NULL && tmp->data != data)
        tmp = tmp->next;
        
    if (tmp == NULL)
        return NULL;
    return &tmp->data;
}












