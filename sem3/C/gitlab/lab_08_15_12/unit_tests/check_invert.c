#include <stdlib.h>
#include <check.h>
#include <assert.h>

#include "inits.h"
#include "errs.h"
#include "operations.h"
#include "alloc_mtrx.h"

#include <stdio.h>

    // for (size_t i = 0; i < rows; i++)
    // {
    //     for (size_t j = 0; j < cols; j++)
    //         printf(" %lf", exp_mtrx_res.data[i][j]);
    //     printf("\n");
    // }

/// @brief Матрица 3х3 (без нулевых элементов)
START_TEST(test_invert_3x3_no_zero_elems)
{
    int rc = OK;
    size_t rows = 3, cols = 3;
    struct mtrx_t mtrx_res, emtrx;

    double smtrx1[ROWS][COLS] = 
    {
        {2, -1, 0},
        {0, 2, -1},
        {-1, -1, 1}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {1, 1, 1},
        {1, 2, 2},
        {2, 3, 4}
    };

    double *data1[] = {smtrx1[0], smtrx1[1], smtrx1[2]};
    struct mtrx_t mtrx1 = {data1, 3, 3};
    // rc = static_to_dynamic_mtrx(smtrx1, rows, cols, &mtrx1);
    // assert(rc == OK);

    rc = invert(&mtrx1, &mtrx_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, rows);
    ck_assert_int_eq(mtrx_res.cols, cols);

    double *data_res[] = {smtrx_res[0], smtrx_res[1], smtrx_res[2]};
    struct mtrx_t exp_mtrx_res = {data_res, 3, 3};
    //rc = static_to_dynamic_mtrx(smtrx_res, rows, cols, &exp_mtrx_res);
    //assert(rc == OK);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    // Доп проверка умножением
    rc = multiplication(&mtrx1, &mtrx_res, &emtrx);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(if_mtrx_e(&emtrx), 0);
    //

    // free_mtrx(&mtrx1);
    free_mtrx(&mtrx_res);
    // free_mtrx(&exp_mtrx_res);
    free_mtrx(&emtrx);
}
END_TEST


/// @brief Матрица 1х1
START_TEST(test_invert_1x1)
{
    int rc = OK;
    size_t rows = 1, cols = 1;
    struct mtrx_t mtrx_res, emtrx;

    double smtrx1[ROWS][COLS] = 
    {
        {1}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {1}
    };

    double *data1[] = {smtrx1[0]};
    struct mtrx_t mtrx1 = {data1, 1, 1};
    // rc = static_to_dynamic_mtrx(smtrx1, rows, cols, &mtrx1);
    // assert(rc == OK);

    rc = invert(&mtrx1, &mtrx_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, rows);
    ck_assert_int_eq(mtrx_res.cols, cols);
    double *data_res[] = {smtrx_res[0]};
    struct mtrx_t exp_mtrx_res = {data_res, 1, 1};
    //rc = static_to_dynamic_mtrx(smtrx_res, rows, cols, &exp_mtrx_res);
    //assert(rc == OK);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    // Доп проверка умножением
    rc = multiplication(&mtrx1, &mtrx_res, &emtrx);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(if_mtrx_e(&emtrx), 0);
    //

    //free_mtrx(&mtrx1);
    free_mtrx(&mtrx_res);
    //free_mtrx(&exp_mtrx_res);
    free_mtrx(&emtrx);
}
END_TEST

/// @brief Матрица где на главной диагонали есть нули и надо переставлять строки
START_TEST(test_invert_to_change_rows)
{
    int rc = OK;
    size_t rows = 2, cols = 2;
    struct mtrx_t mtrx_res, emtrx;

    double smtrx1[ROWS][COLS] = 
    {
        {0, 1},
        {1, 0}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {0, 1},
        {1, 0}
    };

    double *data1[] = {smtrx1[0], smtrx1[1]};
    struct mtrx_t mtrx1 = {data1, 2, 2};
    double *data_res[] = {smtrx_res[0], smtrx_res[1]};
    struct mtrx_t exp_mtrx_res = {data_res, 2, 2};
    // rc = static_to_dynamic_mtrx(smtrx1, rows, cols, &mtrx1);
    // assert(rc == OK);

    rc = invert(&mtrx1, &mtrx_res);
    
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, rows);
    ck_assert_int_eq(mtrx_res.cols, cols);
    //rc = static_to_dynamic_mtrx(smtrx_res, rows, cols, &exp_mtrx_res);
    //assert(rc == OK);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    // Доп проверка умножением
    rc = multiplication(&mtrx1, &mtrx_res, &emtrx);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(if_mtrx_e(&emtrx), 0);
    //

    //free_mtrx(&mtrx1);
    free_mtrx(&mtrx_res);
    //free_mtrx(&exp_mtrx_res);
    free_mtrx(&emtrx);
}
END_TEST





Suite* invert_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("invert");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_invert_3x3_no_zero_elems);
    tcase_add_test(tc_pos, test_invert_1x1);
    tcase_add_test(tc_pos, test_invert_to_change_rows);

    tc_neg = tcase_create("negatives");
    // tcase_add_test(tc_neg, test_addition_neg_diff_size_mtrxs);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}














