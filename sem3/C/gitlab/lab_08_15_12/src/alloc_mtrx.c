#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <assert.h>

#include "alloc_mtrx.h"
#include "errs.h"

// // защита, обьединеннный подход 1
// double *find_pmin(struct mtrx_t *mtrx)
// {
//     double *pmin = mtrx->data[0];
//     for (size_t i = 1; i < mtrx->rows; i++)
//         if (mtrx->data[i] < pmin)
//             pmin = mtrx->data[i];
//     return pmin;
// }

// // защита, обьединеннный подход 1
// void free_mtrx(struct mtrx_t *mtrx)
// {
//     free(find_pmin(mtrx));
//     free(mtrx->data);
//     mtrx->rows = mtrx->cols = 0;
// }

// // защита, обьединеннный подход 1
// void alloc_mtrx_data(struct mtrx_t *mtrx, size_t rows, size_t cols)
// {
//     double **pdata, *data;

//     pdata = malloc(rows * sizeof(double *));
//     if (pdata == NULL)
//     {
//         mtrx->rows = mtrx->cols = 0;
//         return;
//     }
    
//     data = malloc(rows * cols * sizeof(double));
//     if (data == NULL)
//     {
//         free(pdata);
//         mtrx->rows = mtrx->cols = 0;
//         return;
//     }

//     for (size_t i = 0; i < rows; i++)
//         pdata[i] = data + i * cols;

//     mtrx->data = pdata;
//     mtrx->rows = rows;
//     mtrx->cols = cols;
// }

// комментируем для защиты
void free_mtrx(struct mtrx_t *mtrx)
{
    free(mtrx->data);
    mtrx->rows = mtrx->cols = 0;
}

// комментируем для защиты
int alloc_mtrx_data(struct mtrx_t *mtrx, size_t rows, size_t cols)
{
    mtrx->rows = rows;
    mtrx->cols = cols;
    mtrx->data = malloc(rows * sizeof(double *) + rows * cols * sizeof(double));
    if (mtrx->data == NULL)
    {
        mtrx->rows = mtrx->cols = 0;
        return ERR_MEM;
    }
    double *elems = (double *) (mtrx->data + mtrx->rows);
    for (size_t i = 0; i < mtrx->rows; i++)
        mtrx->data[i] = elems + i * mtrx->cols;
    
    return OK;
}

int copy_mtrx(struct mtrx_t *dst, struct mtrx_t *src)
{
    int rc = alloc_mtrx_data(dst, src->rows, src->cols);
    if (rc != OK)
        return rc;

    // memmove(&dst->data[0], &src->data[0], src->rows * src->cols * sizeof(double));
    dst->rows = src->rows;
    dst->cols = src->cols;

    for (size_t i = 0; i < dst->rows; i++)
        for (size_t j = 0; j < dst->cols; j++)
            dst->data[i][j] = src->data[i][j];
    
    return OK;
}

// int static_to_dynamic_mtrx(double src[][COLS], size_t rows, size_t cols, struct mtrx_t *dst)
// {
//     int rc = alloc_mtrx_data(dst, rows, cols);
//     if (rc != OK)
//         return rc;

//     for (size_t i = 0; i < rows; i++)
//     {
//         dst->data[i] = &src[i][0];
//         // memmove(dst->data[i], &src[i], sizeof(double) * cols);
//     }

//     // for (size_t i = 0; i < rows; i++)
//     //     for (size_t j = 0; j < cols; j++)
//     //         dst->data[i][j] = src[i][j];

//     return OK;
// }

int static_to_dynamic_mtrx(double src[][COLS], size_t rows, size_t cols, struct mtrx_t *dst)
{
    assert(rows <= ROWS && cols <= COLS);

    // Выделяем память под массив указателей на статические строки
    dst->rows = rows;
    dst->cols = cols;
    dst->data = malloc(sizeof(double *) * rows);
    if (dst->data == NULL)
        return ERR_MEM;
    //

    for (size_t i = 0; i < rows; i++)
        dst->data[i] = &src[i][0];

    return OK;
}



