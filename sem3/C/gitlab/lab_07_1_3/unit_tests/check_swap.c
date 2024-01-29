#include <stdlib.h>
#include <check.h>
#include <string.h>

#include "array.h"


/// @brief меняет местами значения целых чисел
START_TEST(test_swap_int)
{
    int l = 1, r = 2;
    int save_l = l, save_r = r;

    swap(&l, &r, sizeof(int));

    ck_assert_int_eq(l, save_r);
    ck_assert_int_eq(r, save_l);
}
END_TEST

/// @brief меняет местами значения строк
START_TEST(test_swap_str)
{
    char l[] = "qwe", r[] = "asd";
    char save_l[] = "qwe", save_r[] = "asd";

    swap(&l, &r, sizeof(l));

    ck_assert_str_eq(l, save_r);
    ck_assert_str_eq(r, save_l);
}
END_TEST

struct film_t
{
    char first_letter[3];
    int year;
};

/// @brief меняет местами значения структур
START_TEST(test_swap_struct)
{
    struct film_t l, r, save_l, save_r;
    strcpy(l.first_letter, "q");
    l.year = 123;
    strcpy(r.first_letter, "as");
    r.year = 9;
    save_l = l;
    save_r = r;

    swap(&l, &r, sizeof(struct film_t));

    ck_assert_str_eq(l.first_letter, save_r.first_letter);
    ck_assert_str_eq(r.first_letter, save_l.first_letter);
    ck_assert_int_eq(l.year, save_r.year);
    ck_assert_int_eq(r.year, save_l.year);
}


Suite *swap_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("swap");
    tc_pos = tcase_create("positive");

    tcase_add_test(tc_pos, test_swap_int);
    tcase_add_test(tc_pos, test_swap_str);
    tcase_add_test(tc_pos, test_swap_struct);

    suite_add_tcase(s, tc_pos);

    return s;
}
