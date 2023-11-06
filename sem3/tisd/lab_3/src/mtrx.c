#include <stdlib.h>

#include "mtrx.h"
#include "errs.h"
#include "in_output.h"
#include "operations.h"


#include <stdio.h>

void mtrx_free(int **data, size_t len_data)
{
    for (size_t i = 0; i < len_data; i++)
        free(data[i]);
    free(data);
}

int **mtrx_alloc(size_t rows, size_t cols)
{
    int **data = calloc(rows, sizeof(int *));

    if (data == NULL)
        return NULL;

    for (size_t i = 0; i < rows; i++)
    {
        data[i] = calloc(cols, sizeof(int));
        // printf("%zu\n", i);
        if (data[i] == NULL)
        {
            mtrx_free(data, rows);
            return NULL;
        }
    }
    return data;
}

void sp_mtrx_free(struct sparse_mtrx *sp_mtrx)
{
    free(sp_mtrx->a);
    free(sp_mtrx->ia);
    free(sp_mtrx->ja);
}

int sp_mtrx_alloc(struct sparse_mtrx *sp_mtrx, size_t len_a_ia, size_t len_ja)
{
    sp_mtrx->a = malloc(len_a_ia * sizeof(int));
    if (sp_mtrx->a == NULL)
        return ERR_MEM;
    sp_mtrx->ia = malloc(len_a_ia * sizeof(size_t));
    if (sp_mtrx->ia == NULL)
    {
        free(sp_mtrx->a);
        return ERR_MEM;
    }
    sp_mtrx->ja = malloc(len_ja * sizeof(int));
    if (sp_mtrx->ja == NULL)
    {
        free(sp_mtrx->a);
        free(sp_mtrx->ia);
        return ERR_MEM;
    }

    return OK;
}

void sp_mtrx_full_on_tmp_parts(struct sparse_mtrx *sp_mtrx, int *a, size_t *ia, int *ja, size_t len_a_ia, size_t rows, size_t cols)
{
    for (size_t i = 0; i < len_a_ia; i++)
    {
        sp_mtrx->a[i] = a[i];
        sp_mtrx->ia[i] = ia[i];
    }
    for (size_t j = 0; j < cols; j++)
        sp_mtrx->ja[j] = ja[j];
    sp_mtrx->len_a = len_a_ia;
    sp_mtrx->rows = rows;
    sp_mtrx->cols = cols;
}

int alloc_tmp_max_size_sp_mtrx_parts(size_t rows, size_t cols, int **a, size_t **ia, int **ja)
{
    *a = malloc(rows * cols * sizeof(int));
    if (*a == NULL)
        return ERR_MEM;
    *ia = malloc(rows * cols * sizeof(size_t));
    if (*ia == NULL)
    {
        free(*a);
        return ERR_MEM;
    }
    *ja = malloc(cols * sizeof(int));
    if (*ja == NULL)
    {
        free(*a);
        free(*ia);
        return ERR_MEM;
    }

    return OK;
}

void full_tmp_max_size_sp_mtrx_parts(struct standard_mtrx *mtrx, int *a, size_t *ia, int *ja, size_t *len_a_ia)
{
    *len_a_ia = 0;

    for (size_t j = 0; j < mtrx->cols; j++)
    {
        ja[j] = -1;
        for (size_t i = 0; i < mtrx->rows; i++)
            if (mtrx->mtrx[i][j] != 0)
            {
                a[*len_a_ia] = mtrx->mtrx[i][j];
                ia[*len_a_ia] = i;

                if (ja[j] == -1)
                    ja[j] = *len_a_ia;

                (*len_a_ia)++;
            }
    }
}

int standard_mtrx_to_sparse(struct standard_mtrx *mtrx, struct sparse_mtrx *sp_mtrx)
{
    int *a = NULL;
    size_t *ia = NULL;
    int *ja = NULL;
    size_t len_a_ia;
    int rc = OK;

    // выделение памяти под временные массивы
    rc = alloc_tmp_max_size_sp_mtrx_parts(mtrx->rows, mtrx->cols, &a, &ia, &ja);
    if (rc != OK)
        return rc;

    // заполнение временных массивов
    full_tmp_max_size_sp_mtrx_parts(mtrx, a, ia, ja, &len_a_ia);

    // выделение памяти под элементы структуры
    rc = sp_mtrx_alloc(sp_mtrx, len_a_ia, mtrx->cols);
    if (rc != OK)
        return rc;

    // заполнение элементов структуры
    sp_mtrx_full_on_tmp_parts(sp_mtrx, a, ia, ja, len_a_ia, mtrx->rows, mtrx->cols);


    free(a);
    free(ia);
    free(ja);
    return OK;
}


void sparse_mtrx_to_standard(struct sparse_mtrx *sp_mtrx, struct standard_mtrx *mtrx)
{
    full_mtrx_zero(mtrx);

    size_t end_col;
    for (size_t j = 0; j < sp_mtrx->cols; j++)
    {
        end_col = find_end_col(sp_mtrx, j);
        for (size_t i = sp_mtrx->ja[j]; i < end_col; i++)
        {
            // printf("QQQQQQQQQQQQ: %zu\n", sp_mtrx->ia[i]);
            mtrx->mtrx[sp_mtrx->ia[i]][j] = sp_mtrx->a[i];
        }
    }

    mtrx->rows = sp_mtrx->rows;
    mtrx->cols = sp_mtrx->cols;
}
