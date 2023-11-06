#include <stdio.h>
#include <stdlib.h>

#include "mtrx.h"
#include "in_output.h"
#include "errs.h"
#include "interface.h"
#include "operations.h"
#include "actions.h"


int act_input_mtrx(struct standard_mtrx *mtrx)
{
    int act, rc = OK; 

    printf(TYPE_INPUT_MTRX, 1);
    char c;
    while (scanf("%d", &act) != 1 || !(act == STANDART_MTRX_INPUT || act == RANDOM_MTRX_INPUT) || (c = getchar()) != '\n')
    {
        print_err(ERR_NUM_ACT_INPUT);
        printf(TYPE_INPUT_MTRX, 1);
        
        c = getchar();
        while (c != '\n')
            c = getchar();
    }
    // getchar();

    if (act == STANDART_MTRX_INPUT)
        rc = input_mtrx_standard(mtrx);
    else
    {
        int perc;
        printf("Введите процент заполненности матрицы: ");
        if (scanf("%d", &perc) != 1)
            rc = ERR_IO;
        if (perc < 0 || perc > 100)
            rc = ERR_IO;
        
        if (rc == OK)
            input_mtrx_random(mtrx, perc, 0);
    }

    return rc;
}


int act_addition()
{
    struct standard_mtrx mtrx1, mtrx2, mtrx_res_st_sum, mtrx_res_sp_sum;
    struct sparse_mtrx sp_mtrx1, sp_mtrx2, sp_mtrx_res;
    size_t rows, cols;
    int rc = OK;

    // Вводим кол-во строк и столбцов в матрицах
    rc = input_rows_cols(&rows, &cols);
    if (rc != OK)
        return rc;
    mtrx1.rows = mtrx2.rows = rows;
    mtrx1.cols = mtrx2.cols = cols;
    //

    // Выделяем память под 1 и 2 матрицы
    mtrx1.mtrx = mtrx_alloc(rows, cols);
    if (mtrx1.mtrx == NULL)
        return ERR_MEM;
    printf("qwe\n");
    mtrx2.mtrx = mtrx_alloc(rows, cols);
    if (mtrx2.mtrx == NULL)
    {
        rc = ERR_MEM;
        goto ending_0;
    }
    //

    // Заполнение матрицы 1
    rc = act_input_mtrx(&mtrx1);
    if (rc != OK)
        goto ending_1;
    //
    // Вывод матрицы если она не превышает опредленный развмер для вывода
    if (rows <= MAX_ROW_COL_TO_PRINT && cols <= MAX_ROW_COL_TO_PRINT)
    {
        printf("Матрица 1:\n");
        print_mtrx_standart(&mtrx1);
        printf("\n");
    }
    //
    // Заполнение структуры разреженной матрицы 1 и выделение под нее памяти
    rc = standard_mtrx_to_sparse(&mtrx1, &sp_mtrx1);
    if (rc != OK)
        goto ending_1;
    printf("Сжатый формат матрицы 1: \n");
    print_mtrx_sparse(&sp_mtrx1);
    printf("\n");
    //

    // Заполнение матрицы 2
    rc = act_input_mtrx(&mtrx2);
    if (rc != OK)
        goto ending_2;
    //
    // Вывод матрицы если она не превышает опредленный размер для вывода
    if (rows <= MAX_ROW_COL_TO_PRINT && cols <= MAX_ROW_COL_TO_PRINT)
    {
        printf("Матрица 2:\n");
        print_mtrx_standart(&mtrx2);
        printf("\n");
    }
    //
    // Заполнение структуры разреженной матрицы 2 и выделение под нее памяти
    rc = standard_mtrx_to_sparse(&mtrx2, &sp_mtrx2);
    if (rc != OK)
        goto ending_2;
    printf("Сжатый формат матрицы 2: \n");
    print_mtrx_sparse(&sp_mtrx2);
    printf("\n");
    //


    // Выделение памяти под результирующую структуру разреженной матрицы
    rc = sp_mtrx_alloc(&sp_mtrx_res, sp_mtrx1.len_a + sp_mtrx2.len_a, sp_mtrx1.cols);
    if (rc != OK)
        goto ending_3;
    //
    //Сложение матриц в сжатой форме
    rc = addition_sparse_mtrx(&sp_mtrx1, &sp_mtrx2, &sp_mtrx_res);
    if (rc != OK)
        goto ending_4;
    
    printf("Сжатый формат матрицы суммы: \n");
    print_mtrx_sparse(&sp_mtrx_res);
    printf("\n");
    //

    // Преобразование матрицы из сжатого вида в стандартный
    mtrx_res_st_sum.mtrx = mtrx_alloc(rows, cols);
    mtrx_res_st_sum.rows = rows;
    mtrx_res_st_sum.cols = cols;
    if (mtrx_res_st_sum.mtrx == NULL)
        goto ending_4;
    sparse_mtrx_to_standard(&sp_mtrx_res, &mtrx_res_st_sum);
    //
    // Вывод матрицы если она не превышает опредленный размер для вывода
    if (rows <= MAX_ROW_COL_TO_PRINT && cols <= MAX_ROW_COL_TO_PRINT)
    {
        printf("Матрица суммы:\n");
        print_mtrx_standart(&mtrx_res_st_sum);
        printf("\n");
    }
    //

    // Сравнение матриц получившихся в результате сложения обычных матриц и сжатых
    mtrx_res_sp_sum.mtrx = mtrx_alloc(rows, cols);
    mtrx_res_sp_sum.rows = rows;
    mtrx_res_sp_sum.cols = cols;
    if (mtrx_res_st_sum.mtrx == NULL)
        goto ending_5;
    addition_standart_mtrx(&mtrx1, &mtrx2, &mtrx_res_sp_sum);

    if (cmp_mtrx(&mtrx_res_st_sum, &mtrx_res_sp_sum))
        printf("OK: результат сложения матриц в сжатом виде и в обычном одинаковый \n");
    else
        printf("ERROR: результат сложения матриц в сжатом виде и в обычном разный! \n");
    //



    mtrx_free(mtrx_res_sp_sum.mtrx, rows);

    ending_5:
    mtrx_free(mtrx_res_st_sum.mtrx, rows);
    
    ending_4:
    sp_mtrx_free(&sp_mtrx_res);

    ending_3:
    sp_mtrx_free(&sp_mtrx2);

    ending_2:
    sp_mtrx_free(&sp_mtrx1);

    ending_1:
    mtrx_free(mtrx2.mtrx, rows);
    ending_0:
    mtrx_free(mtrx1.mtrx, rows);

    return rc;
}

