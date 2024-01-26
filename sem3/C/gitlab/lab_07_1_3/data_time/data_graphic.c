#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include <sys/time.h>
#include <time.h>

#include "array.h"
#include "errs.h"

// заполнение неотсортированного массива
void fill_us_arr(int arr[], size_t len_arr)
{
    srand(time(NULL));
    for (size_t i = 0; i < len_arr; i++)
        arr[i] = rand() % 100;
}

// заполнение отсортированного массива
void fill_s_arr(int arr[], size_t len_arr)
{
    for (size_t i = 0; i < len_arr; i++)
        arr[i] = i;
}

// возвращает время в мс
unsigned long long ms_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return -1ULL;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
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
        s = (t[i] - tavg) * (t[i] - tavg);
    s = sqrt(s / (len_t - 1));
    rse = s / (sqrt(len_t) * tavg) * 100;

    return rse;
}


typedef void (*sort_t)(void *arr, size_t len_arr, size_t elem_size, uni_cmp_t cmp);
typedef void (*fill_arr_t)(int arr[], size_t len_arr);

int update_data(int *arr, size_t len_arr, sort_t sort, fill_arr_t fill_arr, 
unsigned long long *t, size_t len_t, char *data_file, char *tab_data_file)
{
    unsigned long long beg, end;

    double rse = 100;
    double tavg;
    FILE *f;
    size_t min_count_repeat = 20;

    size_t i = 0;
    rse = 100;
    while (i < len_t && (rse > 5 || i <= min_count_repeat))
    {
        fill_arr(arr, len_arr);
        beg = ms_now();
        sort(arr, len_arr, sizeof(int), cmp_int);
        end = ms_now();

        t[i] = end - beg;
        // printf("\n\n\n START\n");
        rse = get_rse(t, len_t);
        // printf("\nRSE: %f\n\n", rse);
        i++;
    }
    
    if (i >= len_t)
        return ERR_COUNT_REPEAT_TIME_SMALL;
    
    tavg = get_tavg(t, i);

    f = fopen(data_file, "a");
    if (!f)
        return ERR_FILE_DATA_TIME_NOT_EXICT;
    fprintf(f, "%zu %lld\n", len_arr, (long long) tavg);
    fclose(f);

    // printf("\n%s\n", tab_data_file);
    f = fopen(tab_data_file, "a");
    if (!f)
        return ERR_FILE_DATA_TIME_NOT_EXICT;
    fprintf(f, "|%zu|%lld|%zu|%.2lf|\n", len_arr, (long long) tavg, i, rse);
    // printf("|%zu|%lld|%zu|%lf|\n", len_arr, (long long) tavg, i, rse);
    fclose(f);

    return OK;
}


#define DATA_MYSORT_S "./data_time/mysort_s.txt"
#define DATA_MYSORT_US "./data_time/mysort_us.txt"
#define DATA_QSORT_S "./data_time/qsort_s.txt"
#define DATA_QSORT_US "./data_time/qsort_us.txt"

#define TAB_DATA_MYSORT_S "./data_time/tabs/mysort_s.txt"
#define TAB_DATA_MYSORT_US "./data_time/tabs/mysort_us.txt"
#define TAB_DATA_QSORT_S "./data_time/tabs/qsort_s.txt"
#define TAB_DATA_QSORT_US "./data_time/tabs/qsort_us.txt"

void prep_files(void)
{
    FILE *f;
    f = fopen(DATA_MYSORT_S, "w");
    fclose(f);
    f = fopen(DATA_MYSORT_US, "w");
    fclose(f);
    f = fopen(DATA_QSORT_S, "w");
    fclose(f);
    f = fopen(DATA_QSORT_US, "w");
    fclose(f);
    f = fopen(TAB_DATA_MYSORT_S, "w");
    if (f)
        fprintf(f, "len_arr|ms|repeats|rse\n|---|---|---|---|\n");
    fclose(f);
    f = fopen(TAB_DATA_MYSORT_US, "w");
    if (f)
        fprintf(f, "len_arr|ms|repeats|rse\n|---|---|---|---|\n");
    fclose(f);
    f = fopen(TAB_DATA_QSORT_S, "w");
    if (f)
        fprintf(f, "len_arr|ms|repeats|rse\n|---|---|---|---|\n");
    fclose(f);
    f = fopen(TAB_DATA_QSORT_US, "w");
    if (f)
        fprintf(f, "len_arr|ms|repeats|rse\n|---|---|---|---|\n");
    fclose(f);
}

int main(void)
{
    int *arr = NULL;
    size_t beg_size_s = 10, end_size_s = 400010, step_s = 20000;
    size_t beg_size_us = 10, end_size_us = 5010, step_us = 500;

    // size_t beg_size_s = 10, end_size_s = 10010, step_s = 1000;
    // size_t beg_size_us = 10, end_size_us = 5010, step_us = 500;

    unsigned long long *t = NULL;
    int len_t = 100;
    int rc = OK;
 
    // очищаем файлы
    prep_files();
    //

    printf("SORTED: \n");
    for (size_t len_arr = beg_size_s; len_arr <= end_size_s; len_arr += step_s)
    {
        printf("size %zu \t", len_arr);
        arr = malloc(len_arr * sizeof(int));
        t = malloc(len_t * sizeof(unsigned long long));
        if (!arr && !t)
            return ERR_DYNAMIC_MEMORY;

        // qsort_s
        printf("qsort s\t");
        rc = update_data(arr, len_arr, qsort, fill_s_arr, t, len_t, DATA_QSORT_S, TAB_DATA_QSORT_S);
        if (rc != OK)
            return rc;
        //

        // mysort_s
        printf("mysort s\t");
        rc = update_data(arr, len_arr, mysort, fill_s_arr, t, len_t, DATA_MYSORT_S, TAB_DATA_MYSORT_S);
        if (rc != OK)
            return rc;
        //

        printf("\n");
        free(arr);
    }

    printf("\nUNSORTED: \n");
    for (size_t len_arr = beg_size_us; len_arr <= end_size_us; len_arr += step_us)
    {
        printf("size %zu \t", len_arr);
        arr = malloc(len_arr * sizeof(int));
        t = malloc(len_t * sizeof(unsigned long long));
        if (!arr && !t)
            return ERR_DYNAMIC_MEMORY;

        // qsort_us
        printf("qsort us\t");
        rc = update_data(arr, len_arr, qsort, fill_us_arr, t, len_t, DATA_QSORT_US, TAB_DATA_QSORT_US);
        if (rc != OK)
            return rc;
        //

        // mysort_us
        printf("mysort us\t");
        rc = update_data(arr, len_arr, mysort, fill_us_arr, t, len_t, DATA_MYSORT_US, TAB_DATA_MYSORT_US);
        if (rc != OK)
            return rc;
        //

        printf("\n");
        free(arr);
    }    
}