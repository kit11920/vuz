#include <stdlib.h>
#include <check.h>

#include "errs.h"
#include "node_list.h"
#include "list.h"
#include "str_list.h"

/// @brief Подстрока в начале 
START_TEST(test_search_string_str_in_beg)
{
    node_t *list1, *list2;
    char str1[] = "qwerty123425";
    char str2[] = "qwerty";
    size_t ind;

    ck_assert_int_eq(string_to_list(&list1, str1), OK);
    ck_assert_int_eq(string_to_list(&list2, str2), OK);

    ind = search_string(list1, list2);
    ck_assert_int_eq(ind, 0);

    free_list(&list1);
    free_list(&list2);
} 
END_TEST

/// @brief Подстрока в середине 
START_TEST(test_search_string_str_in_mid)
{
    node_t *list1, *list2;
    char str1[] = "1234 qwerty123425";
    char str2[] = "qwerty";
    size_t ind;

    ck_assert_int_eq(string_to_list(&list1, str1), OK);
    ck_assert_int_eq(string_to_list(&list2, str2), OK);

    ind = search_string(list1, list2);
    ck_assert_int_eq(ind, 5);

    free_list(&list1);
    free_list(&list2);
} 
END_TEST

/// @brief Подстрока в конце 
START_TEST(test_search_string_str_in_end)
{
    node_t *list1, *list2;
    char str1[] = "012345678qwerty";
    char str2[] = "qwerty";
    size_t ind;

    ck_assert_int_eq(string_to_list(&list1, str1), OK);
    ck_assert_int_eq(string_to_list(&list2, str2), OK);

    ind = search_string(list1, list2);
    ck_assert_int_eq(ind, 9);

    free_list(&list1);
    free_list(&list2);
} 
END_TEST

/// @brief Подстрока меньше размера узла 
START_TEST(test_search_string_str_len_2)
{
    node_t *list1, *list2;
    char str1[] = "0qwerty123425";
    char str2[] = "qw";
    size_t ind;

    ck_assert_int_eq(string_to_list(&list1, str1), OK);
    ck_assert_int_eq(string_to_list(&list2, str2), OK);

    ind = search_string(list1, list2);
    ck_assert_int_eq(ind, 1);

    free_list(&list1);
    free_list(&list2);
} 
END_TEST

/// @brief Подстрока равна строке 
START_TEST(test_search_string_str_is_eq)
{
    node_t *list1, *list2;
    char str1[] = "qwerty";
    char str2[] = "qwerty";
    size_t ind;

    ck_assert_int_eq(string_to_list(&list1, str1), OK);
    ck_assert_int_eq(string_to_list(&list2, str2), OK);

    ind = search_string(list1, list2);
    ck_assert_int_eq(ind, 0);

    free_list(&list1);
    free_list(&list2);
} 
END_TEST

/// @brief Подстроки нет в строке
START_TEST(test_search_string_str_no)
{
    node_t *list1, *list2;
    char str1[] = "qwerty";
    char str2[] = "123";
    size_t ind;

    ck_assert_int_eq(string_to_list(&list1, str1), OK);
    ck_assert_int_eq(string_to_list(&list2, str2), OK);

    ind = search_string(list1, list2);
    ck_assert_int_eq(ind, -1);

    free_list(&list1);
    free_list(&list2);
} 
END_TEST

Suite *search_string_suite(void)
{
    Suite *s;
    TCase *tc_pos; //, *tc_neg;

    s = suite_create("search_string");
    tc_pos = tcase_create("positives");
    // tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_search_string_str_in_beg);
    tcase_add_test(tc_pos, test_search_string_str_in_mid);
    tcase_add_test(tc_pos, test_search_string_str_in_end);
    tcase_add_test(tc_pos, test_search_string_str_len_2);
    tcase_add_test(tc_pos, test_search_string_str_is_eq);
    tcase_add_test(tc_pos, test_search_string_str_no);

    suite_add_tcase(s, tc_pos);
    // suite_add_tcase(s, tc_neg);

    return s;
}


