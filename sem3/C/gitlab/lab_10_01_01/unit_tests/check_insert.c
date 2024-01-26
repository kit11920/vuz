#include <stdlib.h>
#include <stdbool.h>
#include <check.h>

#include "errs.h"
#include "node_list.h"
#include "data.h"
#include "help_check.h"
#include "list.h"

/// @brief Вставляет элемент перед первым элементом в списке 
START_TEST(test_insert_before_head)
{
    const size_t len_arr = 2;
    node_t *list_begin, *list_end;
    node_t *insert_node = NULL;

    country_t arr_begin[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200}
        };
    create_list_based_arr(&list_begin, arr_begin, len_arr);

    country_t country = {"France", "Paris", true, 300, 150};
    insert_node = create_node(&country);
    ck_assert_ptr_nonnull(insert_node);
    
    country_t arr_end[] = {
        {"France", "Paris", true, 300, 150},
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200}
        };
    create_list_based_arr(&list_end, arr_end, len_arr + 1);

    insert(&list_begin, insert_node, list_begin);
    ck_assert_int_eq(cmp_list(list_begin, list_end), 0);

    free_list(list_begin);
    free_list(list_end);
} 
END_TEST

/// @brief Вставляет элемент в середину списка
START_TEST(test_insert_before_mid)
{
    const size_t len_arr = 3;
    node_t *list_begin, *list_end;
    node_t *insert_node = NULL, *before = NULL;

    country_t arr_begin[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100}
        };
    create_list_based_arr(&list_begin, arr_begin, len_arr);

    country_t country = {"France", "Paris", true, 300, 150};
    insert_node = create_node(&country);
    ck_assert_ptr_nonnull(insert_node);
    
    country_t arr_end[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"France", "Paris", true, 300, 150},
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100}
        };
    create_list_based_arr(&list_end, arr_end, len_arr + 1);

    before = list_begin->next;

    insert(&list_begin, insert_node, before);
    ck_assert_int_eq(cmp_list(list_begin, list_end), 0);

    
    free_list(list_begin);
    free_list(list_end);
} 
END_TEST

/// @brief Вставляет элемент в перед последним элементом списка
START_TEST(test_insert_before_end)
{
    const size_t len_arr = 3;
    node_t *list_begin, *list_end;
    node_t *insert_node = NULL, *before = NULL;

    country_t arr_begin[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100}
        };
    create_list_based_arr(&list_begin, arr_begin, len_arr);

    country_t country = {"France", "Paris", true, 300, 150};
    insert_node = create_node(&country);
    ck_assert_ptr_nonnull(insert_node);
    
    country_t arr_end[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200},
        {"France", "Paris", true, 300, 150},
        {"Thailand", "Bangkok", false, 1200, 100}
        };
    create_list_based_arr(&list_end, arr_end, len_arr + 1);

    before = list_begin->next->next;

    insert(&list_begin, insert_node, before);
    ck_assert_int_eq(cmp_list(list_begin, list_end), 0);

    free_list(list_begin);
    free_list(list_end);
} 
END_TEST

/// @brief Элемента before нет в списке (список не меняется)
START_TEST(test_insert_no_in_list_before)
{
    const size_t len_arr = 4;
    node_t *list_begin, *list_end;
    node_t *insert_node = NULL, *before = NULL;

    country_t arr_begin[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100},
        {"France", "Paris", true, 300, 150}
        };
    create_list_based_arr(&list_begin, arr_begin, len_arr);

    country_t country = {"France1", "Paris1", true, 1300, 1150};
    insert_node = create_node(&country);
    ck_assert_ptr_nonnull(insert_node);
    
    country_t arr_end[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100},
        {"France", "Paris", true, 300, 150}
        };
    create_list_based_arr(&list_end, arr_end, len_arr);

    country_t country_before = {"qwe", "asd", true, 3, 1};
    before = create_node(&country_before);
    ck_assert_ptr_nonnull(before);

    insert(&list_begin, insert_node, before);
    ck_assert_int_eq(cmp_list(list_begin, list_end), 0);

    
    free_list(list_begin);
    free_list(list_end);
    free_list(insert_node);
    free_list(before);
} 
END_TEST

/// @brief На вход функции подается пустой список
START_TEST(test_insert_head_is_null)
{
    node_t *list = NULL;
    node_t *insert_node = NULL, *before = NULL;

    country_t country = {"France1", "Paris1", true, 1300, 1150};
    insert_node = create_node(&country);
    ck_assert_ptr_nonnull(insert_node);

    country_t country_before = {"qwe", "asd", true, 3, 1};
    before = create_node(&country_before);
    ck_assert_ptr_nonnull(before);

    insert(&list, insert_node, before);

    ck_assert_ptr_null(list);

    free_list(insert_node);
    free_list(before);
} 
END_TEST

/// @brief Вставляемый элемент указывает на NULL
START_TEST(test_insert_elem_is_null)
{
    const size_t len_arr = 3;
    node_t *list_begin, *list_end;
    node_t *before = NULL;

    country_t arr_begin[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100}
        };
    create_list_based_arr(&list_begin, arr_begin, len_arr);

    before = list_begin->next->next;
    
    country_t arr_end[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100}
        };
    create_list_based_arr(&list_end, arr_end, len_arr);

    insert(&list_begin, NULL, before);
    ck_assert_int_eq(cmp_list(list_begin, list_end), 0);

    
    free_list(list_begin);
    free_list(list_end);
} 
END_TEST

/// @brief Элемент before укзаывает на NULL
START_TEST(test_insert_before_is_null)
{
    const size_t len_arr = 3;
    node_t *list_begin, *list_end;
    node_t *insert_node = NULL;

    country_t arr_begin[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100}
        };
    create_list_based_arr(&list_begin, arr_begin, len_arr);

    country_t country = {"France", "Paris", true, 300, 150};
    insert_node = create_node(&country);
    ck_assert_ptr_nonnull(insert_node);
    
    country_t arr_end[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200},
        {"Thailand", "Bangkok", false, 1200, 100}
        };
    create_list_based_arr(&list_end, arr_end, len_arr);

    insert(&list_begin, insert_node, NULL);
    ck_assert_int_eq(cmp_list(list_begin, list_end), 0);

    
    free_list(list_begin);
    free_list(list_end);
    free_list(insert_node);
} 
END_TEST


Suite *insert_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("insert");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_insert_before_head);
    tcase_add_test(tc_pos, test_insert_before_mid);
    tcase_add_test(tc_pos, test_insert_before_end);
    tcase_add_test(tc_neg, test_insert_no_in_list_before);
    tcase_add_test(tc_neg, test_insert_head_is_null);
    tcase_add_test(tc_neg, test_insert_elem_is_null);
    tcase_add_test(tc_neg, test_insert_before_is_null);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}


