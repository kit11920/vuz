#include <stdio.h>
#include <assert.h>

#include "efficiency.h"
#include"efficiency_hash_tree.h"
#include "fort.h"
#include "errs.h"
#include "tree.h"
#include "balanced_tree.h"
#include "external_hashing.h"
#include "internal_hashing.h"


unsigned long long measure_time_for(void *data_struct, int *arr, size_t len_arr)
{
    unsigned long long beg, end;
    (void) data_struct;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
        for (size_t j = 0; j < len_arr; j++)
            (void) arr[j];
    end = ms_now();
    return end - beg;
}

unsigned long long measure_time_bs_tree(void *data_struct, int *arr, size_t len_arr)
{
    node_t *root = data_struct, *parant = NULL;
    unsigned long long beg, end;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
        for (size_t j = 0; j < len_arr; j++)
            find_node_tree(root, arr[j], &parant);
    end = ms_now();
    return end - beg;
}

unsigned long long measure_time_bal_tree(void *data_struct, int *arr, size_t len_arr)
{
    bnode_t *root = data_struct, *parant = NULL;
    unsigned long long beg, end;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
        for (size_t j = 0; j < len_arr; j++)
            find_btree(root, arr[j], &parant);
    end = ms_now();
    return end - beg;
}

unsigned long long measure_time_ex_hash(void *data_struct, int *arr, size_t len_arr)
{
    ex_hash_t *htab = data_struct;
    unsigned long long beg, end;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
        for (size_t j = 0; j < len_arr; j++)
            find_ex_hash_table(htab, arr[j]);
    end = ms_now();
    return end - beg;
}

unsigned long long measure_time_in_hash(void *data_struct, int *arr, size_t len_arr)
{
    in_hash_t *htab = data_struct;
    unsigned long long beg, end;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
        for (size_t j = 0; j < len_arr; j++)
            find_in_hash_table(htab, arr[j]);
    end = ms_now();
    return end - beg;
}


int gettime_hash_tree(measure_time_t measure, void *exp, int *arr, size_t len_arr, unsigned long long *t, size_t len_t, long long *time)
{
    double rse = 100;

    size_t i = 0;
    rse = 100;
    while (i < len_t && (rse > 5 || i <= MIN_COUNT_REAPET))
    {
        t[i] = measure(exp, arr, len_arr);
        
        rse = get_rse(t, i + 1);
        i++;
    }
    
    if (i >= len_t)
        return ERR_COUNT_REPEAT_TIME_SMALL;
    
    *time = (long long) get_tavg(t, i);
    
    return OK;
}

long long minus_for_time(long long time, long long for_time)
{
    if (for_time > time)
        time = 0;
    else
        time -= for_time;
    return time;
}

int make_compare_table_hash_tree(node_t *tree, bnode_t *btree, ex_hash_t *ex_htab, in_hash_t *in_htab, int *data_arr, size_t len_arr)
{
    int rc = OK;
    unsigned long long *t = NULL;
    int len_t = 10000;
    long long for_time, tree_find_time, btree_find_time, ex_htab_find_time, in_htab_find_time;
    size_t tree_bytes, btree_bytes, ex_htab_bytes, in_htab_bytes;
    double tree_mid_cmps, btree_mid_cmps, ex_htab_mid_cmps, in_htab_mid_cmps;

    // Выделение памяти под вспомагательные структуры
    t = malloc(len_t * sizeof(unsigned long long));
    if (!t)
    {
        rc = ERR_MEM;
        return rc;
    }
    //

    printf("Подождите, идет обработка данных...\n");
    ft_table_t *tab = ft_create_table();
    ft_set_border_style(tab, FT_SOLID_STYLE);
    ft_set_cell_prop(tab, FT_ANY_ROW, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_printf_ln(tab, "|bin search tree|balanced tree|external hash|internal hash");

    rc = gettime_hash_tree(measure_time_for, NULL, data_arr, len_arr, t, len_t, &for_time);
    assert(rc == OK); 

    rc = gettime_hash_tree(measure_time_bs_tree, tree, data_arr, len_arr, t, len_t, &tree_find_time);
    assert(rc == OK); 
    tree_find_time = minus_for_time(tree_find_time, for_time);

    rc = gettime_hash_tree(measure_time_bal_tree, btree, data_arr, len_arr, t, len_t, &btree_find_time);
    assert(rc == OK); 
    btree_find_time = minus_for_time(btree_find_time, for_time);

    rc = gettime_hash_tree(measure_time_ex_hash, ex_htab, data_arr, len_arr, t, len_t, &ex_htab_find_time);
    assert(rc == OK); 
    ex_htab_find_time = minus_for_time(ex_htab_find_time, for_time);

    rc = gettime_hash_tree(measure_time_in_hash, in_htab, data_arr, len_arr, t, len_t, &in_htab_find_time);
    assert(rc == OK); 
    in_htab_find_time = minus_for_time(in_htab_find_time, for_time);


    ft_printf_ln(tab, "find (mks)|%lld|%lld|%lld|%lld", tree_find_time, btree_find_time, ex_htab_find_time, in_htab_find_time);
    
    tree_bytes = mem_bytes_tree(tree);
    btree_bytes = mem_bytes_btree(btree);
    ex_htab_bytes = mem_bytes_ex_hash_table(ex_htab);
    in_htab_bytes = mem_bytes_in_hash_table(in_htab);
    ft_printf_ln(tab, "bytes|%zu|%zu|%zu|%zu", tree_bytes, btree_bytes, ex_htab_bytes, in_htab_bytes);


    tree_mid_cmps = mid_cmp_tree(tree); 
    btree_mid_cmps = mid_cmp_btree(btree);
    ex_htab_mid_cmps = mid_cmp_ex_hash_table(ex_htab);
    in_htab_mid_cmps = mid_cmp_in_hash_table(in_htab);
    ft_printf_ln(tab, "average\ncomparisons|%.2lf|%.2lf|%.2lf|%.2lf", tree_mid_cmps, btree_mid_cmps, ex_htab_mid_cmps, in_htab_mid_cmps);

    printf("Кол-во вычислений в одном замере: %d\n", COUNT_CALCS);
    printf("В одном замере время поиска каждого элемента структуры в сумме\n");
    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);

    free(t);
    return OK;
}











