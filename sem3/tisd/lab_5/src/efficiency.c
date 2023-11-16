#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>

#include "arr.h"
#include "list.h"
#include "errs.h"
#include "fort.h"

#define MIN_COUNT_REAPET 100

#define BEGIN 5000
#define END 50000
#define STEP 5000

// возвращает время в мкс
unsigned long long ms_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return -1ULL;

    // return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
    return val.tv_sec * 1000000ULL + val.tv_usec;
}

double get_tavg(unsigned long long *t, size_t len_t)
{
    assert(len_t != 0);
    unsigned long long sum = 0;
    double tavg;

    for (size_t i = 0; i < len_t; i++)
    {
        sum += t[i];
    }

    if (sum == 0)
        tavg = 0.0;
    else
        tavg = sum / len_t;

    assert( tavg >= 0);
    return tavg;
}

double get_rse(unsigned long long *t, size_t len_t)
{
    double tavg;
    double s, rse, eps = 1e-5;

    tavg = get_tavg(t, len_t);
    if (fabs(tavg) < eps)
        return 0.0;
    // printf("tavg: %lld\n", tavg);
    // printf("len_t, sqrt(len_t): %zu %f\n", len_t, sqrt(len_t));

    for (size_t i = 0; i < len_t; i++)
    {
        // printf("%llu ", t[i]);
        s = (t[i] - tavg) * (t[i] - tavg);
    }
    s = sqrt(s / (len_t - 1));
    rse = s / (sqrt(len_t) * tavg) * 100;

    // if (rse > 10.0)
    // {
    //     printf("RSE: %lf\t\t", rse);
    //     for (size_t i = 0; i < len_t; i++)
    //         printf("%llu ", t[i]);
    //     printf("\n");
    // }
        

    return rse;
}


typedef unsigned long long (* measure_time_t)(size_t);

unsigned long long measure_time_add_arr_queue(size_t size)
{
    arr_queue_t queue;
    init_arr_queue(&queue);
    unsigned long long beg, end, beg2, end2, time = 0;

    beg = ms_now();
    for (size_t i = 0; i < size; i++)
        push_arr_queue(&queue, 1.2);
    end = ms_now();

    beg2 = ms_now();
    for (size_t i = 0; i < size; i++)
        ;
    end2 = ms_now();

    // for (size_t i = 0; i < size; i++)
    //     del_elem_static_stack(&stack);

    if (end2 - beg2 < end - beg)
        time += end - beg - (end2 - beg2);

    // printf("qwe   %llu %llu \n", end - beg, end2 - beg2);

    return time;
}

unsigned long long measure_time_add_list_queue(size_t size)
{
    list_queue_t queue;
    init_list_queue(&queue);
    unsigned long long beg, end, beg2, end2;

    beg = ms_now();
    for (size_t i = 0; i < size; i++)
        just_push_list_queue(&queue, 1.2);
    end = ms_now();

    beg2 = ms_now();
    for (size_t i = 0; i < size; i++)
        ;
    end2 = ms_now();

    // for (size_t i = 0; i < size; i++)
    //     del_elem_list_stack(&stack, &prev);
    free_queue(&queue);

    // printf("qwe   %llu %llu \n", end - beg, end2 - beg2);

    if (end2 - beg2 >= end - beg)
        return 0ull;

    return end - beg - (end2 - beg2);
}

unsigned long long measure_time_del_arr_queue(size_t size)
{
    arr_queue_t queue;
    init_arr_queue(&queue);
    unsigned long long beg, end, beg2, end2, time = 0;
    double tmp;

    for (size_t i = 0; i < size; i++)
        push_arr_queue(&queue, (double) i);

    beg = ms_now();
    for (size_t i = 0; i < size; i++)
        pop_arr_queue(&queue, &tmp);
    end = ms_now();

    beg2 = ms_now();
    for (size_t i = 0; i < size; i++)
        ;
    end2 = ms_now();

    if (end2 - beg2 < end - beg)
        time += end - beg - (end2 - beg2);

    // printf("qwe   %llu %llu \n", end - beg, end2 - beg2);

    return time;
}

unsigned long long measure_time_del_list_queue(size_t size)
{
    list_queue_t queue;
    init_list_queue(&queue);
    unsigned long long beg, end, beg2, end2;
    double tmp;

    for (size_t i = 0; i < size; i++)
        just_push_list_queue(&queue, (double) i);

    beg = ms_now();
    for (size_t i = 0; i < size; i++)
        just_pop_list_queue(&queue, &tmp);
    end = ms_now();

    beg2 = ms_now();
    for (size_t i = 0; i < size; i++)
        ;
    end2 = ms_now();

    free_queue(&queue);

    // printf("qwe   %llu %llu \n", end - beg, end2 - beg2);
    if (end2 - beg2 >= end - beg)
        return 0ull;
    return end - beg - (end2 - beg2);
}


int gettime(measure_time_t measure, size_t size, unsigned long long *t, size_t len_t, long long *time)
{
    double rse = 100;

    size_t i = 0;
    rse = 100;
    while (i < len_t && (rse > 5 || i <= MIN_COUNT_REAPET))
    {
        t[i] = measure(size);
        
        // printf("\n\n\n START\n");
        rse = get_rse(t, i + 1);
        // printf("\nRSE: %f\n", rse);
        i++;
    }
    
    if (i >= len_t)
        return ERR_COUNT_REPEAT_TIME_SMALL;
    
    *time = (long long) get_tavg(t, i);
    
    return OK;
}

int make_compare_table(void)
{
    int rc = OK;
    unsigned long long *t = NULL;
    int len_t = 500;
    long long static_add_time, list_add_time, static_del_time, list_del_time;
    size_t static_bytes, list_bytes;
    int perc_add, perc_del, perc_bytes;

    static_bytes = sizeof(arr_queue_t);

    // Выделение памяти под вспомагательные структуры
    t = malloc(len_t * sizeof(unsigned long long));
    if (!t)
    {
        rc = ERR_MEM;
        return rc;
    }
    //


    size_t beg = BEGIN, end = END, step = STEP;
    assert (end <= MAX_LEN_ARR_QUEUE && end <= MAX_LEN_LIST_QUEUE);
    // size_t beg = 1, end = 10, step = 1;

    printf("Подождите, идет обработка данных...\n");
    ft_table_t *tab = ft_create_table();
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_printf_ln(tab, "size|add \n(array, mks)|add \n(list, mks)|efficiency\nadd|del \n(array, mks)|del \n(list, mks)|efficiency\ndel| array \n bytes| list \n bytes|percent\nbytes");

    // printf("Размер\t| Добавление элемента в стек (мкс)\t\t| Удаление элемента из стека (мкс)\t\t| Обьем памяти (Б)\n");
    // printf("\t|статический массив|список \t| процент |статический массив|список \t| процент |статический массив |список \n");
    for (size_t size = beg; size <= end; size += step)
    {
        list_bytes = sizeof(list_queue_t) + sizeof(node_t) * size;

        rc = gettime(measure_time_add_arr_queue, size, t, len_t, &static_add_time);
        if (rc != OK)
        {
            print_err(rc);
            return rc;
        }

        rc = gettime(measure_time_del_arr_queue, size, t, len_t, &static_del_time);
        if (rc != OK)
        {
            print_err(rc);
            return rc;
        }

        rc = gettime(measure_time_add_list_queue, size, t, len_t, &list_add_time);
        if (rc != OK)
        {
            print_err(rc);
            return rc;
        }

        rc = gettime(measure_time_del_list_queue, size, t, len_t, &list_del_time);
        if (rc != OK)
        {
            print_err(rc);
            return rc;
        }

        perc_add = (int) round((list_add_time - static_add_time) / (double) list_add_time * 100);
        perc_del = (int) round((list_del_time - static_del_time) / (double) list_del_time * 100);
        if (list_bytes >= static_bytes)
            perc_bytes = (int) round((list_bytes - static_bytes) / (double) list_bytes * 100);
        else
            perc_bytes = -(int) round((static_bytes - list_bytes) / (double) static_bytes * 100);
        // printf("%zu\t|%lld\t\t\t| %lld\t\t| %d |%lld\t\t| %lld\t\t| %d |%zu\t\t| %zu | %d\n", 
        // size, static_add_time, list_add_time, perc_add, static_del_time, list_del_time, perc_del, static_bytes, list_bytes, perc_bytes);
        ft_printf_ln(tab, "%zu|%lld|%lld|%d%%|%lld|%lld|%d%%|%zu|%zu|%d%%", 
        size, static_add_time, list_add_time, perc_add, static_del_time, list_del_time, perc_del, static_bytes, list_bytes, perc_bytes);
    }
    printf("Размер статического массива - %d\n", MAX_LEN_ARR_QUEUE);
    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);
    // just_clear_list_stack(&li_stack);
    free(t);
    return OK;
}




