#include <stdlib.h>
#include <stdbool.h>
#include <check.h>

#include "errs.h"
#include "node_list.h"
#include "data.h"
#include "help_check.h"
#include "list.h"

/// @brief Ищет элемент в середине списка
START_TEST(test_find_elem_mid)
{
    const size_t len_arr = 3;
    node_t *list, *search_node = NULL, *exp_node = NULL;

    country_t arr[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200}, 
        {"France", "Paris", true, 300, 150}
        };
    create_list_based_arr(&list, arr, len_arr);

    country_t country = {"Japan", "qwe", true, 1, 1};
    exp_node = create_node(&country);
    ck_assert_ptr_nonnull(exp_node);

    search_node = find(list, &country, cmp_name);

    ck_assert_int_eq(cmp_name(search_node->data, exp_node->data), 0);

    free_list(list);
    free_list(exp_node);
} 
END_TEST

/// @brief Ищет элемент в начале списка
START_TEST(test_find_elem_beg)
{
    const size_t len_arr = 3;
    node_t *list, *search_node = NULL, *exp_node = NULL;

    country_t arr[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200}, 
        {"France", "Paris", true, 300, 150}
        };
    create_list_based_arr(&list, arr, len_arr);

    country_t country = {"Russia", "qwe", true, 1, 1};
    exp_node = create_node(&country);
    ck_assert_ptr_nonnull(exp_node);

    search_node = find(list, &country, cmp_name);

    ck_assert_int_eq(cmp_name(search_node->data, exp_node->data), 0);


    
    free_list(list);
    free_list(exp_node);
} 
END_TEST

/// @brief Ищет элемент в конце списка
START_TEST(test_find_elem_end)
{
    const size_t len_arr = 3;
    node_t *list, *search_node = NULL, *exp_node = NULL;

    country_t arr[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200}, 
        {"France", "Paris", true, 300, 150}
        };
    create_list_based_arr(&list, arr, len_arr);

    country_t country = {"France", "qwe", true, 1, 1};
    exp_node = create_node(&country);
    ck_assert_ptr_nonnull(exp_node);

    search_node = find(list, &country, cmp_name);

    ck_assert_int_eq(cmp_name(search_node->data, exp_node->data), 0);

    free_list(list);
    free_list(exp_node);
} 
END_TEST

/// @brief Искомого элемента в списке нет
START_TEST(test_find_no_elem_in_list)
{
    const size_t len_arr = 3;
    node_t *list, *search_node = NULL;

    country_t arr[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200}, 
        {"France", "Paris", true, 300, 150}
        };
    create_list_based_arr(&list, arr, len_arr);

    country_t country = {"qwe", "qwe", true, 1, 1};

    search_node = find(list, &country, cmp_name);

    ck_assert_ptr_null(search_node);

    
    free_list(list);
} 
END_TEST

/// @brief Списко пустой
START_TEST(test_find_list_is_empty)
{
    node_t *search_node = NULL;

    country_t country = {"France", "qwe", true, 1, 1};

    search_node = find(NULL, &country, cmp_name);

    ck_assert_ptr_null(search_node);
} 
END_TEST

Suite *find_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("find");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_find_elem_mid);
    tcase_add_test(tc_pos, test_find_elem_beg);
    tcase_add_test(tc_pos, test_find_elem_end);
    tcase_add_test(tc_neg, test_find_no_elem_in_list);
    tcase_add_test(tc_neg, test_find_list_is_empty);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}
