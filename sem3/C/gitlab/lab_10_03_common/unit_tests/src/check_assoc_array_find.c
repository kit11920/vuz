#include <stdlib.h>
#include <check.h>
#include <stdio.h>

#include "associative_array.h"
#include "help_check.h"


/// @brief Искомый элемент в начале (для отстортированного массива)
START_TEST(test_aa_find_elem_beg)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 3;
    str_int_t data[] = {
        {"crt y", 1},
        {"brta", 2},
        {"asde", 3}
    };
    size_t ind_search = 2;
    char *key_search = data[ind_search].str;
    int exp_num = data[ind_search].num;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key_search, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Искомый элемент в середине (для отстортированного массива)
START_TEST(test_aa_find_elem_mid)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 4;
    str_int_t data[] = {
        {"c", 1},
        {"a", 2},
        {"b", 3},
        {"d", 5}
    };
    // size_t ind_search = 2;
    char *key_search = "b";
    int exp_num = 3;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key_search, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Искомый элемент в конце (для отстортированного массива)
START_TEST(test_aa_find_elem_end)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 2;
    str_int_t data[] = {
        {"basde", 1},
        {"abrta", 2}
    };
    size_t ind_search = 0;
    char *key_search = data[ind_search].str;
    int exp_num = data[ind_search].num;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key_search, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Искомый элемент корень (для бинарного дерева поиска)
START_TEST(test_aa_find_elem_root)
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
    size_t ind_search = 0;
    char *key_search = data[ind_search].str;
    int exp_num = data[ind_search].num;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key_search, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Искомый элемент в середине дерева (для бинарного дерева поиска)
START_TEST(test_aa_find_elem_mid_tree)
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
    size_t ind_search = 3;
    char *key_search = data[ind_search].str;
    int exp_num = data[ind_search].num;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key_search, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Искомый элемент лист (для бинарного дерева поиска)
START_TEST(test_aa_find_elem_leaf)
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
    size_t ind_search = 7;
    char *key_search = data[ind_search].str;
    int exp_num = data[ind_search].num;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key_search, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Искомый элемент один в массиве
START_TEST(test_aa_find_elem_one)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 1;
    str_int_t data[] = {
        {"asde", 1}
    };
    size_t ind_search = 0;
    char *key_search = data[ind_search].str;
    int exp_num = data[ind_search].num;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key_search, &num), ASSOC_ARRAY_OK);
    ck_assert_int_eq(*num, exp_num);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Искомого элемента нет
START_TEST(test_aa_find_elem_no)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 5;
    str_int_t data[] = {
        {"asde", 1},
        {"brta", 2},
        {"c", 3},
        {"d", 4},
        {"e", 5}
    };
    char *key_search = "qwerty";
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key_search, &num), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Длина массива 0
START_TEST(test_aa_find_len_arr_0)
{
    assoc_array_t arr = assoc_array_create();
    char *key = "qwerty";
    int *num = NULL;
    ck_assert_int_eq(assoc_array_find(arr, key, &num), ASSOC_ARRAY_NOT_FOUND);
    
    assoc_array_destroy(&arr);
}
END_TEST

/// @brief key - пустая строка
START_TEST(test_aa_find_key_len_0)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 5;
    str_int_t data[] = {
        {"asde", 1},
        {"brta", 2},
        {"c", 3},
        {"d", 4},
        {"e", 5}
    };
    char *key_search = "";
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key_search, &num), ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief key = NULL
START_TEST(test_aa_find_key_null)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 5;
    str_int_t data[] = {
        {"asde", 1},
        {"brta", 2},
        {"c", 3},
        {"d", 4},
        {"e", 5}
    };
    // char *key_search = "qwerty";
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, NULL, &num), ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief arr = NULL
START_TEST(test_aa_find_arr_null)
{
    char *key_search = "qwerty";
    int *num = NULL;

    ck_assert_int_eq(assoc_array_find(NULL, key_search, &num), ASSOC_ARRAY_INVALID_PARAM);

}
END_TEST


Suite *find_assoc_array_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc_array_find");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_aa_find_elem_beg);
    tcase_add_test(tc_pos, test_aa_find_elem_mid);
    tcase_add_test(tc_pos, test_aa_find_elem_end);
    tcase_add_test(tc_pos, test_aa_find_elem_one);

    tcase_add_test(tc_pos, test_aa_find_elem_root);
    tcase_add_test(tc_pos, test_aa_find_elem_mid_tree);
    tcase_add_test(tc_pos, test_aa_find_elem_leaf);

    tcase_add_test(tc_neg, test_aa_find_elem_no);
    tcase_add_test(tc_neg, test_aa_find_len_arr_0);
    tcase_add_test(tc_neg, test_aa_find_key_len_0);
    tcase_add_test(tc_neg, test_aa_find_key_null);
    tcase_add_test(tc_neg, test_aa_find_arr_null);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}











