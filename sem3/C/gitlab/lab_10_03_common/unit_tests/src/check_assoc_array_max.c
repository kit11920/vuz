#include <stdlib.h>
#include <check.h>
#include <stdio.h>

#include "associative_array.h"
#include "help_check.h"


/// @brief Много элементов в массиве (широкое дерево)
START_TEST(test_aa_max_elems_alot)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 10;
    str_int_t data[] = {
        {"d", 1},
        {"f", 2},
        {"b", 3},
        {"ed", 4},
        {"c", 5},
        {"i", 6},
        {"a", 7},
        {"ef", 8},
        {"j", 9},
        {"eb", 10}
    };
    size_t ind_search = 8;
    int exp_num = data[ind_search].num;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_max(arr, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief 3 элемента в массиве
START_TEST(test_aa_max_elems_3)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 3;
    str_int_t data[] = {
        {"qwe", 1},
        {"brta", 2},
        {"a", 9}
    };
    size_t ind_search = 0;
    int exp_num = data[ind_search].num;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_max(arr, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief 2 элемента в массиве
START_TEST(test_aa_max_elems_2)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 2;
    str_int_t data[] = {
        {"a", 1},
        {"brta", 2}
    };
    size_t ind_search = 1;
    int exp_num = data[ind_search].num;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_max(arr, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Один элемент в массиве
START_TEST(test_aa_max_elem_one)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 1;
    str_int_t data[] = {
        {"asde", 1}
    };
    size_t ind_search = 0;
    int exp_num = data[ind_search].num;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_max(arr, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Длина массива 0
START_TEST(test_aa_max_len_arr_0)
{
    assoc_array_t arr = assoc_array_create();
    int *num = NULL;
    ck_assert_int_eq(assoc_array_max(arr, &num), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief arr = NULL
START_TEST(test_aa_max_arr_null)
{
    int *num = NULL;

    ck_assert_int_eq(assoc_array_max(NULL, &num), ASSOC_ARRAY_INVALID_PARAM);

}
END_TEST


Suite *max_assoc_array_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc_array_max");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_aa_max_elems_alot);
    tcase_add_test(tc_pos, test_aa_max_elems_3);
    tcase_add_test(tc_pos, test_aa_max_elems_2);
    tcase_add_test(tc_pos, test_aa_max_elem_one);
    tcase_add_test(tc_neg, test_aa_max_len_arr_0);
    tcase_add_test(tc_neg, test_aa_max_arr_null);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}











