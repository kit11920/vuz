#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include <assert.h>

#include "arr.h"
#include "errs.h"

/// @brief В выходном массиве несколько элементов, памяти выделено сколько надо 
START_TEST(test_make_sqrt_arr_enouph_mem_some_sqrt)
{
    size_t len_in = 6, len_out = 4;
    const size_t exp_len_out = 4;
    int in_arr[] = {1, 4, 6, 9, 100, 1000};
    int exp_out_arr[] = {1, 4, 9, 100}; 
    int out_arr[exp_len_out];
    int rc;

    rc = make_sqrt_arr(in_arr, len_in, out_arr, &len_out);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(len_out, exp_len_out);
    ck_assert_mem_eq(out_arr, exp_out_arr, len_out * sizeof(int));
}
END_TEST

/// @brief В выходном массиве несколько элементов, 
/// памяти выделено сколько надо динамически с подсчетом нужношо обьема
START_TEST(test_make_sqrt_arr_enouph_mem_some_sqrt_dynamic)
{
    size_t len_in = 6, len_out = 0;
    const size_t exp_len_out = 4;
    int in_arr[] = {1, 4, 6, 9, 100, 1000};
    int exp_out_arr[] = {1, 4, 9, 100}; 
    int *out_arr = NULL;
    int rc;

    rc = make_sqrt_arr(in_arr, len_in, NULL, &len_out);
    ck_assert_int_eq(rc, ERR_NOT_ENOUPH_MEM);
    out_arr = malloc(len_out * sizeof(int));
    assert(out_arr != NULL);

    make_sqrt_arr(in_arr, len_in, out_arr, &len_out);
    ck_assert_int_eq(len_out, exp_len_out);
    ck_assert_mem_eq(out_arr, exp_out_arr, len_out * sizeof(int));
    free(out_arr);
}
END_TEST

/// @brief В выходном массиве несколько элементов, памяти избыточно
START_TEST(test_make_sqrt_arr_too_much_mem_some_sqrt)
{
    const size_t exp_len_out = 4;
    size_t len_in = 6, len_out = exp_len_out + 10;
    int in_arr[] = {1, 4, 6, 9, 100, 1000};
    int exp_out_arr[] = {1, 4, 9, 100}; 
    int out_arr[exp_len_out + 10];
    int rc;

    rc = make_sqrt_arr(in_arr, len_in, out_arr, &len_out);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(len_out, exp_len_out);
    ck_assert_mem_eq(out_arr, exp_out_arr, exp_len_out * sizeof(int));
}
END_TEST

/// @brief В выходном массиве несколько элементов, памяти недостаточно
START_TEST(test_make_sqrt_arr_not_enouph_mem_some_sqrt)
{
    const size_t exp_len_out = 4;
    size_t len_in = 6, len_out = exp_len_out - 3;
    int in_arr[] = {1, 4, 6, 9, 100, 1000};
    int exp_out_arr[] = {1, 4, 9, 100}; 
    int out_arr[exp_len_out - 3];
    int rc;

    rc = make_sqrt_arr(in_arr, len_in, out_arr, &len_out);
    ck_assert_int_eq(rc, ERR_NOT_ENOUPH_MEM);
    ck_assert_int_eq(len_out, exp_len_out);
    ck_assert_mem_eq(out_arr, exp_out_arr, len_out * sizeof(int));
}
END_TEST

/// @brief Выходной массив пуст
START_TEST(test_make_sqrt_arr_empty_out_arr)
{
    size_t len_in = 9, len_out = 4;
    const size_t exp_len_out = 0;
    int in_arr[] = {2, 3, 5, 7, 6, 90, 0, -10, -9};
    int out_arr[4];
    int rc;

    rc = make_sqrt_arr(in_arr, len_in, out_arr, &len_out);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(len_out, exp_len_out);
}
END_TEST

/// @brief Выходной массив полностью заполнен
START_TEST(test_make_sqrt_arr_full_out_arr)
{
    size_t len_in = 2, len_out = 2;
    const size_t exp_len_out = 2;
    int in_arr[] = {121, 144};
    int exp_out_arr[] = {121, 144}; 
    int out_arr[exp_len_out];
    int rc;

    rc = make_sqrt_arr(in_arr, len_in, out_arr, &len_out);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(len_out, exp_len_out);
    ck_assert_mem_eq(out_arr, exp_out_arr, len_out * sizeof(int));
}
END_TEST

/// @brief Входной массив длины 1
START_TEST(test_make_sqrt_arr_1_len_in)
{
    size_t len_in = 1, len_out = 1;
    const size_t exp_len_out = 1;
    int in_arr[] = {10000};
    int exp_out_arr[] = {10000}; 
    int out_arr[exp_len_out];
    int rc;

    rc = make_sqrt_arr(in_arr, len_in, out_arr, &len_out);
    ck_assert_int_eq(rc, OK);
    ck_assert_int_eq(len_out, exp_len_out);
    ck_assert_mem_eq(out_arr, exp_out_arr, len_out * sizeof(int));
}
END_TEST

/// @brief Входной массив длины NULL
START_TEST(test_make_sqrt_arr_null_in_arr)
{
    size_t len_in = 0, len_out = 1;
    int *in_arr = NULL;
    int out_arr[1];
    int rc;

    rc = make_sqrt_arr(in_arr, len_in, out_arr, &len_out);
    ck_assert_int_eq(rc, ERR_PARAM);
}
END_TEST


Suite *make_sqrt_arr_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("make_sqrt_arr");
    tc_pos = tcase_create("positive");
    tc_neg = tcase_create("negativ");

    tcase_add_test(tc_pos, test_make_sqrt_arr_enouph_mem_some_sqrt);
    tcase_add_test(tc_pos, test_make_sqrt_arr_enouph_mem_some_sqrt_dynamic);
    tcase_add_test(tc_pos, test_make_sqrt_arr_too_much_mem_some_sqrt);
    tcase_add_test(tc_pos, test_make_sqrt_arr_not_enouph_mem_some_sqrt);
    tcase_add_test(tc_pos, test_make_sqrt_arr_empty_out_arr);
    tcase_add_test(tc_pos, test_make_sqrt_arr_full_out_arr);
    tcase_add_test(tc_pos, test_make_sqrt_arr_1_len_in);

    tcase_add_test(tc_neg, test_make_sqrt_arr_null_in_arr);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}

