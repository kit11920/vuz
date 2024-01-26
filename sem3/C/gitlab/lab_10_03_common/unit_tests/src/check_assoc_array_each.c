#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include <assert.h>

#include "associative_array.h"
#include "help_check.h"

/// @brief Применяет ко всем значениям действие action_plus изменяя их (элементов в массиве несколько)
START_TEST(test_aa_each_num_plus)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 3;
    str_int_t data[] = {
        {"asde", 1},
        {"brta", 2},
        {"crt y", 3}
    };
    int *num = NULL;
    int plus = 10;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_each(arr, action_plus, &plus), ASSOC_ARRAY_OK);
    for (size_t i = 0; i < len_data; i++)
    {
        assoc_array_find(arr, data[i].str, &num);
        ck_assert_int_eq(*num, data[i].num + plus);
    }

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Применяет ко всем значениям действие action_plus изменяя их (элемент в массиве один)
START_TEST(test_aa_each_num_plus_len_arr_1)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 1;
    str_int_t data[] = {
        {"asde", 1}
    };
    int *num = NULL;
    int plus = 10;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_each(arr, action_plus, &plus), ASSOC_ARRAY_OK);
    for (size_t i = 0; i < len_data; i++)
    {
        assoc_array_find(arr, data[i].str, &num);
        ck_assert_int_eq(*num, data[i].num + plus);
    }

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Применяет ко всем значениям действие action_count_key_is_char
START_TEST(test_aa_each_count_key_is_char)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 6;
    str_int_t data[] = {
        {"k", 9},
        {"asde", 1},
        {"e", 8},
        {"c", 2},
        {"qwert", 0},
        {"crt y", 3}
    };
    int count = 0;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_each(arr, action_count_key_is_char, &count), ASSOC_ARRAY_OK);
    ck_assert_int_eq(count, 3);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief Длина массива 0
START_TEST(test_aa_each_len_arr_0)
{
    assoc_array_t arr = assoc_array_create();
    int count = 0;
    ck_assert_int_eq(assoc_array_each(arr, action_count_key_is_char, &count), ASSOC_ARRAY_OK);
    ck_assert_int_eq(count, 0);
    
    assoc_array_destroy(&arr);
}
END_TEST


/// @brief action func = NULL
START_TEST(test_aa_each_action_null)
{
    assoc_array_t arr = assoc_array_create();
    size_t len_data = 3;
    str_int_t data[] = {
        {"asde", 1},
        {"brta", 2},
        {"crt y", 3}
    };
    int plus = 10;

    ck_assert_int_eq(full_assoc_array(arr, data, len_data), ASSOC_ARRAY_OK);
    ck_assert_int_eq(assoc_array_each(arr, NULL, &plus), ASSOC_ARRAY_INVALID_PARAM);

    assoc_array_destroy(&arr);
}
END_TEST

/// @brief arr - NULL
START_TEST(test_aa_each_arr_null)
{
    int plus = 10;
    ck_assert_int_eq(assoc_array_each(NULL, action_plus, &plus), ASSOC_ARRAY_INVALID_PARAM);
}
END_TEST


Suite *each_assoc_array_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("assoc_array_each");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_aa_each_num_plus);
    tcase_add_test(tc_pos, test_aa_each_num_plus_len_arr_1);
    tcase_add_test(tc_pos, test_aa_each_count_key_is_char);
    tcase_add_test(tc_pos, test_aa_each_len_arr_0);
    
    tcase_add_test(tc_neg, test_aa_each_action_null);
    tcase_add_test(tc_neg, test_aa_each_arr_null);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}

