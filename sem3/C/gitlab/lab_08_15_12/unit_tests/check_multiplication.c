#include <stdlib.h>
#include <check.h>
#include <assert.h>

#include "inits.h"
#include "errs.h"
#include "operations.h"
#include "alloc_mtrx.h"


/// @brief Умножение матриц состоящих из ненулевых элементов и нулевых элементов (строк в матрице 1 < столбцов в матрице 2)
START_TEST(test_multiplication_rows1_lt_cols2)
{
    int rc = OK;
    struct mtrx_t mtrx1, mtrx2, exp_mtrx_res, mtrx_res;

    double smtrx1[ROWS][COLS] = 
    {
        {1, 3},
        {0, 2}
    };
    double smtrx2[ROWS][COLS] = 
    {
        {1, 0, 1},
        {8, 9, 2}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {25, 27, 7},
        {16, 18, 4}
    };

    rc = static_to_dynamic_mtrx(smtrx1, 2, 2, &mtrx1);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx2, 2, 3, &mtrx2);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx_res, 2, 3, &exp_mtrx_res);
    assert(rc == OK);

    rc = multiplication(&mtrx1, &mtrx2, &mtrx_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, 2);
    ck_assert_int_eq(mtrx_res.cols, 3);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    free_mtrx(&mtrx1);
    free_mtrx(&mtrx2);
    free_mtrx(&exp_mtrx_res);
    free_mtrx(&mtrx_res);
}
END_TEST

/// @brief Умножение матриц состоящих из ненулевых элементов и нулевых элементов (строк в матрице 1 > столбцов в матрице 2)
START_TEST(test_multiplication_rows1_gt_cols2)
{
    int rc = OK;
    struct mtrx_t mtrx1, mtrx2, exp_mtrx_res, mtrx_res;

    double smtrx1[ROWS][COLS] = 
    {
        {1},
        {2},
        {3},
        {4}
    };
    double smtrx2[ROWS][COLS] = 
    {
        {2, 1}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {2, 1},
        {4, 2},
        {6, 3},
        {8, 4},
    };

    rc = static_to_dynamic_mtrx(smtrx1, 4, 1, &mtrx1);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx2, 1, 2, &mtrx2);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx_res, 4, 2, &exp_mtrx_res);
    assert(rc == OK);

    rc = multiplication(&mtrx1, &mtrx2, &mtrx_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, 4);
    ck_assert_int_eq(mtrx_res.cols, 2);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    free_mtrx(&mtrx1);
    free_mtrx(&mtrx2);
    free_mtrx(&exp_mtrx_res);
    free_mtrx(&mtrx_res);
}
END_TEST

/// @brief Умножение матриц-векторов (строк в матрице 1 == столбцов в матрице 2)
START_TEST(test_multiplication_rows1_eq_cols2)
{
    int rc = OK;
    struct mtrx_t mtrx1, mtrx2, exp_mtrx_res, mtrx_res;

    double smtrx1[ROWS][COLS] = 
    {
        {1, 2, 3, 4, 5}
    };
    double smtrx2[ROWS][COLS] = 
    {
        {1},
        {2},
        {3},
        {4},
        {5}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {55}
    };

    rc = static_to_dynamic_mtrx(smtrx1, 1, 5, &mtrx1);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx2, 5, 1, &mtrx2);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx_res, 1, 1, &exp_mtrx_res);
    assert(rc == OK);

    rc = multiplication(&mtrx1, &mtrx2, &mtrx_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, 1);
    ck_assert_int_eq(mtrx_res.cols, 1);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    free_mtrx(&mtrx1);
    free_mtrx(&mtrx2);
    free_mtrx(&exp_mtrx_res);
    free_mtrx(&mtrx_res);
}
END_TEST

/// @brief Умножение матриц 1х1
START_TEST(test_multiplication_1x1_mtrx)
{
    int rc = OK;
    struct mtrx_t mtrx1, mtrx2, exp_mtrx_res, mtrx_res;

    double smtrx1[ROWS][COLS] = 
    {
        {0.01}
    };
    double smtrx2[ROWS][COLS] = 
    {
        {0.1}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {0.001}
    };

    rc = static_to_dynamic_mtrx(smtrx1, 1, 1, &mtrx1);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx2, 1, 1, &mtrx2);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx_res, 1, 1, &exp_mtrx_res);
    assert(rc == OK);

    rc = multiplication(&mtrx1, &mtrx2, &mtrx_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, 1);
    ck_assert_int_eq(mtrx_res.cols, 1);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    free_mtrx(&mtrx1);
    free_mtrx(&mtrx2);
    free_mtrx(&exp_mtrx_res);
    free_mtrx(&mtrx_res);
}
END_TEST

/// @brief Умножение на матрицу состоющую из нулей
START_TEST(test_multiplication_on_zero_mtrx)
{
    int rc = OK;
    struct mtrx_t mtrx1, mtrx2, exp_mtrx_res, mtrx_res;

    double smtrx1[ROWS][COLS] = 
    {
        {1, 3},
        {0, 2}
    };
    double smtrx2[ROWS][COLS] = 
    {
        {0, 0, 0},
        {0, 0, 0}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {0, 0, 0},
        {0, 0, 0}
    };

    rc = static_to_dynamic_mtrx(smtrx1, 2, 2, &mtrx1);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx2, 2, 3, &mtrx2);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx_res, 2, 3, &exp_mtrx_res);
    assert(rc == OK);

    rc = multiplication(&mtrx1, &mtrx2, &mtrx_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, 2);
    ck_assert_int_eq(mtrx_res.cols, 3);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    free_mtrx(&mtrx1);
    free_mtrx(&mtrx2);
    free_mtrx(&exp_mtrx_res);
    free_mtrx(&mtrx_res);
}
END_TEST

/// @brief Число столбцов матрицы 1 не равно числу строк матрицы 2
START_TEST(test_multiplication_col1_noneq_rows2)
{
    int rc = OK;
    struct mtrx_t mtrx1, mtrx2, mtrx_res;

    double smtrx1[ROWS][COLS] = 
    {
        {1.03, 1, 3}
    };
    double smtrx2[ROWS][COLS] = 
    {
        {0.2, 2},
        {1, 2}
    };

    rc = static_to_dynamic_mtrx(smtrx1, 1, 3, &mtrx1);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx2, 2, 2, &mtrx2);
    assert(rc == OK);

    rc = addition(&mtrx1, &mtrx2, &mtrx_res);

    ck_assert_int_eq(rc, ERR_SIZE_MTRX);

    free_mtrx(&mtrx1);
    free_mtrx(&mtrx2);
}
END_TEST


Suite* multiplication_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("multiplication");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_multiplication_rows1_lt_cols2);
    tcase_add_test(tc_pos, test_multiplication_rows1_gt_cols2);
    tcase_add_test(tc_pos, test_multiplication_rows1_eq_cols2);
    tcase_add_test(tc_pos, test_multiplication_on_zero_mtrx);
    tcase_add_test(tc_pos, test_multiplication_1x1_mtrx);
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_multiplication_col1_noneq_rows2);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}





