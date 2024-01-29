#include <stddef.h>
#include <assert.h>
#include <math.h>

#include "inits.h"
#include "errs.h"
#include "alloc_mtrx.h"

#include <stdio.h>
#include "in_output.h"

int addition(struct mtrx_t *mtrx1, struct mtrx_t *mtrx2, struct mtrx_t *mtrx_res)
{
    if (!(mtrx1->rows == mtrx2->rows && mtrx1->cols == mtrx2->cols))
        return ERR_SIZE_MTRX;

    // Выделяем память под результирующую матрицу
    int rc = alloc_mtrx_data(mtrx_res, mtrx1->rows, mtrx1->cols);
    if (rc != OK)
        return rc;
    //

    // Производим операцию сложения
    for (size_t i = 0; i < mtrx1->rows; i++)
        for (size_t j = 0; j < mtrx1->cols; j++)
            mtrx_res->data[i][j] = mtrx1->data[i][j] + mtrx2->data[i][j];
    //

    return OK;
}

int multiplication(struct mtrx_t *mtrx1, struct mtrx_t *mtrx2, struct mtrx_t *mtrx_res)
{
    if (!(mtrx1->cols == mtrx2->rows))
        return ERR_SIZE_MTRX;

    double elem_new;

    // Выделяем память под результирующую матрицу
    int rc = alloc_mtrx_data(mtrx_res, mtrx1->rows, mtrx2->cols);
    if (rc != OK)
        return rc;
    //

    // Производим операцию умножения
    for (size_t i = 0; i < mtrx1->rows; i++)
        for (size_t j = 0; j < mtrx2->cols; j++)
        {
            elem_new = 0.0;
            for (size_t k = 0; k < mtrx1->cols; k++)
                elem_new += mtrx1->data[i][k] * mtrx2->data[k][j];
            mtrx_res->data[i][j] = elem_new;
        }
    //

    return OK;
}

void make_nonzero_diadonal_el(struct mtrx_t *mtrx1, struct mtrx_t *mtrx2, size_t id)
{
    assert(mtrx1->rows == mtrx1->cols && mtrx2->rows == mtrx2->cols && mtrx1->rows == mtrx2->cols);

    size_t ind_max_el = id;

    for (size_t i = 1; i < mtrx1->rows; i++)
        if (fabs(mtrx1->data[i][id]) > fabs(mtrx1->data[ind_max_el][id]))
            ind_max_el = i;

    if (ind_max_el != id)
    {
        // printf("[%zu %zu] [%zu %zu] %lf > %lf\n", id, id, ind_max_el, id, mtrx1->data[id][id], mtrx1->data[ind_max_el][id]);
        double *tmp = mtrx1->data[id];
        mtrx1->data[id] = mtrx1->data[ind_max_el];
        mtrx1->data[ind_max_el] = tmp;

        tmp = mtrx2->data[id];
        mtrx2->data[id] = mtrx2->data[ind_max_el];
        mtrx2->data[ind_max_el] = tmp; 
    }
}

void fill_id_1(struct mtrx_t *mtrx_res)
{
    assert(mtrx_res->rows == mtrx_res->cols);
    size_t n = mtrx_res->rows;

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
        {
            if (i == j)
                mtrx_res->data[i][j] = 1.0;
            else
                mtrx_res->data[i][j] = 0.0;
        }
}

// void rows_to_normal(struct mtrx_t *mtrx)
// {
//     int swapped = 1;
//     for (size_t i = 0; i < mtrx->rows - 1 && swapped; i++)
//         for (size_t j = 0; j < mtrx->rows - 1 - i && swapped; j++)
//         {
//             swapped = 0;
//             if (&mtrx->data[j] > &mtrx->data[j + 1])
//             {
//                 double *tmp = mtrx->data[j];
//                 mtrx->data[j] = mtrx->data[j + 1];
//                 mtrx->data[j + 1] = tmp;
//                 swapped = 1;
//             }
//         }
// }

int invert(struct mtrx_t *mtrx1, struct mtrx_t *mtrx_res)
{
    int rc = OK;

    if (!(mtrx1->rows == mtrx1->cols))
        return ERR_SIZE_MTRX;

    size_t n = mtrx1->rows;

    // Создает копию матрицы 1 и выделяет память под эту копию
    struct mtrx_t mtrx;
    rc = copy_mtrx(&mtrx, mtrx1); 
    if (rc != OK)
        return rc;
    //

    // print_mtrx_standart(mtrx1);
    // print_mtrx_standart(&mtrx);

    // Выделяем память под результирующую матрицу
    rc = alloc_mtrx_data(mtrx_res, n, n);
    if (rc != OK)
        return rc;
    //

    // Заполняем диагональ единицами а ост нулями
    fill_id_1(mtrx_res);
    //

    double k;
    // прямой ход
    for (size_t id = 0; n > 0 && id < n - 1; id++)
    {
        make_nonzero_diadonal_el(&mtrx, mtrx_res, id);
        // printf("changed\n");
        // print_mtrx_standart(&mtrx);
        for (size_t i = id + 1; i < n && rc == OK; i++)
        {
            if (fabs(mtrx.data[id][id]) < EPS)
                rc = ERR_ZERO_DET;
            k = mtrx.data[i][id] / mtrx.data[id][id];
            for (size_t j = 0; j < n && rc == OK; j++)
            {
                mtrx.data[i][j] -= k * mtrx.data[id][j];
                mtrx_res->data[i][j] -= k * mtrx_res->data[id][j];
            }
        }
    }
    //
    // printf("\nпрямой ход\n");
    // print_mtrx_standart(&mtrx);
    // print_mtrx_standart(mtrx_res);
    // printf("\n");

    // обратный ход
    for (int id = n - 1; id > 0 && rc == OK; id--)
    {
        // // make_nonzero_diadonal_el(&mtrx, mtrx_res, id); 
        // printf("changed\n");
        // print_mtrx_standart(&mtrx);
        for (int i = id - 1; i >= 0 && rc == OK; i--)
        {
            if (fabs(mtrx.data[id][id]) < EPS)
                rc = ERR_ZERO_DET;
            k = mtrx.data[i][id] / mtrx.data[id][id];
            for (size_t j = 0; j < n; j++)
            {
                mtrx.data[i][j] -= k * mtrx.data[id][j];
                mtrx_res->data[i][j] -= k * mtrx_res->data[id][j];
            }
        }
    }
    //
    // printf("\nобратный ход\n");
    // print_mtrx_standart(&mtrx);
    // print_mtrx_standart(mtrx_res);
    // printf("\n");

    // Приводим строки матрицы в изначальное состояние (сортируем строки по указутелю)
    // rows_to_normal(mtrx_res);
    //

    // printf("\nперестановка в норму\n");
    // print_mtrx_standart(&mtrx);
    // print_mtrx_standart(mtrx_res);
    // printf("\n");

    // Доводим диагональ до единиц
    for (size_t i = 0; i < n && rc == OK; i++)
    {
        k = mtrx.data[i][i];
        // Проверка что матрица не вырождена
        if (fabs(k) < EPS)  
        {
            rc = ERR_ZERO_DET;
        }
        else
            for (size_t j = 0; j < n; j++)
            {
                mtrx.data[i][j] /= k;
                mtrx_res->data[i][j] /= k;
            }
    }
    //

    if (rc != OK)
        free_mtrx(mtrx_res);

    free_mtrx(&mtrx);

    // print_mtrx_standart(mtrx1);

    return rc;
}


int compare_mtrxs(struct mtrx_t *l_mtrx1, struct mtrx_t *r_mtrx)
{
    const int equal = 0, diff = 1;

    if (l_mtrx1->rows != r_mtrx->rows || l_mtrx1->cols != r_mtrx->cols)
        return diff;
    
    size_t rows = l_mtrx1->rows, cols = l_mtrx1->cols;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            if (l_mtrx1->data[i][j] - r_mtrx->data[i][j] >= EPS)
                return diff;
    
    return equal;
}


int if_mtrx_e(struct mtrx_t *mtrx)
{
    int rc;

    struct mtrx_t emtrx;
    rc = alloc_mtrx_data(&emtrx, mtrx->rows, mtrx->cols);
    if (rc != OK)
        return rc;
    fill_id_1(&emtrx);

    rc = compare_mtrxs(mtrx, &emtrx);
    free_mtrx(&emtrx);

    return rc;
}

