#include <stdlib.h>
#include <check.h>

#include "errs.h"
#include "node_list.h"
#include "list.h"
#include "help_check.h"
#include "str_list.h"

/// @brief Все пробелы единичные
START_TEST(test_del_2spaces_only_1_spaces)
{
    node_t *list, *exp_list;
    char str[] = "q w erty 123 4 2 5 ";
    char exp_str[] = "q w erty 123 4 2 5 ";

    ck_assert_int_eq(string_to_list(&list, str), OK);
    ck_assert_int_eq(string_to_list(&exp_list, exp_str), OK);

    del_2spaces(list);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(&list);
    free_list(&exp_list);
} 
END_TEST

/// @brief Пробелов нет
START_TEST(test_del_2spaces_no_spaces)
{
    node_t *list, *exp_list;
    char str[] = "qwerty";
    char exp_str[] = "qwerty";

    ck_assert_int_eq(string_to_list(&list, str), OK);
    ck_assert_int_eq(string_to_list(&exp_list, exp_str), OK);

    del_2spaces(list);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(&list);
    free_list(&exp_list);
} 
END_TEST

/// @brief Пробелов рядом больше 2х
START_TEST(test_del_2spaces_many_spaces_close)
{
    node_t *list, *exp_list;
    char str[] = "q          we   r t y";
    char exp_str[] = "q we r t y";

    ck_assert_int_eq(string_to_list(&list, str), OK);
    ck_assert_int_eq(string_to_list(&exp_list, exp_str), OK);

    del_2spaces(list);
    
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(&list);
    free_list(&exp_list);
} 
END_TEST

/// @brief Строка из 1 символа
START_TEST(test_del_2spaces_1_char)
{
    node_t *list, *exp_list;
    char str[] = "q";
    char exp_str[] = "q";

    ck_assert_int_eq(string_to_list(&list, str), OK);
    ck_assert_int_eq(string_to_list(&exp_list, exp_str), OK);

    del_2spaces(list);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(&list);
    free_list(&exp_list);
} 
END_TEST

/// @brief Строка состоит из пробелов
START_TEST(test_del_2spaces_all_spaces)
{
    node_t *list, *exp_list;
    char str[] = "                       ";
    char exp_str[] = " ";

    ck_assert_int_eq(string_to_list(&list, str), OK);
    ck_assert_int_eq(string_to_list(&exp_list, exp_str), OK);

    del_2spaces(list);
    ck_assert_int_eq(cmp_list(list, exp_list), 0);

    free_list(&list);
    free_list(&exp_list);
} 
END_TEST


Suite *del_2spaces_suite(void)
{
    Suite *s;
    TCase *tc_pos; //, *tc_neg;

    s = suite_create("del_2spaces");
    tc_pos = tcase_create("positives");
    // tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_del_2spaces_only_1_spaces);
    tcase_add_test(tc_pos, test_del_2spaces_no_spaces);
    tcase_add_test(tc_pos, test_del_2spaces_many_spaces_close);
    tcase_add_test(tc_pos, test_del_2spaces_1_char);
    tcase_add_test(tc_pos, test_del_2spaces_all_spaces);

    suite_add_tcase(s, tc_pos);
    // suite_add_tcase(s, tc_neg);

    return s;
}
