#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "limits.h"
#include "my_snprintf.h"

// Закомментированы те тесты которые для snprintf не компилируются но возможны для my_snprintf как ошибочные 

/// @brief В строке только %s 
START_TEST(test_my_snprintf_just_s)
{
    // char exp_str[] = "qw asa   qwe\n\n";
    const size_t str_size = 15;
    char str[str_size], exp_str[str_size];
    int lenstr, exp_lenstr;

    lenstr = my_snprintf(str, str_size, "%s%s%s%s%s", "qw as", "", "a", "   ", "qwe\n\n");
    exp_lenstr = snprintf(exp_str, str_size, "%s%s%s%s%s", "qw as", "", "a", "   ", "qwe\n\n");
    ck_assert_int_eq(lenstr, exp_lenstr);
    ck_assert_str_eq(str, exp_str);
}
END_TEST

/// @brief В строке только %llx
START_TEST(test_my_snprintf_just_llx)
{
    // char exp_str[] = "01a4d2ffffffffffffffff";
    const size_t str_size = 23;
    char str[str_size], exp_str[str_size];
    int lenstr, exp_lenstr;

    lenstr = my_snprintf(str, str_size, "%llx%llx%llx%llx%llx", 0llu, 1llu, 10llu, 1234llu, ULLONG_MAX);
    exp_lenstr = snprintf(exp_str, str_size, "%llx%llx%llx%llx%llx", 0llu, 1llu, 10llu, 1234llu, ULLONG_MAX);
    ck_assert_int_eq(lenstr, exp_lenstr);
    ck_assert_str_eq(str, exp_str);
}
END_TEST

/// @brief В строке %s %llx и другие символы
START_TEST(test_my_snprintf_s_llx_and_other)
{
    // char exp_str[] = "__qw 181cd qwerty";
    const size_t str_size = 18;
    char str[str_size], exp_str[str_size];
    int lenstr, exp_lenstr;

    lenstr = my_snprintf(str, str_size, "__%s %llx qwerty", "qw", 98765llu);
    exp_lenstr = snprintf(exp_str, str_size, "__%s %llx qwerty", "qw", 98765llu);
    ck_assert_int_eq(lenstr, exp_lenstr);
    ck_assert_str_eq(str, exp_str);
}
END_TEST

/// @brief В строке нет %s %llx
START_TEST(test_my_snprintf_without_s_llx)
{
    // char exp_str[] = "qwert y";
    const size_t str_size = 8;
    char str[str_size], exp_str[str_size];
    int lenstr, exp_lenstr;

    lenstr = my_snprintf(str, str_size, "qwert y");
    exp_lenstr = snprintf(exp_str, str_size, "qwert y");
    ck_assert_int_eq(lenstr, exp_lenstr);
    ck_assert_str_eq(str, exp_str);
    
}
END_TEST

// /// @brief Переданы лишние параметры для %s %llx
// START_TEST(test_my_snprintf_more_params)
// {
//     // char exp_str[] = "__qw 181cd qwerty";
//     const size_t str_size = 18;
//     char str[str_size], exp_str[str_size];
//     int lenstr, exp_lenstr;

//     lenstr = my_snprintf(str, str_size, "__%s %llx qwerty", "qw", 98765llu, 10llu, "e");
//     exp_lenstr = snprintf(exp_str, str_size, "__%s %llx qwerty", "qw", 98765llu, 10llu, "e");
//     ck_assert_int_eq(lenstr, exp_lenstr);
//     ck_assert_str_eq(str, exp_str);
    
// }
// END_TEST

// /// @brief format == ""
// START_TEST(test_my_snprintf_format_empty)
// {
//     // char exp_str[] = "";
//     const size_t str_size = 1;
//     char str[str_size], exp_str[str_size];
//     int lenstr, exp_lenstr;
//     char format[] = "";

//     lenstr = my_snprintf(str, str_size, format, 1);
//     exp_lenstr = snprintf(exp_str, str_size, format, 1);
//     ck_assert_int_eq(lenstr, exp_lenstr);
//     ck_assert_str_eq(str, exp_str);
    
// }
// END_TEST

/// @brief Под строку выделено больше памяти чем надо
START_TEST(test_my_snprintf_more_memory)
{
    // char exp_str[] = "qwerty";
    const size_t str_size = 7;
    char str[str_size], exp_str[str_size];
    int lenstr, exp_lenstr;

    lenstr = my_snprintf(str, str_size, "qwerty");
    exp_lenstr = snprintf(exp_str, str_size, "qwerty");
    ck_assert_str_eq(str, exp_str);
    ck_assert_int_eq(lenstr, exp_lenstr);
}
END_TEST

// /// @brief В строке % без спецефикатора
// START_TEST(test_my_snprintf_just_percent)
// {
//     const size_t str_size = 18;
//     char str[str_size], exp_str[str_size];
//     int lenstr, exp_lenstr;

//     lenstr = my_snprintf(str, str_size, "__% qwerty", "qw", 98765llu);
//     exp_lenstr = snprintf(exp_str, str_size, "__% qwerty", "qw", 98765llu);
//     ck_assert_int_eq(lenstr, exp_lenstr);
// }
// END_TEST

/// @brief Под строку выделено не достаточно памяти в строке нет %s %llx
START_TEST(test_my_snprintf_not_enough_mem_without_percent)
{
    // char exp_str[] = "qwer";
    const size_t str_size = 5;
    char str[str_size], exp_str[str_size];
    int lenstr, exp_lenstr;

    lenstr = my_snprintf(str, str_size, "qwerty");
    exp_lenstr = snprintf(exp_str, str_size, "qwerty");
    ck_assert_int_eq(lenstr, exp_lenstr);
    ck_assert_str_eq(exp_str, str);
}
END_TEST

/// @brief Под строку выделено не достаточно памяти в строке есть %s %llx
START_TEST(test_my_snprintf_not_enough_mem_with_percent)
{
    // char exp_str[] = "a MAX 36|";
    const size_t str_size = 10;
    char str[str_size], exp_str[str_size];
    int lenstr, exp_lenstr;

    lenstr = my_snprintf(str, str_size, "a %s %llx| qwert %s , %llx y", "MAX", 54llu, "A", 6llu);
    exp_lenstr = snprintf(exp_str, str_size, "a %s %llx| qwert %s , %llx y", "MAX", 54llu, "A", 6llu);
    // char *real_str = "a MAX 36| qwert A , 6 y";
    ck_assert_int_eq(lenstr, exp_lenstr); 
    ck_assert_str_eq(exp_str, str);
}
END_TEST

/// @brief Под строку выделено не достаточно памяти для заполнения %llx
START_TEST(test_my_snprintf_not_enough_mem_in_llx)
{
    // char exp_str[] = "75b";
    const size_t str_size = 4;
    char str[str_size], exp_str[str_size];
    int lenstr, exp_lenstr;
    char format[] = "%llx";

    lenstr = my_snprintf(str, str_size, format, 123456789llu);
    exp_lenstr = snprintf(exp_str, str_size, format, 123456789llu);
    // char *real_str = "75bcd15";
    ck_assert_int_eq(lenstr, exp_lenstr); 
    ck_assert_str_eq(exp_str, str);
}
END_TEST

/// @brief Под строку выделено не достаточно памяти для заполнения %s
START_TEST(test_my_snprintf_not_enough_mem_in_s)
{
    // char exp_str[] = "qw";
    const size_t str_size = 3;
    char str[str_size], exp_str[str_size];
    int lenstr, exp_lenstr;
    char format[] = "%s";

    lenstr = my_snprintf(str, str_size, format, "qwertyui");
    exp_lenstr = snprintf(exp_str, str_size, format, "qwertyui");
    // char *real_str = "qwertyui";
    ck_assert_int_eq(lenstr, exp_lenstr); 
    ck_assert_str_eq(exp_str, str);
}
END_TEST

/// @brief str == NULL
START_TEST(test_my_snprintf_str_null)
{
    size_t str_size = 0;
    char *str = NULL;
    int lenstr, exp_lenstr;

    lenstr = my_snprintf(str, str_size, "__%s %llx qwerty", "qw", 98765llu);
    exp_lenstr = snprintf(str, str_size, "__%s %llx qwerty", "qw", 98765llu);
    // char *real_str = "__qw 181cd qwerty";
    ck_assert_int_eq(lenstr, exp_lenstr);
}
END_TEST

/// @brief str_size == 0
START_TEST(test_my_snprintf_str_size_0)
{
    const size_t str_size = 8;
    char str[str_size], exp_str[str_size];
    int lenstr, exp_lenstr;

    lenstr = my_snprintf(str, 0, "qwert y");
    exp_lenstr = snprintf(exp_str, 0, "qwert y");
    ck_assert_int_eq(lenstr, exp_lenstr);
    
}
END_TEST

// /// @brief format == NULL
// START_TEST(test_my_snprintf_format_null)
// {
//     const size_t str_size = 18;
//     char str[str_size], exp_str[str_size];
//     int lenstr, exp_lenstr;
//     char *format = NULL;

//     lenstr = my_snprintf(str, str_size, format);
//     exp_lenstr = snprintf(exp_str, str_size, format);
//     ck_assert_int_eq(lenstr, exp_lenstr);
    
// }
// END_TEST


Suite *my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("my_snprintf");
    tc_pos = tcase_create("positives");
    tc_neg = tcase_create("negative");

    tcase_add_test(tc_pos, test_my_snprintf_just_llx);

    tcase_add_test(tc_pos, test_my_snprintf_just_s);
    
    tcase_add_test(tc_pos, test_my_snprintf_s_llx_and_other);
    tcase_add_test(tc_pos, test_my_snprintf_without_s_llx);
    // tcase_add_test(tc_pos, test_my_snprintf_format_empty);
    tcase_add_test(tc_pos, test_my_snprintf_more_memory);
    // tcase_add_test(tc_pos, test_my_snprintf_more_params);

    tcase_add_test(tc_neg, test_my_snprintf_str_null);
    tcase_add_test(tc_neg, test_my_snprintf_str_size_0);
    // tcase_add_test(tc_neg, test_my_snprintf_format_null);
    // tcase_add_test(tc_neg, test_my_snprintf_just_percent);
    tcase_add_test(tc_neg, test_my_snprintf_not_enough_mem_without_percent);
    tcase_add_test(tc_neg, test_my_snprintf_not_enough_mem_with_percent);
    tcase_add_test(tc_neg, test_my_snprintf_not_enough_mem_in_llx);
    tcase_add_test(tc_neg, test_my_snprintf_not_enough_mem_in_s);

    suite_add_tcase(s, tc_pos);
    suite_add_tcase(s, tc_neg);

    return s;
}




























