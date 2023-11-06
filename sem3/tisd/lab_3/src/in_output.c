#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "in_output.h"
#include "mtrx.h"
#include "errs.h"
#include "interface.h"


int input_rows_cols(size_t *rows, size_t *cols)
{
    int r, c;

    printf("Введите количество строк и столбцов в матрице: ");
    if (scanf("%d%d", &r, &c) != 2)
        return ERR_IO;
    if (r <= 0 || c <= 0)
        return ERR_IO;
    
    *rows = r;
    *cols = c;

    return OK;
}


int input_mtrx_standard(struct standard_mtrx *mtrx)
{
    int count, el, k;
    size_t i, j;
    printf("Введите количество ненулевых элементов матрицы целых чисел: ");
    if (scanf("%d", &count) != 1)
        return ERR_IO;
    if (count < 0)
        return ERR_IO;
    printf("Введите индексы ненулевого элемента, затем сам элемент, например: \n");
    printf("0 0 1 - элемента в индексами [0, 0] имеент значение 1\n");
    
    k = 0;
    while (k < count)
    {
        if (scanf("%zu", &i) != 1)
            return ERR_IO;
        if (i >= mtrx->rows)
            return ERR_RANGE;
        if (scanf("%zu", &j) != 1)
            return ERR_IO;
        if (j >= mtrx->cols)
            return ERR_RANGE;
        if (scanf("%d", &el) != 1)
            return ERR_IO;
        if (el == 0)
            printf("Ненулевой элемент не может равняться 0\n");
        else if (mtrx->mtrx[i][j] != 0)
        {
            printf("Элемент перезаписан\n");
            mtrx->mtrx[i][j] = el;
        }
        else
        {
            mtrx->mtrx[i][j] = el;
            k++;
        }
    }
    // printf("Введите матрицу целых чисел:\n");
    // for (size_t i = 0; i < mtrx->rows; i++)
    //     for (size_t j = 0; j < mtrx->cols; j++)
    //     {
    //         printf("[%zu, %zu]: ", i, j);
    //         if(scanf("%d", &mtrx->mtrx[i][j]) != 1)
    //             return ERR_IO;
    //     }   
    return OK;
}

void full_mtrx_zero(struct standard_mtrx *mtrx)
{
    for (size_t i = 0; i < mtrx->rows; i++)
        for (size_t j = 0; j < mtrx->cols; j++)
            mtrx->mtrx[i][j] = 0;
}

void input_mtrx_random(struct standard_mtrx *mtrx, int perc, unsigned int num)
{
    int count_signf, now_signf = 0;
    int i, j;

    full_mtrx_zero(mtrx);
    
    count_signf = (int) round((perc * mtrx->rows * mtrx->cols) / 100.0);

    srand(time(NULL) + num);
    while (now_signf < count_signf)
    {
        i = rand() % mtrx->rows;
        j = rand() % mtrx->cols;
        if (mtrx->mtrx[i][j] == 0)
        {
            mtrx->mtrx[i][j] = 1 + rand() % 100;
            now_signf++;
        }
    }
}

void print_mtrx_standart(struct standard_mtrx *mtrx)
{
    for (size_t i = 0; i < mtrx->rows; i++)
    {
        for (size_t j = 0; j < mtrx->cols; j++)
            printf("%5d ", mtrx->mtrx[i][j]);
        printf("\n");
    }
}

void print_mtrx_sparse(struct sparse_mtrx *sp_mtrx)
{
    if (sp_mtrx->len_a == 0)
    {
        printf("Матрица состоит только из 0\n");
        return;
    }
    
    printf("A:  ");
    for (size_t i = 0; i < sp_mtrx->len_a; i++)
        printf("%5d", sp_mtrx->a[i]);
    printf("\n");

    printf("IA: ");
    for (size_t i = 0; i < sp_mtrx->len_a; i++)
        printf("%5d", sp_mtrx->ia[i]);
    printf("\n");

    printf("JA: ");
    for (size_t i = 0; i < sp_mtrx->cols; i++)
        printf("%5d", sp_mtrx->ja[i]);
    printf("\n");
}




