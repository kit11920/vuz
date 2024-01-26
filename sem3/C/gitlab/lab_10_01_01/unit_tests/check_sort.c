#include <stdlib.h>
#include <stdbool.h>
#include <check.h>

#include "errs.h"
#include "node_list.h"
#include "data.h"
#include "help_check.h"
#include "list.h"

/// @brief Элементы в рандомном порядке, все разные
START_TEST(test_sort_random_all_diff)
{
    const size_t len_arr = 5;
    node_t *list, *exp_list;

    country_t exp_arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150},
        {"d", "qwe", true, 300, 150},
        {"e", "asd", true, 300, 150}
        };
    create_list_based_arr(&exp_list, exp_arr, len_arr);
    country_t arr[] = {
        {"e", "asd", true, 300, 150},
        {"b", "Tokyo", false, 900, 200}, 
        {"a",  "Moscow", false, 0, 50},
        {"d", "qwe", true, 300, 150},
        {"c", "Paris", true, 300, 150}
        };
    create_list_based_arr(&list, arr, len_arr);

    list = sort(list, cmp_name);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief Элементы в рандомном порядке, есть одинаковые
START_TEST(test_sort_random_have_same_elems)
{
    const size_t len_arr = 6;
    node_t *list, *exp_list;

    country_t exp_arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"a", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150},
        {"c", "qwe", true, 300, 150},
        {"d", "qwe", true, 300, 150},
        {"e", "asd", true, 300, 150}
        };
    create_list_based_arr(&exp_list, exp_arr, len_arr);
    country_t arr[] = {
        {"e", "asd", true, 300, 150},
        {"c", "Paris", true, 300, 150},
        {"c", "qwe", true, 300, 150},
        {"a",  "Moscow", false, 0, 50}, 
        {"d", "qwe", true, 300, 150},
        {"a", "Tokyo", false, 900, 200}
        };
    create_list_based_arr(&list, arr, len_arr);

    list = sort(list, cmp_name);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief Элементы в в порядке возрастания
START_TEST(test_sort_up)
{
    const size_t len_arr = 4;
    node_t *list, *exp_list;

    country_t exp_arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&exp_list, exp_arr, len_arr);
    country_t arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&list, arr, len_arr);

    list = sort(list, cmp_name);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief Элементы в порядке убывания
START_TEST(test_sort_down)
{
    const size_t len_arr = 3;
    node_t *list, *exp_list;

    country_t exp_arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}, 
        {"c", "Paris", true, 300, 150}
        };
    create_list_based_arr(&exp_list, exp_arr, len_arr);
    country_t arr[] = {
        {"c", "Paris", true, 300, 150},
        {"b", "Tokyo", false, 900, 200},
        {"a",  "Moscow", false, 0, 50}
        };
    create_list_based_arr(&list, arr, len_arr);

    list = sort(list, cmp_name);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief 2 элементы в порядке вовзрастания
START_TEST(test_sort_2_elems_up)
{
    const size_t len_arr = 2;
    node_t *list, *exp_list;

    country_t exp_arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}
        };
    create_list_based_arr(&exp_list, exp_arr, len_arr);
    country_t arr[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"b", "Tokyo", false, 900, 200}
        };
    create_list_based_arr(&list, arr, len_arr);

    list = sort(list, cmp_name);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief 2 элементы в порядке убывания
START_TEST(test_sort_2_elems_down)
{
    const size_t len_arr = 2;
    node_t *list, *exp_list;

    country_t exp_arr[] = {
        {"c", "Paris", true, 300, 150},
        {"d", "qwe", true, 300, 150}
        };
    create_list_based_arr(&exp_list, exp_arr, len_arr);
    country_t arr[] = {
        {"d", "qwe", true, 300, 150},
        {"c", "Paris", true, 300, 150},
        };
    create_list_based_arr(&list, arr, len_arr);

    list = sort(list, cmp_name);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief 1 элемент
START_TEST(test_sort_1_elem)
{
    const size_t len_arr = 1;
    node_t *list, *exp_list;

    country_t exp_arr[] = {
        {"a",  "Moscow", false, 0, 50}
        };
    create_list_based_arr(&exp_list, exp_arr, len_arr);
    country_t arr[] = {
        {"a",  "Moscow", false, 0, 50}
        };
    create_list_based_arr(&list, arr, len_arr);

    list = sort(list, cmp_name);

    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(list);
    free_list(exp_list);
} 
END_TEST

/// @brief на вход функции подается нулевой указатель
START_TEST(test_sort_null_head)
{
    node_t *list = NULL;

    list = sort(list, cmp_name);

    ck_assert_ptr_null(list);
} 
END_TEST

Suite *sort_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("sort");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_sort_random_all_diff);
    tcase_add_test(tc_pos, test_sort_random_have_same_elems);
    tcase_add_test(tc_pos, test_sort_up);
    tcase_add_test(tc_pos, test_sort_down);
    tcase_add_test(tc_pos, test_sort_2_elems_up);
    tcase_add_test(tc_pos, test_sort_2_elems_down);
    tcase_add_test(tc_pos, test_sort_1_elem);

    tcase_add_test(tc_neg, test_sort_null_head);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}