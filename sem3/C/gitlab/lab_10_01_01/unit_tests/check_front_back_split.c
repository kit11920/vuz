#include <stdlib.h>
#include <stdbool.h>
#include <check.h>

#include "errs.h"
#include "node_list.h"
#include "data.h"
#include "help_check.h"
#include "list.h"

/// @brief Нечетное количество элменетов
START_TEST(test_fbs_odd_elems)
{
    const size_t len_arr = 5;
    node_t *list, *back, *exp_front_list, *exp_back_list;

    country_t arr[] = {
        {"Russia", "Moscow", false, 0, 50},
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100},
        {"France", "Paris", true, 300, 150},
        {"Egypt", "Cairo", true, 400, 300}
    };
    create_list_based_arr(&list, arr, len_arr);

    country_t exp_front_arr[] = {
        {"Russia", "Moscow", false, 0, 50},
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100}
    };
    create_list_based_arr(&exp_front_list, exp_front_arr, len_arr / 2 + 1);

    country_t exp_back_arr[] = {
        {"France", "Paris", true, 300, 150},
        {"Egypt", "Cairo", true, 400, 300}
    };
    create_list_based_arr(&exp_back_list, exp_back_arr, len_arr / 2);

    front_back_split(list, &back);

    ck_assert_int_eq(cmp_list(list, exp_front_list), 0);
    ck_assert_int_eq(cmp_list(back, exp_back_list), 0);

    free_list(list);
    free_list(back);
    free_list(exp_front_list);
    free_list(exp_back_list);
} 
END_TEST

/// @brief Четное количество элменетов
START_TEST(test_fbs_even_elems)
{
    const size_t len_arr = 4;
    node_t *list, *back, *exp_front_list, *exp_back_list;

    country_t arr[] = {
        {"Russia", "Moscow", false, 0, 50},
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100},
        {"France", "Paris", true, 300, 150},
    };
    create_list_based_arr(&list, arr, len_arr);

    country_t exp_front_arr[] = {
        {"Russia", "Moscow", false, 0, 50},
        {"Japan", "Tokyo", false, 900, 200},
    };
    create_list_based_arr(&exp_front_list, exp_front_arr, len_arr / 2);

    country_t exp_back_arr[] = {
        {"Thailand", "Bangkok", false, 1200, 100},
        {"France", "Paris", true, 300, 150}
    };
    create_list_based_arr(&exp_back_list, exp_back_arr, len_arr / 2);

    front_back_split(list, &back);

    ck_assert_int_eq(cmp_list(list, exp_front_list), 0);
    ck_assert_int_eq(cmp_list(back, exp_back_list), 0);

    free_list(list);
    free_list(back);
    free_list(exp_front_list);
    free_list(exp_back_list);
} 
END_TEST

/// @brief 1 элемент
START_TEST(test_fbs_1_elem)
{
    const size_t len_arr = 1;
    node_t *list, *back, *exp_front_list;

    country_t arr[] = {
        {"Russia", "Moscow", false, 0, 50}
    };
    create_list_based_arr(&list, arr, len_arr);

    country_t exp_front_arr[] = {
        {"Russia", "Moscow", false, 0, 50}
    };
    create_list_based_arr(&exp_front_list, exp_front_arr, len_arr);

    front_back_split(list, &back);

    ck_assert_int_eq(cmp_list(list, exp_front_list), 0);
    ck_assert_ptr_null(back);

    free_list(list);
    free_list(exp_front_list);
} 
END_TEST

/// @brief список пуст
START_TEST(test_fbs_list_is_empty)
{
    node_t *list = NULL, *back = NULL;

    front_back_split(list, &back);

    ck_assert_ptr_null(list);
    ck_assert_ptr_null(back);
} 
END_TEST


Suite *front_back_split_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("front_back_split");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_fbs_odd_elems);
    tcase_add_test(tc_pos, test_fbs_even_elems);
    tcase_add_test(tc_pos, test_fbs_1_elem);

    tcase_add_test(tc_neg, test_fbs_list_is_empty);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
