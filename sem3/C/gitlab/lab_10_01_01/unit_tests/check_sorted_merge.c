#include <stdlib.h>
#include <stdbool.h>
#include <check.h>

#include "errs.h"
#include "node_list.h"
#include "data.h"
#include "help_check.h"
#include "list.h"

/// @brief Первый список длиннее второго
START_TEST(test_sorted_merge_list1_gt_list2)
{
    const size_t len_arr1 = 3, len_arr2 = 2;
    const size_t len_arr = len_arr1 + len_arr2;
    node_t *list1, *list2, *exp_list, *list;

    country_t arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150},
        {"d", "qwe", true, 300, 150},
        {"e", "asd", true, 300, 150}
        };
    create_list_based_arr(&exp_list, arr, len_arr);
    country_t arr1[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"c", "Paris", true, 300, 150},
        {"e", "asd", true, 300, 150}
        };
    create_list_based_arr(&list1, arr1, len_arr1);
    country_t arr2[] = {
        {"b", "Tokyo", false, 900, 200},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&list2, arr2, len_arr2);

    list = sorted_merge(&list1, &list2, cmp_name);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief Списки одинаковой длины
START_TEST(test_sorted_merge_list1_eq_list2)
{
    const size_t len_arr1 = 2, len_arr2 = 2;
    const size_t len_arr = len_arr1 + len_arr2;
    node_t *list1, *list2, *exp_list, *list;

    country_t arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200},
        {"d", "qwe", true, 300, 150},
        {"e", "asd", true, 300, 150}
        };
    create_list_based_arr(&exp_list, arr, len_arr);
    country_t arr1[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"e", "asd", true, 300, 150}
        };
    create_list_based_arr(&list1, arr1, len_arr1);
    country_t arr2[] = {
        {"b", "Tokyo", false, 900, 200},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&list2, arr2, len_arr2);

    list = sorted_merge(&list1, &list2, cmp_name);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief Первый список короче второго
START_TEST(test_sorted_merge_list1_lt_list2)
{
    const size_t len_arr1 = 1, len_arr2 = 3;
    const size_t len_arr = len_arr1 + len_arr2;
    node_t *list1, *list2, *exp_list, *list;

    country_t arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&exp_list, arr, len_arr);
    country_t arr1[] = {
        {"c", "Paris", true, 300, 150}
        };
    create_list_based_arr(&list1, arr1, len_arr1);
    country_t arr2[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&list2, arr2, len_arr2);

    list = sorted_merge(&list1, &list2, cmp_name);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief Первый список пуст
START_TEST(test_sorted_merge_list1_is_empty)
{
    const size_t len_arr2 = 4;
    const size_t len_arr = len_arr2;
    node_t *list2, *exp_list, *list;

    country_t arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&exp_list, arr, len_arr);

    country_t arr2[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&list2, arr2, len_arr2);

    list = sorted_merge(NULL, &list2, cmp_name);

    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief Второй список пуст
START_TEST(test_sorted_merge_list2_is_empty)
{
    const size_t len_arr1 = 4;
    const size_t len_arr = len_arr1;
    node_t *list1, *exp_list, *list;

    country_t arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&exp_list, arr, len_arr);

    country_t arr1[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&list1, arr1, len_arr1);

    list = sorted_merge(&list1, NULL, cmp_name);

    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief Оба списка пусты
START_TEST(test_sorted_merge_list1_list2_is_empty)
{
    node_t *list;

    list = sorted_merge(NULL, NULL, cmp_name);

    ck_assert_ptr_null(list);
} 
END_TEST


Suite *sorted_merge_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("sorted_merge");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_sorted_merge_list1_gt_list2);
    tcase_add_test(tc_pos, test_sorted_merge_list1_eq_list2);
    tcase_add_test(tc_pos, test_sorted_merge_list1_lt_list2);

    tcase_add_test(tc_neg, test_sorted_merge_list1_is_empty);
    tcase_add_test(tc_neg, test_sorted_merge_list2_is_empty);
    tcase_add_test(tc_neg, test_sorted_merge_list1_list2_is_empty);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
