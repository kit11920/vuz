#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>

#include "in_output.h"
#include "mtrx.h"
#include "errs.h"
#include "operations.h"

#define ROWS 5000
#define COLS 5000
#define MIN_COUNT_REAPET 15

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
    {
        // printf("%llu ", t[i]);
        s = (t[i] - tavg) * (t[i] - tavg);
    }
    s = sqrt(s / (len_t - 1));
    rse = s / (sqrt(len_t) * tavg) * 100;

    return rse;
}

int gettime_addition_standart_mtrx(struct standard_mtrx *mtrx1, struct standard_mtrx *mtrx2, struct standard_mtrx *mtrx_res, 
                                    unsigned long long *t, size_t len_t, long long *time)
{
    unsigned long long beg, end;
    double rse = 100;

    size_t i = 0;
    rse = 100;
    while (i < len_t && (rse > 5 || i <= MIN_COUNT_REAPET))
    {
        beg = ms_now();
        addition_standart_mtrx(mtrx1, mtrx2, mtrx_res);
        end = ms_now();

        t[i] = end - beg;
        // printf("\n\n\n START\n");
        rse = get_rse(t, i + 1);
        // printf("\nRSE: %f\n\n", rse);
        i++;
    }

    if (i >= len_t)
        return ERR_COUNT_REPEAT_TIME_SMALL;
    
    *time = (long long) get_tavg(t, i);
    
    return OK;
}

int gettime_addition_sparse_mtrx(struct sparse_mtrx *mtrx1, struct sparse_mtrx *mtrx2, struct sparse_mtrx *mtrx_res, 
                                    unsigned long long *t, size_t len_t, long long *time)
{
    unsigned long long beg, end;
    double rse = 100;

    size_t i = 0;
    rse = 100;
    while (i < len_t && (rse > 5 || i <= MIN_COUNT_REAPET))
    {
        beg = ms_now();
        addition_sparse_mtrx(mtrx1, mtrx2, mtrx_res);
        end = ms_now();

        t[i] = end - beg;
        // printf("\n\n\n START\n");
        rse = get_rse(t, i + 1);
        // printf("\nRSE: %f\n\n", rse);
        i++;
    }

    if (i >= len_t)
        return ERR_COUNT_REPEAT_TIME_SMALL;
    
    *time = (long long) get_tavg(t, i);
    
    return OK;
}

size_t count_st_mtrx_bytes(size_t rows, size_t cols)
{
    size_t b = 0;
    b = sizeof(struct standard_mtrx) + rows * sizeof(int *) + rows * cols * sizeof(int);
    return b;
}

size_t count_sp_mtrx_bytes(struct sparse_mtrx *mtrx)
{
    size_t b = 0;
    b = sizeof(*mtrx) + mtrx->len_a * sizeof(int) + mtrx->len_a * sizeof(int) + mtrx->cols * sizeof(int);
    return  b;
}

int make_compare_table(void)
{
    struct standard_mtrx mtrx1, mtrx2, mtrx_res;
    struct sparse_mtrx sp_mtrx1, sp_mtrx2, sp_mtrx_res;
    unsigned long long *t = NULL;
    int len_t = 100;
    int rc = OK;
    long long st_time, sp_time;
    int percent_time = 0, percent_bytes = 0;
    size_t st_mtrx_bytes, sp_mtrx_bytes;
    st_mtrx_bytes = count_st_mtrx_bytes(ROWS, COLS);

    // Выделяем память под матрицы стандартного вида
    mtrx1.mtrx = mtrx_alloc(ROWS, COLS);
    if (mtrx1.mtrx == NULL)
        return ERR_MEM;
    mtrx2.mtrx = mtrx_alloc(ROWS, COLS);
    if (mtrx2.mtrx == NULL)
    {
        rc = ERR_MEM;
        goto ending_0;
    }
    mtrx_res.mtrx = mtrx_alloc(ROWS, COLS);
    if (mtrx_res.mtrx == NULL)
    {
        rc = ERR_MEM;
        goto ending_1;
    }
    mtrx1.rows = mtrx2.rows = mtrx_res.rows = ROWS;
    mtrx1.cols = mtrx2.cols  = mtrx_res.cols = COLS;
    //

    // Выделение памяти под вспомагательные структуры
    t = malloc(len_t * sizeof(unsigned long long));
    if (!t)
    {
        rc = ERR_MEM;
        goto ending_2;
    }
    //

    // Заголовок таблицы
    printf("\n");
    printf("Размер матрицы: %d x %d\n", ROWS, COLS);
    printf("\t\t|\t\tВремя обработки (мс)\t\t|\tЗанимаемая память одной матрицей (байты)\n");
    printf("Процент\t\t|Стандартный\tСжатый\t\tЭффективность\t|Стандартный\tСжатый\t\tЭффективность\n");
    printf("заполненности\t|вид матрицы\tвид матрицы\tпо времени\t|вид матрицы\tвид матрицы\tпо памяти\n");
    printf("\n");
    //

    for (int percent = 1; percent <= 100 && percent_bytes >= 0; percent++)
    {
        input_mtrx_random(&mtrx1, percent, 0);
        input_mtrx_random(&mtrx2, percent, 1);


        // Сложение матриц в стандартном виде
        rc = gettime_addition_standart_mtrx(&mtrx1, &mtrx2, &mtrx_res, t, len_t, &st_time);
        if (rc != OK)
            goto ending_2;
        //

        // Заполнение структур разреженной матрицы 1, 2 и результирующей и выделение под них памяти
        // Сложение матриц в сжатом виде
        rc = standard_mtrx_to_sparse(&mtrx1, &sp_mtrx1);
        if (rc == OK)
        {
            // if (percent == 1)
            // {
            //     printf("%zu\n", sp_mtrx1.len_a);
            //     size_t b = 0;
            //     b = sizeof(sp_mtrx1) + sp_mtrx1.len_a * sizeof(int) + sp_mtrx1.len_a * sizeof(int) + sp_mtrx1.cols * sizeof(int);
            //     printf("len_a - %zu\n", sp_mtrx1.len_a);
            //     printf("cols - %zu\n", sp_mtrx1.cols);
            //     printf("%zu\n", b);

            // }
            rc = standard_mtrx_to_sparse(&mtrx2, &sp_mtrx2);
            if (rc == OK)
            {
                rc = sp_mtrx_alloc(&sp_mtrx_res, sp_mtrx1.len_a + sp_mtrx2.len_a, sp_mtrx1.cols);
                if (rc == OK)
                {
                    rc = gettime_addition_sparse_mtrx(&sp_mtrx1, &sp_mtrx2, &sp_mtrx_res, t, len_t, &sp_time);
                    sp_mtrx_free(&sp_mtrx_res);
                }
                sp_mtrx_free(&sp_mtrx2);
            }
            // Обьем памяти
            sp_mtrx_bytes = count_sp_mtrx_bytes(&sp_mtrx1);
            if (st_mtrx_bytes >  sp_mtrx_bytes)
                percent_bytes = (int) round((st_mtrx_bytes - sp_mtrx_bytes) / (double) st_mtrx_bytes * 100);
            else
                percent_bytes = -(int) round((sp_mtrx_bytes - st_mtrx_bytes) / (double) sp_mtrx_bytes * 100);

            // if (percent == 1)
            //     printf("%zu\n", sp_mtrx1.len_a);
                // print_mtrx_sparse(&sp_mtrx1);
            //
            sp_mtrx_free(&sp_mtrx1);
        }
        if (rc != OK)
            goto ending_3;
        //

        // На столько процентов затрачено больше времени
        if (st_time >= sp_time)
            percent_time = (int) round((st_time - sp_time) / (double) st_time * 100);
        else 
            percent_time = - (int) round((sp_time - st_time) / (double) sp_time * 100);
        //

        // Печатаем таблицу
        printf("%d%%\t\t|%lld\t\t%lld\t\t%d%%\t\t|%zu\t%zu \t%d%%\n", percent, st_time, sp_time, percent_time, st_mtrx_bytes, sp_mtrx_bytes, percent_bytes);
    //
    }


    ending_3:
    free(t);
    ending_2:
    mtrx_free(mtrx_res.mtrx, mtrx_res.rows);
    ending_1:
    mtrx_free(mtrx2.mtrx, mtrx2.rows);
    ending_0:
    mtrx_free(mtrx1.mtrx, mtrx1.rows);

    return rc;
}

