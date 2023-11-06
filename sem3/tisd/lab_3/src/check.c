#include <stdlib.h>
#include <stdio.h>

#include "mtrx.h"
#include "errs.h"
#include "operations.h"
#include "in_output.h"


int check_addition(size_t rows, size_t cols, int percent1, int percent2, int *failed)
{
    struct standard_mtrx mtrx1, mtrx2, mtrx_res, sp_mtrx_res_in_st;
    struct sparse_mtrx sp_mtrx1, sp_mtrx2, sp_mtrx_res;
    int rc = OK;

    // Выделяем память под матрицы стандартного вида
    mtrx1.mtrx = mtrx_alloc(rows, cols);
    if (mtrx1.mtrx == NULL)
        return ERR_MEM;
    mtrx2.mtrx = mtrx_alloc(rows, cols);
    if (mtrx2.mtrx == NULL)
    {
        rc = ERR_MEM;
        goto ending_0;
    }
    mtrx_res.mtrx = mtrx_alloc(rows, cols);
    if (mtrx_res.mtrx == NULL)
    {
        rc = ERR_MEM;
        goto ending_1;
    }
    sp_mtrx_res_in_st.mtrx = mtrx_alloc(rows, cols);
    if (sp_mtrx_res_in_st.mtrx == NULL)
    {
        rc = ERR_MEM;
        goto ending_2;
    }
    mtrx1.rows = mtrx2.rows = mtrx_res.rows = sp_mtrx_res_in_st.rows = rows;
    mtrx1.cols = mtrx2.cols  = mtrx_res.cols = sp_mtrx_res_in_st.cols = cols;
    //

    // Заполнение матрицы 1
    input_mtrx_random(&mtrx1, percent1, percent1);
    //
    // Заполнение структуры разреженной матрицы 1 и выделение под нее памяти
    rc = standard_mtrx_to_sparse(&mtrx1, &sp_mtrx1);
    if (rc != OK)
        goto ending_3;
    //

    // Заполнение матрицы 2
    input_mtrx_random(&mtrx2, percent2, percent2 + 3000);
    //
    // Заполнение структуры разреженной матрицы 2 и выделение под нее памяти
    rc = standard_mtrx_to_sparse(&mtrx2, &sp_mtrx2);
    if (rc != OK)
        goto ending_4;
    //

    // Выделение памяти под результирующую структуру разреженной матрицы
    rc = sp_mtrx_alloc(&sp_mtrx_res, sp_mtrx1.len_a + sp_mtrx2.len_a, sp_mtrx1.cols);
    if (rc != OK)
        goto ending_5;
    //

    //Сложение матриц в сжатой форме
    rc = addition_sparse_mtrx(&sp_mtrx1, &sp_mtrx2, &sp_mtrx_res);
    if (rc != OK)
        goto ending_6;

    // Преобразование матрицы из сжатого вида в стандартный
    sparse_mtrx_to_standard(&sp_mtrx_res, &sp_mtrx_res_in_st);
    //

    // Сложение матриц в стандартном виде
    addition_standart_mtrx(&mtrx1, &mtrx2, &mtrx_res);
    //

    if (!cmp_mtrx(&mtrx_res, &sp_mtrx_res_in_st))
    {
        printf("ERROR\n");
        printf("%zu x %zu \t mtrx1 - %d%%\t mtrx22 - %d%%  - ok\n", rows, cols, percent1, percent2);
        printf("mtrx1\n");
        print_mtrx_standart(&mtrx1);
        printf("\n");
        printf("mtrx2\n");
        print_mtrx_standart(&mtrx2);
        printf("\n");
        (*failed)++;
    }
    else
        printf("%zu x %zu  %d%%  %d%%  - ok\n", rows, cols, percent1, percent2);


    ending_6:
    sp_mtrx_free(&sp_mtrx_res);
    ending_5:
    sp_mtrx_free(&sp_mtrx2);
    ending_4:
    sp_mtrx_free(&sp_mtrx1);
    ending_3:
    mtrx_free(sp_mtrx_res_in_st.mtrx, sp_mtrx_res_in_st.rows);
    ending_2:
    mtrx_free(mtrx_res.mtrx, mtrx_res.rows);
    ending_1:
    mtrx_free(mtrx2.mtrx, mtrx2.rows);
    ending_0:
    mtrx_free(mtrx1.mtrx, mtrx1.rows);
    return rc;
}



int check_main(void)
{
    int rc = OK;
    int failed = 0;
    size_t s[] = {1, 2, 3, 5, 10, 20, 100};
    size_t len_s = 7;
    size_t rows, cols;
    int p[] = {0, 1, 10, 25, 50, 75, 100};
    size_t len_p = 6;
    int perc1, perc2;

    for (size_t ri = 0; ri < len_s; ri++)
       for (size_t ci = 0; ci < len_s; ci++) 
            for (size_t p1i = 0; p1i < len_p; p1i++)
                for (size_t p2i = 0; p2i < len_p; p2i++)
                {
                    rows = s[ri];
                    cols = s[ci];
                    perc1 = p[p1i];
                    perc2 = p[p2i];
                    rc = check_addition(rows, cols, perc1, perc2, &failed);
                    if (rc != OK)
                        return rc;
                }
    printf("failed - %d\n", failed);
    return rc;
}

