#include <stdlib.h>
#include <check.h>

#include "array.h"
#include "errs.h"


/// @brief В массиве все элементы положительны
START_TEST(test_key_arr_all_elem_pos)
{
    int rc;
    int exp_arr[4] = {3, 2, 4, 1};
    int arr_src[4] = {3, 2, 4, 1};
    size_t len_arr = 4;
;
    int *pb_farr, *pe_farr;

    rc = key(arr_src, arr_src + len_arr, &pb_farr, &pe_farr);

    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(pb_farr, exp_arr, pe_farr - pb_farr);
    if (rc == OK)
        free(pb_farr);
}
END_TEST

/// @brief р - в середине массива, слева от него нет отрицательных элементов
START_TEST(test_key_arr_p_middlearr_left_no_neg_elem)
{
    int rc;
    int arr_src[6] = {5, 3, 3, 4, -1, 2};
    size_t len_arr = 6;

    int exp_arr[4] = {5, 3, 3, 4};
    int *pb_farr, *pe_farr;

    rc = key(arr_src, arr_src + len_arr, &pb_farr, &pe_farr);

    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(pb_farr, exp_arr, pe_farr - pb_farr);
    if (rc == OK)
        free(pb_farr);
}
END_TEST

/// @brief р - в середине массива, слева от него есть отрицательные элементы
START_TEST(test_key_arr_p_middlearr_left_neg_elem)
{
    int rc;
    int arr_src[6] = {5, -3, 3, 4, -1, 2};
    size_t len_arr = 6;

    int exp_arr[4] = {5, -3, 3, 4};
    int *pb_farr, *pe_farr;

    rc = key(arr_src, arr_src + len_arr, &pb_farr, &pe_farr);

    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(pb_farr, exp_arr, pe_farr - pb_farr);
    if (rc == OK)
        free(pb_farr);
}
END_TEST

/// @brief р - последний элемент массива
START_TEST(test_key_arr_p_last_elem)
{
    int rc;
    int arr_src[4] = {-1, -2, 4, -9};
    size_t len_arr = 4;

    int exp_arr[4] = {-1, -2, 4, -9};
    int *pb_farr, *pe_farr;

    rc = key(arr_src, arr_src + len_arr, &pb_farr, &pe_farr);

    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(pb_farr, exp_arr, pe_farr - pb_farr);
    if (rc == OK)
        free(pb_farr);
}
END_TEST

/// @brief р - имеет индекс 1 (второй элемент массива)
START_TEST(test_key_arr_p_is_ind_2)
{
    int rc;
    int arr_src[4] = {1, -2, 3, 4};
    size_t len_arr = 4;

    int exp_arr[1] = {1};
    int *pb_farr, *pe_farr;

    rc = key(arr_src, arr_src + len_arr, &pb_farr, &pe_farr);

    ck_assert_int_eq(rc, OK);
    ck_assert_mem_eq(pb_farr, exp_arr, pe_farr - pb_farr);
    if (rc == OK)
        free(pb_farr);
}
END_TEST

/// @brief на вход функции поступает пустой массив
START_TEST(test_key_empty_src_arr)
{
    int rc;
    int arr_src[1] = {1};

    int *pb_farr, *pe_farr;

    rc = key(arr_src, arr_src, &pb_farr, &pe_farr);

    ck_assert_int_eq(rc, ERR_EMPTY_ARRAY);
}
END_TEST

/// @brief после фильтрации получается пустой массив
START_TEST(test_key_empty_filter_arr)
{
    int rc;
    int arr_src[4] = {-1, 2, 3, 4};
    size_t len_arr = 4;

    int *pb_farr, *pe_farr;

    rc = key(arr_src, arr_src + len_arr, &pb_farr, &pe_farr);

    ck_assert_int_eq(rc, ERR_EMPTY_FILTER_ARRAY);
}
END_TEST



Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("key");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_key_arr_all_elem_pos);
    tcase_add_test(tc_pos, test_key_arr_p_middlearr_left_no_neg_elem);
    tcase_add_test(tc_pos, test_key_arr_p_middlearr_left_neg_elem);
    tcase_add_test(tc_pos, test_key_arr_p_last_elem);
    tcase_add_test(tc_pos, test_key_arr_p_is_ind_2);

    tcase_add_test(tc_neg, test_key_empty_src_arr);
    tcase_add_test(tc_neg, test_key_empty_filter_arr);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}



