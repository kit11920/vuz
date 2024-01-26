#include <stdlib.h>
#include <check.h>
#include <stdio.h>

#include "associative_array.h"
#include "help_check.h"

/// @brief Удаляемый элемент в начале (для отстортированного массива)
START_TEST(test_aa_remove_elem_beg)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 3;
    str_int_t data[] = {
        {"asde", 1},
        {"brta", 2},
        {"crt y", 3}
    };
    size_t ind_search = 0;
    char *key = data[ind_search].str;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key, &num), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Удаляемый элемент в середине (для отстортированного массива)
START_TEST(test_aa_remove_elem_mid)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 4;
    str_int_t data[] = {
        {"qasde", 1},
        {"b", 2},
        {"acrt y", 3},
        {"c", 5}
    };
    char *key = "b";
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key, &num), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Удаляемый элемент в конце (для отстортированного массива)
START_TEST(test_aa_remove_elem_end)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 2;
    str_int_t data[] = {
        {"asde", 1},
        {"brta", 2}
    };
    size_t ind_search = 1;
    char *key = data[ind_search].str;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key, &num), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Удаляемый элемент в корень (для бинарного дерева поиска)
START_TEST(test_aa_remove_elem_root)
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
    char *key = data[ind_search].str;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key, &num), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Удаляемый элемент в середине дерева (для бинарного дерева поиска)
START_TEST(test_aa_remove_elem_mid_tree)
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
    size_t ind_search = 2;
    char *key = data[ind_search].str;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key, &num), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Удаляемый элемент в лист (для бинарного дерева поиска)
START_TEST(test_aa_remove_elem_leaf)
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
    size_t ind_search = 4;
    char *key = data[ind_search].str;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key, &num), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Удаляемый элемент один
START_TEST(test_aa_remove_elem_one)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 1;
    str_int_t data[] = {
        {"asde", 1}
    };
    size_t ind_search = 0;
    char *key = data[ind_search].str;
    int *num = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_find(arr, key, &num), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST


/// @brief Удаляемого элемента нет 
START_TEST(test_aa_remove_elem_no)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 3;
    str_int_t data[] = {
        {"asde", 1},
        {"brta", 2},
        {"crt y", 3}
    };
    char *key = "qwerty";

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_NOT_FOUND);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Длина массива 0
START_TEST(test_aa_remove_len_arr_0)
{
    assoc_array_t arr = assoc_array_create();
    char *key = "qwerty";
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_NOT_FOUND);
    
    assoc_array_destroy(&arr);
}
END_TEST

/// @brief key - пустая строка
START_TEST(test_aa_remove_key_len_0)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 3;
    str_int_t data[] = {
        {"asde", 1},
        {"brta", 2},
        {"crt y", 3}
    };
    char *key = "";

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief key - null
START_TEST(test_aa_remove_key_null)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 3;
    str_int_t data[] = {
        {"asde", 1},
        {"brta", 2},
        {"crt y", 3}
    };
    char *key = NULL;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_remove(arr, key), ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief arr- null
START_TEST(test_aa_remove_arr_null)
{
    char *key = "qwerty";
    ck_assert_int_eq(assoc_array_remove(NULL, key), ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST


Suite *remove_assoc_array_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc_array_remove");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_aa_remove_elem_beg);
    tcase_add_test(tc_pos, test_aa_remove_elem_mid);
    tcase_add_test(tc_pos, test_aa_remove_elem_end);
    tcase_add_test(tc_pos, test_aa_remove_elem_one);

    tcase_add_test(tc_pos, test_aa_remove_elem_root);
    tcase_add_test(tc_pos, test_aa_remove_elem_mid_tree);
    tcase_add_test(tc_pos, test_aa_remove_elem_leaf);

    tcase_add_test(tc_neg, test_aa_remove_elem_no);
    tcase_add_test(tc_neg, test_aa_remove_len_arr_0);
    tcase_add_test(tc_neg, test_aa_remove_key_len_0);
    tcase_add_test(tc_neg, test_aa_remove_key_null);
    tcase_add_test(tc_neg, test_aa_remove_arr_null);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}











