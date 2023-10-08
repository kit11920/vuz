#include <stdlib.h>
#include <assert.h>



#include "country_struct.h"
#include "work_table.h"


#include <stdio.h>
#include "in_output.h"


void bubble_sort_orig_table(struct country_t table[], const size_t len_table)
{
    // // сортировка только по невалидному полю
    // assert(cmp != cmp_country_exrsn_trsm_count_sights && cmp != cmp_country_exrsn_trsm_type_sights &&
    //     cmp != cmp_country_beach_trsm_air_tempr && cmp != cmp_country_beach_trsm_water_tempr &&
    //     cmp != cmp_country_beach_trsm_season && cmp != cmp_country_sport_trsm_sport_type);

    if (len_table == 0)
        return;

    struct country_t tmp;
    for (size_t i = 0; i < len_table - 1; i++)
        for (size_t j = 0; j < len_table - 1 - i; j++)
            if (table[j].time > table[j + 1].time)
            {
                tmp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = tmp;
            }
}

void merge_orig_table(struct country_t table[], size_t l, size_t m, size_t r)
{
    struct country_t tmp[BIG_TABLE_LEN];
    size_t li = 0, mi = 0;

    while (l + li < m && m + mi <= r)
    {
        if (table[l + li].time <= table[m + mi].time)
        {
            tmp[li + mi] = table[l + li];
            li++;
        } 
        else
        {
            tmp[li + mi] = table[m + mi];
            mi++;
        }
    }
    while (l + li < m)
    {
        tmp[li + mi] = table[l + li];
        li++;
    }
    while (m + mi <= r)
    {
        tmp[li + mi] = table[m + mi];
        mi++;
    }

    for (size_t i = l; i <= r; i++)
        table[i] = tmp[i - l];
    // printf("l, m, r - %zu %zu %zu\n", l, m, r);
    // print_table_time(table, 8);
    // printf("\n");
}

void merge_sort_orig_table(struct country_t table[], size_t l, size_t r)
{
    // print_table_time(table, 8);
    
    if (r - l > 0)
    {
        size_t m;
        m = (l + r) / 2;
        // printf("l, r, m - %zu %zu %zu\n", l, r, m);
        merge_sort_orig_table(table, l, m);
        merge_sort_orig_table(table, m + 1, r);
        merge_orig_table(table, l, m + 1, r);
        // print_table_time(table, r - l + 1);
    }
}

void make_key_table(const struct country_t table[], const size_t len_table, struct key_table_t key_table[])
{
    for (size_t i = 0; i < len_table; i++)
    {
        key_table[i].ind_orig = table[i].ind;
        key_table[i].time = table[i].time;
    }
}

void bubble_sort_key_table(struct key_table_t table[], size_t len_table)
{
    if (len_table == 0)
        return;

    struct key_table_t tmp;
    for (size_t i = 0; i < len_table - 1; i++)
        for (size_t j = 0; j < len_table - 1 - i; j++)
            if (table[j].time > table[j + 1].time)
            {
                tmp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = tmp;
            }
}

void merge_key_table(struct key_table_t table[], size_t l, size_t m, size_t r)
{
    struct key_table_t tmp[BIG_TABLE_LEN];
    size_t li = 0, mi = 0;

    while (l + li < m && m + mi <= r)
    {
        if (table[l + li].time <= table[m + mi].time)
        {
            tmp[li + mi] = table[l + li];
            li++;
        } 
        else
        {
            tmp[li + mi] = table[m + mi];
            mi++;
        }
    }
    while (l + li < m)
    {
        tmp[li + mi] = table[l + li];
        li++;
    }
    while (m + mi <= r)
    {
        tmp[li + mi] = table[m + mi];
        mi++;
    }

    for (size_t i = l; i <= r; i++)
        table[i] = tmp[i - l];
}

void merge_sort_key_table(struct key_table_t table[], size_t l, size_t r)
{
    if (r - l > 0)
    {
        size_t m;
        m = (l + r) / 2;
        merge_sort_key_table(table, l, m);
        merge_sort_key_table(table, m + 1, r);
        merge_key_table(table, l, m + 1, r);
    }
}
















