#include <stdio.h>
#include <assert.h>

#include "efficiency_hash_tree.h"
#include "efficiency.h"
#include "fort.h"
#include "errs.h"
#include "external_hashing.h"
#include "internal_hashing.h"


int make_compare_table_hash_collision(int *data_arr, size_t len_arr)
{
    int rc = OK;
    unsigned long long *t = NULL;
    int len_t = 10000;
    long long for_time, ex_htab_find_time, in_htab_find_time;
    size_t ex_htab_bytes, in_htab_bytes;
    double ex_htab_mid_cmps, in_htab_mid_cmps;

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
    ft_printf_ln(tab, "size table\nm|external hash\nfind (mks)|external hash\nbytes|external hash\naverage cmps|internal hash\nfind (mks)|internal hash\nbytes|internal hash\naverage cmps");

    rc = gettime_hash_tree(measure_time_for, NULL, data_arr, len_arr, t, len_t, &for_time);
    assert(rc == OK); 

    int first = 1;
    size_t m = find_simple_bigger_n(len_arr);
    while (m <= len_arr * 4 || first)
    {
        first = 0;

        ex_hash_t ex_htab = create_ex_hash_table();
        rc = fill_ex_hash_table_with_m(&ex_htab, data_arr, len_arr, m);
        assert(rc == OK);
        rc = gettime_hash_tree(measure_time_ex_hash, &ex_htab, data_arr, len_arr, t, len_t, &ex_htab_find_time);
        assert(rc == OK); 
        ex_htab_find_time = minus_for_time(ex_htab_find_time, for_time);
        ex_htab_bytes = mem_bytes_ex_hash_table(&ex_htab);
        ex_htab_mid_cmps = mid_cmp_ex_hash_table(&ex_htab);
        // print_ex_hash_table(&ex_htab);
        free_ex_hash_tab(&ex_htab);

        in_hash_t in_htab = create_in_hash_table();
        rc = fill_in_hash_table_with_m(&in_htab, data_arr, len_arr, m);
        assert(rc == OK);
        rc = gettime_hash_tree(measure_time_in_hash, &in_htab, data_arr, len_arr, t, len_t, &in_htab_find_time);
        assert(rc == OK); 
        in_htab_find_time = minus_for_time(in_htab_find_time, for_time);
        in_htab_bytes = mem_bytes_in_hash_table(&in_htab);
        in_htab_mid_cmps = mid_cmp_in_hash_table(&in_htab);
        // print_in_hash_table(&in_htab);
        free_in_hash_tab(&in_htab);

        ft_printf_ln(tab, "%zu|%lld|%zu|%.2lf|%lld|%zu|%.2lf", m, ex_htab_find_time, ex_htab_bytes, ex_htab_mid_cmps, in_htab_find_time, in_htab_bytes, in_htab_mid_cmps);
        m = find_simple_bigger_n(m + 1);
    }

    printf("Кол-во вычислений в одном замере: %d\n", COUNT_CALCS);
    printf("В одном замере время поиска каждого элемента структуры в сумме\n");
    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);

    free(t);
    return OK;
}












