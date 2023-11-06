#include <stddef.h>
#include <assert.h>

#include "operations.h"
#include "mtrx.h"
#include "errs.h"


#include <stdio.h>

void addition_standart_mtrx(struct standard_mtrx *mtrx1, struct standard_mtrx *mtrx2, struct standard_mtrx *out_mtrx)
{
    assert((mtrx1->rows == mtrx2->rows) && (mtrx1->cols == mtrx2->cols));
    assert((mtrx1->rows == out_mtrx->rows) && (mtrx1->cols == out_mtrx->cols));

    for (size_t i = 0; i < mtrx1->rows; i++)
        for (size_t j = 0; j < mtrx1->cols; j++)
            out_mtrx->mtrx[i][j] = mtrx1->mtrx[i][j] + mtrx2->mtrx[i][j];
}

size_t find_end_col(struct sparse_mtrx *mtrx, size_t j)
{
    size_t end_col;
    size_t ind_end_col = j + 1;

    while (ind_end_col < mtrx->cols && mtrx->ja[ind_end_col] == -1)
        ind_end_col++;
    if (ind_end_col >= mtrx->cols)
        end_col = mtrx->len_a;
    else
        end_col = mtrx->ja[ind_end_col];
    
    // printf("INDD: %zu %zu\n", j, end_col);
    
    return end_col;
}

int addition_sparse_mtrx(struct sparse_mtrx *mtrx1, struct sparse_mtrx *mtrx2, struct sparse_mtrx *out_mtrx)
{
    assert((mtrx1->rows == mtrx2->rows) && (mtrx1->cols == mtrx2->cols));

    int *a = NULL;
    size_t *ia = NULL;
    int *ja = NULL;
    size_t len_a_ia = 0;
    int rc = OK;

    // Выделяем память под части структуры разреженной матрицы out_mtrx - которая получится в результате сложения
    rc = alloc_tmp_max_size_sp_mtrx_parts(mtrx1->rows, mtrx1->cols, &a, &ia, &ja);
    if (rc != OK)
        return rc;

    for (size_t j = 0; j < mtrx1->cols; j++)
    {
        if (mtrx1->ja[j] == -1 && mtrx2->ja[j] == -1)
            ja[j] = -1;
        else if (mtrx1->ja[j] == -1)
        {
            size_t end_col = find_end_col(mtrx2, j);

            // ja[j] = mtrx2->ja[j];
            ja[j] = len_a_ia;
            for (size_t i = mtrx2->ja[j]; i < end_col; i++)
            {
                ia[len_a_ia] = mtrx2->ia[i];
                a[len_a_ia] = mtrx2->a[i];
                len_a_ia++;
            }
        }
        else if (mtrx2->ja[j] == -1)
        {
            size_t end_col = find_end_col(mtrx1, j);

            // ja[j] = mtrx1->ja[j];
            ja[j] = len_a_ia;
            for (size_t i = mtrx1->ja[j]; i < end_col; i++)
            {
                ia[len_a_ia] = mtrx1->ia[i];
                a[len_a_ia] = mtrx1->a[i];
                len_a_ia++;
            }
        }
        else
        {
            size_t i1 = mtrx1->ja[j], i2 = mtrx2->ja[j]; // индексы в массиве a ia
            size_t end_col_1, end_col_2;
            end_col_1 = find_end_col(mtrx1, j);
            end_col_2 = find_end_col(mtrx2, j);

            // printf("INDDDDD: %zu %zu\n", i1, end_col_1);
            // printf("INDDDDD: %zu %zu\n", i2, end_col_2);

            // ja[j] = mtrx1->ia[i1] < mtrx2->ia[i2] ? i1 : i2;
            ja[j] = len_a_ia;
            // printf("MTRXXXX: %zu %zu\n", mtrx1->ia[i1], mtrx2->ia[i2]);
            // printf("JA:   %d\n", ja[j]);

            while (i1 < end_col_1 && i2 < end_col_2)
            {
                if (mtrx1->ia[i1] < mtrx2->ia[i2])
                {
                    ia[len_a_ia] = mtrx1->ia[i1];
                    a[len_a_ia] = mtrx1->a[i1];
                    len_a_ia++;
                    i1++;
                }
                else if (mtrx1->ia[i1] > mtrx2->ia[i2])
                {
                    ia[len_a_ia] = mtrx2->ia[i2];
                    a[len_a_ia] = mtrx2->a[i2];
                    len_a_ia++;
                    i2++;
                }
                else
                {
                    if (mtrx1->a[i1] + mtrx2->a[i2] != 0)
                    {
                        ia[len_a_ia] = mtrx1->ia[i1];
                        a[len_a_ia] = mtrx1->a[i1] + mtrx2->a[i2];
                        len_a_ia++;
                    }
                    i1++;
                    i2++;
                }
            }
            while (i1 < end_col_1)
            {
                ia[len_a_ia] = mtrx1->ia[i1];
                a[len_a_ia] = mtrx1->a[i1];
                len_a_ia++;
                i1++;
            }
            while (i2 < end_col_2)
            {
                ia[len_a_ia] = mtrx2->ia[i2];
                a[len_a_ia] = mtrx2->a[i2];
                len_a_ia++;
                i2++;
            }
        }
    }
    
    sp_mtrx_full_on_tmp_parts(out_mtrx, a, ia, ja, len_a_ia, mtrx1->rows, mtrx1->cols);

    free(a);
    free(ia);
    free(ja);
    return OK;
}

_Bool cmp_mtrx(struct standard_mtrx *mtrx1, struct standard_mtrx *mtrx2)
{
    if (mtrx1->rows != mtrx2->rows || mtrx1->cols != mtrx2->cols)
        return 0;
    
    _Bool same = 1;
    for (size_t i = 0; i < mtrx1->rows; i++)
        for  (size_t j = 0; j < mtrx1->cols; j++)
            if (mtrx1->mtrx[i][j] != mtrx2->mtrx[i][j])
                same = 0;
    return same;
}
