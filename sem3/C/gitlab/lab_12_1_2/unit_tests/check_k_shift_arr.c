#include <stdlib.h>
#include <check.h>
#include <stdio.h>

#include "arr.h"
#include "errs.h"

/// @brief Сдвигает влево на 1 
START_TEST(test_k_shift_arr_left_1)
{
    size_t len_arr = 4;
    int arr[] = {1, 2, 3, 4};
    int exp_arr[] = {2, 3, 4, 1};
    int k = 1;
    int rc = OK;

    rc = k_shift_arr(arr, len_arr, k);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, exp_arr, sizeof(int) * len_arr);
}
END_TEST

/// @brief Сдвигает влево на k
START_TEST(test_k_shift_arr_left_k)
{
    size_t len_arr = 3;
    int arr[] = {1, 2, 3};
    int exp_arr[] = {2, 3, 1};
    int k = 7;
    int rc = OK;

    rc = k_shift_arr(arr, len_arr, k);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, exp_arr, sizeof(int) * len_arr);
}
END_TEST

/// @brief Сдвигает вправо на 1 
START_TEST(test_k_shift_arr_right_1)
{
    size_t len_arr = 5;
    int arr[] = {1, 2, 3, 4, 5};
    int exp_arr[] = {5, 1, 2, 3, 4};
    int k = -1;
    int rc = OK;

    rc = k_shift_arr(arr, len_arr, k);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, exp_arr, sizeof(int) * len_arr);
}
END_TEST

/// @brief Сдвигает вправо на k
START_TEST(test_k_shift_arr_right_k)
{
    size_t len_arr = 4;
    int arr[] = {1, 2, 3, 4};
    int exp_arr[] = {3, 4, 1, 2};
    int k = -2;
    int rc = OK;

    rc = k_shift_arr(arr, len_arr, k);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, exp_arr, sizeof(int) * len_arr);
}
END_TEST

/// @brief Сдвигает длина массива 1
START_TEST(test_k_shift_arr_len_arr_1)
{
    size_t len_arr = 1;
    int arr[] = {1};
    int exp_arr[] = {1};
    int k = 10;
    int rc = OK;

    rc = k_shift_arr(arr, len_arr, k);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, exp_arr, sizeof(int) * len_arr);
}
END_TEST

/// @brief Сдвигает k = 0
START_TEST(test_k_shift_arr_k_0)
{
    size_t len_arr = 4;
    int arr[] = {1, 2, 3, 4};
    int exp_arr[] = {1, 2, 3, 4};
    int k = 0;
    int rc = OK;

    rc = k_shift_arr(arr, len_arr, k);
    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(arr, exp_arr, sizeof(int) * len_arr);
}
END_TEST


/// @brief Сдвигает длина массива 0
START_TEST(test_k_shift_arr_len_arr_0)
{
    size_t len_arr = 0;
    int arr[] = {1};
    int k = 10;
    int rc = OK;

    rc = k_shift_arr(arr, len_arr, k);
    ck_assert_int_eq(rc, ERR_PARAM);
}
END_TEST

/// @brief Сдвигает длина arr = NULL
START_TEST(test_k_shift_arr_null_arr)
{
    size_t len_arr = 0;
    int *arr = NULL;
    int k = 10;
    int rc = OK;

    rc = k_shift_arr(arr, len_arr, k);
    ck_assert_int_eq(rc, ERR_PARAM);
}
END_TEST








Suite *k_shift_arr_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("k_shift_arr");
    tc_pos = tcase_create("positive");
    tc_neg = tcase_create("negativ");

    tcase_add_test(tc_pos, test_k_shift_arr_left_1);
    tcase_add_test(tc_pos, test_k_shift_arr_left_k);
    tcase_add_test(tc_pos, test_k_shift_arr_right_1);
    tcase_add_test(tc_pos, test_k_shift_arr_right_k);
    tcase_add_test(tc_pos, test_k_shift_arr_len_arr_1);
    tcase_add_test(tc_pos, test_k_shift_arr_k_0);
    
    tcase_add_test(tc_neg, test_k_shift_arr_len_arr_0);
    tcase_add_test(tc_neg, test_k_shift_arr_null_arr);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}


























