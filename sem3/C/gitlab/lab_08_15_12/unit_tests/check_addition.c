#include <stdlib.h>
#include <check.h>
#include <assert.h>

#include "inits.h"
#include "errs.h"
#include "operations.h"
#include "alloc_mtrx.h"


/// @brief Сложение матриц состоящих из ненулевых элементов и нулевых элементов
START_TEST(test_addition_diff_elems_matrix)
{
    int rc = OK;
    size_t rows = 2, cols = 4;
    struct mtrx_t mtrx1, mtrx2, exp_mtrx_res, mtrx_res;

    double smtrx1[ROWS][COLS] = 
    {
        {1.01, 2, 3, 4},
        {5, 0, 1.3, 0}
    };
    double smtrx2[ROWS][COLS] = 
    {
        {4, 3, 2, 1},
        {0, 0, 2, 3}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {5.01, 5, 5, 5},
        {5, 0, 3.3, 3}
    };

    rc = static_to_dynamic_mtrx(smtrx1, rows, cols, &mtrx1);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx2, rows, cols, &mtrx2);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx_res, rows, cols, &exp_mtrx_res);
    assert(rc == OK);

    rc = addition(&mtrx1, &mtrx2, &mtrx_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, rows);
    ck_assert_int_eq(mtrx_res.cols, cols);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    free_mtrx(&mtrx1);
    free_mtrx(&mtrx2);
    free_mtrx(&exp_mtrx_res);
    free_mtrx(&mtrx_res);
}
END_TEST

/// @brief Сложение матриц при котором результат нулевая матрицы
START_TEST(test_addition_res_zero_mtrx)
{
    int rc = OK;
    size_t rows = 1, cols = 3;
    struct mtrx_t mtrx1, mtrx2, exp_mtrx_res, mtrx_res;

    double smtrx1[ROWS][COLS] = 
    {
        {1, 0, -2.22}
    };
    double smtrx2[ROWS][COLS] = 
    {
        {-1, 0, 2.22}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {0, 0, 0}
    };

    rc = static_to_dynamic_mtrx(smtrx1, rows, cols, &mtrx1);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx2, rows, cols, &mtrx2);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx_res, rows, cols, &exp_mtrx_res);
    assert(rc == OK);

    rc = addition(&mtrx1, &mtrx2, &mtrx_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, rows);
    ck_assert_int_eq(mtrx_res.cols, cols);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    free_mtrx(&mtrx1);
    free_mtrx(&mtrx2);
    free_mtrx(&exp_mtrx_res);
    free_mtrx(&mtrx_res);
}
END_TEST

/// @brief Сложение матриц 1х1
START_TEST(test_addition_1x1_mtrx)
{
    int rc = OK;
    size_t rows = 1, cols = 1;
    struct mtrx_t mtrx1, mtrx2, exp_mtrx_res, mtrx_res;

    double smtrx1[ROWS][COLS] = 
    {
        {1.03}
    };
    double smtrx2[ROWS][COLS] = 
    {
        {0.2}
    };
    double smtrx_res[ROWS][COLS] = 
    {
        {1.23}
    };

    rc = static_to_dynamic_mtrx(smtrx1, rows, cols, &mtrx1);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx2, rows, cols, &mtrx2);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx_res, rows, cols, &exp_mtrx_res);
    assert(rc == OK);

    rc = addition(&mtrx1, &mtrx2, &mtrx_res);

    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(mtrx_res.rows, rows);
    ck_assert_int_eq(mtrx_res.cols, cols);
    ck_assert_int_eq(compare_mtrxs(&mtrx_res, &exp_mtrx_res), 0);

    free_mtrx(&mtrx1);
    free_mtrx(&mtrx2);
    free_mtrx(&exp_mtrx_res);
    free_mtrx(&mtrx_res);
}
END_TEST

/// @brief Матрицы разного размера
START_TEST(test_addition_neg_diff_size_mtrxs)
{
    int rc = OK;
    struct mtrx_t mtrx1, mtrx2, mtrx_res;

    double smtrx1[ROWS][COLS] = 
    {
        {1.03, 1}
    };
    double smtrx2[ROWS][COLS] = 
    {
        {0.2, 2},
        {1, 2}
    };

    rc = static_to_dynamic_mtrx(smtrx1, 1, 2, &mtrx1);
    assert(rc == OK);
    rc = static_to_dynamic_mtrx(smtrx2, 2, 2, &mtrx2);
    assert(rc == OK);

    rc = addition(&mtrx1, &mtrx2, &mtrx_res);

    ck_assert_int_eq(rc, ERR_SIZE_MTRX);

    free_mtrx(&mtrx1);
    free_mtrx(&mtrx2);
}
END_TEST


Suite* addition_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("addition");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_addition_diff_elems_matrix);
    tcase_add_test(tc_pos, test_addition_res_zero_mtrx);
    tcase_add_test(tc_pos, test_addition_1x1_mtrx);
    
    tc_neg = tcase_create("negatives");
    tcase_add_test(tc_neg, test_addition_neg_diff_size_mtrxs);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}

