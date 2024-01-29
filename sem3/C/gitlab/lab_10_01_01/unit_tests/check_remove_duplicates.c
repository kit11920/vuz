#include <stdlib.h>
#include <stdbool.h>
#include <check.h>

#include "errs.h"
#include "node_list.h"
#include "data.h"
#include "help_check.h"
#include "list.h"

/// @brief Удаляет один элемент из списка длинной более 1 элменета
START_TEST(test_rd_rm_1_elem)
{
    const size_t len_arr = 5;
    node_t *list_begin, *list_end;

    country_t arr_begin[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200}, 
        {"Thailand", "Bangkok", false, 1200, 100},
        {"Thailand", "Paris", true, 300, 150},
        {"Egypt", "Cairo", true, 400, 300}
        };
    create_list_based_arr(&list_begin, arr_begin, len_arr);

    country_t arr_end[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200}, 
        {"Thailand", "Bangkok", false, 1200, 100},
        {"Egypt", "Cairo", true, 400, 300}
        };
    create_list_based_arr(&list_end, arr_end, len_arr - 1);

    remove_duplicates(&list_begin, cmp_name);

    ck_assert_int_eq(cmp_list(list_begin, list_end), 0);

    free_list(list_begin);
    free_list(list_end);
} 
END_TEST

/// @brief В списке все элементы одинаковые
START_TEST(test_rd_all_elems_same)
{
    const size_t len_arr_beg = 5, len_arr_end = 1;
    node_t *list_begin, *list_end;

    country_t arr_begin[] = {
        {"a",  "Moscow", false, 0, 50}, 
        {"a", "Tokyo", false, 900, 200}, 
        {"a", "Bangkok", false, 1200, 100},
        {"a", "Paris", true, 300, 150},
        {"a", "Cairo", true, 400, 300}
        };
    create_list_based_arr(&list_begin, arr_begin, len_arr_beg);

    country_t arr_end[] = {
        {"a",  "Moscow", false, 0, 50}
        };
    create_list_based_arr(&list_end, arr_end, len_arr_end);

    remove_duplicates(&list_begin, cmp_name);
    ck_assert_int_eq(cmp_list(list_begin, list_end), 0);

    free_list(list_begin);
    free_list(list_end);
} 
END_TEST

/// @brief В списке все элементы разные
START_TEST(test_rd_all_elems_diff)
{
    const size_t len_arr = 5;
    node_t *list_begin, *list_end;

    country_t arr_begin[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200}, 
        {"Thailand", "Bangkok", false, 1200, 100},
        {"France", "Paris", true, 300, 150},
        {"Egypt", "Cairo", true, 400, 300}
        };
    create_list_based_arr(&list_begin, arr_begin, len_arr);

    country_t arr_end[] = {
        {"Russia",  "Moscow", false, 0, 50}, 
        {"Japan", "Tokyo", false, 900, 200}, 
        {"Thailand", "Bangkok", false, 1200, 100},
        {"France", "Paris", true, 300, 150},
        {"Egypt", "Cairo", true, 400, 300}
        };
    create_list_based_arr(&list_end, arr_end, len_arr);

    remove_duplicates(&list_begin, cmp_name);
    ck_assert_int_eq(cmp_list(list_begin, list_end), 0);

    free_list(list_begin);
    free_list(list_end);
} 
END_TEST

/// @brief В списке 1 элемент
START_TEST(test_rd_1_elem_in_list)
{
    const size_t len_arr = 1;
    node_t *list_begin, *list_end;

    country_t arr_begin[] = {
        {"Russia",  "Moscow", false, 0, 50}
        };
    create_list_based_arr(&list_begin, arr_begin, len_arr);

    country_t arr_end[] = {
        {"Russia",  "Moscow", false, 0, 50}
        };
    create_list_based_arr(&list_end, arr_end, len_arr);

    remove_duplicates(&list_begin, cmp_name);
    ck_assert_int_eq(cmp_list(list_begin, list_end), 0);

    free_list(list_begin);
    free_list(list_end);
} 
END_TEST

/// @brief Список пуст
START_TEST(test_rd_list_is_empty)
{
    node_t *list = NULL;

    remove_duplicates(&list, cmp_name);
    ck_assert_ptr_null(list);
} 
END_TEST


Suite *remove_duplicates_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("remove_duplicates");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_rd_rm_1_elem);
    tcase_add_test(tc_pos, test_rd_all_elems_same);
    tcase_add_test(tc_pos, test_rd_all_elems_diff);
    tcase_add_test(tc_pos, test_rd_1_elem_in_list);
    tcase_add_test(tc_neg, test_rd_list_is_empty);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}

