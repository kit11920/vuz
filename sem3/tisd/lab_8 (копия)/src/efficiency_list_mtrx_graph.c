#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "errs.h"
#include "fort.h"
#include "list_graph.h"
#include "mtrx_graph.h"
#include "efficiency.h"
#include "efficiency_list_mtrx_graph.h"



unsigned long long measure_time_for(void *data_struct)
{
    (void) data_struct;
    unsigned long long beg, end;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
        ;
    end = ms_now();
    return end - beg;
}

unsigned long long measure_time_mtrx_graph(void *data_struct)
{
    mtrxg_t *graph = data_struct;
    int *path = NULL;
    unsigned long long beg, end;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
    {
        find_ham_path_mtrx_graph(graph, &path);
        free(path);
    }
    end = ms_now();

    return end - beg;
}

unsigned long long measure_time_list_graph(void *data_struct)
{
    listg_t *graph = data_struct;
    int *path = NULL;
    unsigned long long beg, end;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
    {
        find_ham_path_list_graph(graph, &path);
        free(path);
    }
    end = ms_now();

    return end - beg;
}

int gettime_list_mtrx_graph(measure_time_t measure, void *data_struct, unsigned long long *t, size_t len_t, long long *time)
{
    double rse = 100;

    size_t i = 0;
    rse = 100;
    while (i < len_t && (rse > 5 || i <= MIN_COUNT_REAPET))
    {
        t[i] = measure(data_struct);
        
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

int make_compare_table_list_mtrx_graph(listg_t *list_graph, mtrxg_t *mtrx_graph)
{
    int rc = OK;
    unsigned long long *t = NULL;
    int len_t = 10000;
    long long for_time, list_ham_time, mtrx_ham_time;
    size_t list_bytes, mtrx_bytes;
    double koef_time, koef_bytes;

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
    ft_printf_ln(tab, "|list graph|mtrx graph|koef");

    rc = gettime_list_mtrx_graph(measure_time_for, NULL, t, len_t, &for_time);
    assert(rc == OK); 

    rc = gettime_list_mtrx_graph(measure_time_list_graph, list_graph, t, len_t, &list_ham_time);
    assert(rc == OK); 
    list_ham_time = minus_for_time(list_ham_time, for_time);

    rc = gettime_list_mtrx_graph(measure_time_mtrx_graph, mtrx_graph, t, len_t, &mtrx_ham_time);
    assert(rc == OK); 
    mtrx_ham_time = minus_for_time(mtrx_ham_time, for_time);

    koef_time = mtrx_ham_time / (double) list_ham_time;

    ft_printf_ln(tab, "find ham path (mks)|%lld|%lld|%.2lf", list_ham_time, mtrx_ham_time, koef_time);

    list_bytes = bytes_list_graph(list_graph);
    mtrx_bytes = bytes_mtrx_graph(mtrx_graph);
    koef_bytes = mtrx_bytes / (double) list_bytes;
    ft_printf_ln(tab, "bytes|%zu|%zu|%.2lf", list_bytes, mtrx_bytes, koef_bytes);


    printf("Узлы - %zu, ребра - %zu\n", mtrx_graph->count_v, count_edges(mtrx_graph));
    printf("Кол-во вычислений в одном замере: %d\n", COUNT_CALCS);
    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);

    free(t);
    return OK;
}













