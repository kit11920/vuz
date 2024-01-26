#include <stdlib.h>
#include <check.h>

#include "list.h"
#include "node_list.h"
#include "str_list.h"
#include "errs.h"
#include "help_check.h"

/// @brief Склеивает строки так что у второй строки не надо удалять узел 
START_TEST(test_cat_str_list_cat_no_del_node)
{
    node_t *list1, *list2, *exp_list;
    char str1[] = "1234";
    char str2[] = "12341234";
    char exp_str[] = "123412341234";

    ck_assert_int_eq(string_to_list(&list1, str1), OK);
    ck_assert_int_eq(string_to_list(&list2, str2), OK);
    ck_assert_int_eq(string_to_list(&exp_list, exp_str), OK);

    cat_str_list(list1, list2);
    ck_assert_int_eq(cmp_list(list1, exp_list), 0);

    free_list(&list1);
    free_list(&exp_list);
}
END_TEST

/// @brief Склеивает строки так что у второй строки надо удалять узел 
START_TEST(test_cat_str_list_cat_del_node)
{
    node_t *list1, *list2, *exp_list;
    char str1[] = "123412";
    char str2[] = "34123";
    char exp_str[] = "12341234123";

    ck_assert_int_eq(string_to_list(&list1, str1), OK);
    ck_assert_int_eq(string_to_list(&list2, str2), OK);
    ck_assert_int_eq(string_to_list(&exp_list, exp_str), OK);

    cat_str_list(list1, list2);
    ck_assert_int_eq(cmp_list(list1, exp_list), 0);

    free_list(&list1);
    free_list(&exp_list);
}
END_TEST

/// @brief Склеивает строки так что вторая строка полностью изсчезает так как состоит из 1 узла
START_TEST(test_cat_str_list_one_node_list2)
{
    node_t *list1, *list2, *exp_list;
    char str1[] = "12";
    char str2[] = "3";
    char exp_str[] = "123";

    ck_assert_int_eq(string_to_list(&list1, str1), OK);
    ck_assert_int_eq(string_to_list(&list2, str2), OK);
    ck_assert_int_eq(string_to_list(&exp_list, exp_str), OK);

    cat_str_list(list1, list2);
    ck_assert_int_eq(cmp_list(list1, exp_list), 0);

    free_list(&list1);
    free_list(&exp_list);
}
END_TEST



Suite *cat_str_list_suite(void)
{
    Suite *s;
    TCase *tc_pos; //, *tc_neg;

    s = suite_create("cat_str_list");
    tc_pos = tcase_create("positives");
    // tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_cat_str_list_cat_no_del_node);
    tcase_add_test(tc_pos, test_cat_str_list_cat_del_node);
    tcase_add_test(tc_pos, test_cat_str_list_one_node_list2);

    suite_add_tcase(s, tc_pos);
    // suite_add_tcase(s, tc_neg);

    return s;
}































