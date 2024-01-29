#include <stdlib.h>
#include <check.h>
#include <assert.h>


#include "errs.h"
#include "film.h"
#include "check_cmp.h"


// Сравнение по году, если l < r
START_TEST (test_cmp_by_year_l_lt_r)
{
    int rc = OK;
    struct film_t l, r;
    film_init_null(&l);
    film_init_null(&r);
    
    rc = film_init_content(&l, "qwe", "qwe", 1);
    assert(rc == OK);
    rc = film_init_content(&r, "qwe", "qwe", 2);
    assert(rc == OK);

    rc = film_cmp_by_year(&l, &r);
    ck_assert_int_lt(rc, 0);

    free_film(&l);
    free_film(&r);
} END_TEST

// Сравнение по году, если l == r
START_TEST (test_cmp_by_year_l_eq_r)
{
    int rc = OK;
    struct film_t l, r;
    film_init_null(&l);
    film_init_null(&r);
    
    rc = film_init_content(&l, "qwe", "qwe", 1);
    assert(rc == OK);
    rc = film_init_content(&r, "qwe", "qwe", 1);
    assert(rc == OK);

    rc = film_cmp_by_year(&l, &r);
    ck_assert_int_eq(rc, 0);

    free_film(&l);
    free_film(&r);
} END_TEST

// Сравнение по году, если l > r
START_TEST (test_cmp_by_year_l_gt_r)
{
    int rc = OK;
    struct film_t l, r;
    film_init_null(&l);
    film_init_null(&r);
    
    rc = film_init_content(&l, "qwe", "qwe", 10);
    assert(rc == OK);
    rc = film_init_content(&r, "qwe", "qwe", 2);
    assert(rc == OK);

    rc = film_cmp_by_year(&l, &r);
    ck_assert_int_gt(rc, 0);

    free_film(&l);
    free_film(&r);
} END_TEST

// Сравнение по названию, если l < r
START_TEST (test_cmp_by_title_l_lt_r)
{
    int rc = OK;
    struct film_t l, r;
    film_init_null(&l);
    film_init_null(&r);
    
    rc = film_init_content(&l, "a", "qwe", 10);
    assert(rc == OK);
    rc = film_init_content(&r, "b", "qwe", 2);
    assert(rc == OK);

    rc = film_cmp_by_title(&l, &r);
    ck_assert_int_lt(rc, 0);

    free_film(&l);
    free_film(&r);
} END_TEST

// Сравнение по названию, если l == r
START_TEST (test_cmp_by_title_l_eq_r)
{
    int rc = OK;
    struct film_t l, r;
    film_init_null(&l);
    film_init_null(&r);
    
    rc = film_init_content(&l, "a", "qwe", 10);
    assert(rc == OK);
    rc = film_init_content(&r, "a", "qwe", 2);
    assert(rc == OK);

    rc = film_cmp_by_title(&l, &r);
    ck_assert_int_eq(rc, 0);

    free_film(&l);
    free_film(&r);
} END_TEST

// Сравнение по названию, если l > r
START_TEST (test_cmp_by_title_l_gt_r)
{
    int rc = OK;
    struct film_t l, r;
    film_init_null(&l);
    film_init_null(&r);
    
    rc = film_init_content(&l, "z", "qwe", 10);
    assert(rc == OK);
    rc = film_init_content(&r, "b", "qwe", 2);
    assert(rc == OK);

    rc = film_cmp_by_title(&l, &r);
    ck_assert_int_gt(rc, 0);

    free_film(&l);
    free_film(&r);
} END_TEST

// Сравнение по имени режиссера, если l < r
START_TEST (test_cmp_by_name_l_lt_r)
{
    int rc = OK;
    struct film_t l, r;
    film_init_null(&l);
    film_init_null(&r);
    
    rc = film_init_content(&l, "zen", "a", 10);
    assert(rc == OK);
    rc = film_init_content(&r, "bb", "b", 2);
    assert(rc == OK);

    rc = film_cmp_by_name(&l, &r);
    ck_assert_int_lt(rc, 0);

    free_film(&l);
    free_film(&r);
} END_TEST

// Сравнение по имени режиссера, если l == r
START_TEST (test_cmp_by_name_l_eq_r)
{
    int rc = OK;
    struct film_t l, r;
    film_init_null(&l);
    film_init_null(&r);
    
    rc = film_init_content(&l, "zen", "aa a", 10);
    assert(rc == OK);
    rc = film_init_content(&r, "bb", "aa a", 2);
    assert(rc == OK);

    rc = film_cmp_by_name(&l, &r);
    ck_assert_int_eq(rc, 0);

    free_film(&l);
    free_film(&r);
} END_TEST

// Сравнение по имени режиссера, если l > r
START_TEST (test_cmp_by_name_l_gt_r)
{
    int rc = OK;
    struct film_t l, r;
    film_init_null(&l);
    film_init_null(&r);
    
    rc = film_init_content(&l, "zen", "bbb", 10);
    assert(rc == OK);
    rc = film_init_content(&r, "bb", "a", 2);
    assert(rc == OK);

    rc = film_cmp_by_name(&l, &r);
    ck_assert_int_gt(rc, 0);

    free_film(&l);
    free_film(&r);
} END_TEST


Suite* cmp_suite(void)
{
    Suite *s;
    TCase *tc_pos; //, *tc_neg;

    s = suite_create("cmp");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_cmp_by_year_l_lt_r);
    tcase_add_test(tc_pos, test_cmp_by_year_l_eq_r);
    tcase_add_test(tc_pos, test_cmp_by_year_l_gt_r);
    tcase_add_test(tc_pos, test_cmp_by_title_l_lt_r);
    tcase_add_test(tc_pos, test_cmp_by_title_l_eq_r);
    tcase_add_test(tc_pos, test_cmp_by_title_l_gt_r);
    tcase_add_test(tc_pos, test_cmp_by_name_l_lt_r);
    tcase_add_test(tc_pos, test_cmp_by_name_l_eq_r);
    tcase_add_test(tc_pos, test_cmp_by_name_l_gt_r);
    
    // tc_neg = tcase_create("negatives");
    // tcase_add_test(tc_neg, test_addition_neg_diff_size_mtrxs);

    suite_add_tcase(s, tc_pos);
    // suite_add_tcase(s, tc_neg);

    return s;
}
