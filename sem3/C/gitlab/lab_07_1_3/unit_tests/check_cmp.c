#include <stdlib.h>
#include <check.h>
#include <string.h>

#include "array.h"


/// @brief (l > r)
START_TEST(test_cmp_int_l_more_r)
{
    int l = 2, r = 1;
    int rc;

    rc = cmp_int(&l, &r);

    ck_assert_int_eq(rc, 1);
}
END_TEST

/// @brief (l == r)
START_TEST(test_cmp_int_l_eq_r)
{
    int l = 2, r = 2;
    int rc;

    rc = cmp_int(&l, &r);

    ck_assert_int_eq(rc, 0);
}
END_TEST

/// @brief (l < r)
START_TEST(test_cmp_int_l_less_r)
{
    int l = 1, r = 2;
    int rc;

    rc = cmp_int(&l, &r);

    ck_assert_int_eq(rc, -1);
}
END_TEST


Suite *cmp_int_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("cmp_int");
    tc_pos = tcase_create("positive");

    tcase_add_test(tc_pos, test_cmp_int_l_more_r);
    tcase_add_test(tc_pos, test_cmp_int_l_eq_r);
    tcase_add_test(tc_pos, test_cmp_int_l_less_r);

    suite_add_tcase(s, tc_pos);

    return s;
}

/// @brief (l > r)
START_TEST(test_cmp_str_l_more_r)
{
    char l[] = "qwe", r[] = "abc";

    int rc;
    rc = cmp_str(l, r);
    ck_assert_int_gt(rc, 0);
}
END_TEST

/// @brief (l == r)
START_TEST(test_cmp_str_l_eq_r)
{
    char l[] = "qwe", r[] = "qwe";

    int rc;
    rc = cmp_str(l, r);
    ck_assert_int_eq(rc, 0);
}
END_TEST

/// @brief (l < r)
START_TEST(test_cmp_str_l_less_r)
{
    char l[] = "az", r[] = "ba";

    int rc;
    rc = cmp_str(l, r);
    ck_assert_int_lt(rc, 0);
}
END_TEST

Suite *cmp_str_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("cmp_str");
    tc_pos = tcase_create("positive");

    tcase_add_test(tc_pos, test_cmp_str_l_more_r);
    tcase_add_test(tc_pos, test_cmp_str_l_eq_r);
    tcase_add_test(tc_pos, test_cmp_str_l_less_r);
    

    suite_add_tcase(s, tc_pos);

    return s;
}


