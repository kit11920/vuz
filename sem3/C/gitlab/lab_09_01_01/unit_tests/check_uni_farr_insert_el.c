#include <stdlib.h>
#include <check.h>
#include <assert.h>


#include "errs.h"
#include "film_array.h"
#include "film.h"
#include "check_uni_farr_insert_el.h"
#include "help_func_check.h"

/// @brief Массив вводится отсортированным по году (рандомный порядок)
START_TEST (test_sort_year)
{
    int rc = OK;
    struct film_t *farr, *data;
    

    const size_t len_arr = 5;
    uni_cmp_t cmp = film_cmp_by_year;

    // Выделяем память под массивы структур
    farr = calloc(len_arr, sizeof(struct film_t));
    assert(farr != NULL);;
    //

    char *titles[] = {"interesting film", "boring film", "boring film", "boring film", "boring film"};
    char *names[] = {"Le man", "Le man", "Le man", "Le man", "Le man"};
    int years[] = {2003, 3, 1000, 1, 2020};

    rc = create_arr_by_data(&data, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // добавляем сруктуры дынных в отсортированный массив 
    for (size_t i = 0; i < len_arr; i++)
        uni_farr_insert_el(farr, i, &data[i], cmp);
    //

    ck_assert_int_eq(if_arr_sorted(farr, len_arr, cmp), 0);

    free_farr(farr, len_arr);
    free_farr(data, len_arr);

} END_TEST

/// @brief Массив вводится отсортированным по названию (рандомный порядок)
START_TEST (test_sort_title)
{
    int rc = OK;
    struct film_t *farr, *data;
    

    size_t len_arr = 3;
    uni_cmp_t cmp = film_cmp_by_title;
    

    // Выделяем память под массивы структур
    farr = calloc(len_arr, sizeof(struct film_t));
    assert(farr != NULL);
    //

    char *titles[] = {"interesting film", "amazing film", "boring film"};
    char *names[] = {"Le man", "Le man", "Le man"};
    int years[] = {2003, 3, 1000};

    rc = create_arr_by_data(&data, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // добавляем сруктуры дынных в отсортированный массив 
    for (size_t i = 0; i < len_arr; i++)
        uni_farr_insert_el(farr, i, &data[i], cmp);
    //

    ck_assert_int_eq(if_arr_sorted(farr, len_arr, cmp), 0);

    free_farr(farr, len_arr);
    free_farr(data, len_arr);

} END_TEST

/// @brief Массив вводится отсортированным по имени (рандомный порядок)
START_TEST (test_sort_name)
{
    int rc = OK;
    struct film_t *farr, *data;
    

    size_t len_arr = 4;
    uni_cmp_t cmp = film_cmp_by_name;
    

    // Выделяем память под массивы структур
    farr = calloc(len_arr, sizeof(struct film_t));
    assert(farr != NULL);
    //

    char *titles[] = {"interesting film", "amazing film", "boring film", "wow film"};
    char *names[] = {"a", "c", "b", "q"};
    int years[] = {2003, 3, 1000, 1};

    rc = create_arr_by_data(&data, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // добавляем сруктуры дынных в отсортированный массив 
    for (size_t i = 0; i < len_arr; i++)
        uni_farr_insert_el(farr, i, &data[i], cmp);
    //

    ck_assert_int_eq(if_arr_sorted(farr, len_arr, cmp), 0);

    free_farr(farr, len_arr);
    free_farr(data, len_arr);

} END_TEST

/// @brief Массив вводится отсортированным по году (2 элемента по убыванию)
START_TEST (test_sort_2_elem_down)
{
    int rc = OK;
    struct film_t *farr, *data;
    

    size_t len_arr = 2;
    uni_cmp_t cmp = film_cmp_by_year;

    // Выделяем память под массивы структур
    farr = calloc(len_arr, sizeof(struct film_t));
    assert(farr != NULL);
    //

    char *titles[] = {"interesting film", "amazing film"};
    char *names[] = {"Le man", "q"};
    int years[] = {2003, 1};

    rc = create_arr_by_data(&data, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // добавляем сруктуры дынных в отсортированный массив 
    for (size_t i = 0; i < len_arr; i++)
        uni_farr_insert_el(farr, i, &data[i], cmp);
    //

    ck_assert_int_eq(if_arr_sorted(farr, len_arr, cmp), 0);

    free_farr(farr, len_arr);
    free_farr(data, len_arr);

} END_TEST

/// @brief Массив вводится отсортированным по году (2 элемента по возрастанию)
START_TEST (test_sort_2_elem_up)
{
    int rc = OK;
    struct film_t *farr, *data;
    

    size_t len_arr = 2;
    uni_cmp_t cmp = film_cmp_by_year;

    // Выделяем память под массивы структур
    farr = calloc(len_arr, sizeof(struct film_t));
    assert(farr != NULL);
    //

    char *titles[] = {"interesting film", "amazing film"};
    char *names[] = {"Le man", "q"};
    int years[] = {2003, 100000};

    rc = create_arr_by_data(&data, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // добавляем сруктуры дынных в отсортированный массив 
    for (size_t i = 0; i < len_arr; i++)
        uni_farr_insert_el(farr, i, &data[i], cmp);
    //

    ck_assert_int_eq(if_arr_sorted(farr, len_arr, cmp), 0);

    free_farr(farr, len_arr);
    free_farr(data, len_arr);

} END_TEST

/// @brief Массив вводится отсортированным по году (по убыванию)
START_TEST (test_sort_down)
{
    int rc = OK;
    struct film_t *farr, *data;
    

    size_t len_arr = 3;
    uni_cmp_t cmp = film_cmp_by_year;

    // Выделяем память под массивы структур
    farr = calloc(len_arr, sizeof(struct film_t));
    assert(farr != NULL);
    //

    char *titles[] = {"interesting film", "amazing film", "sdf"};
    char *names[] = {"Le man", "q", "we"};
    int years[] = {2003, 10, 1};

    rc = create_arr_by_data(&data, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // добавляем сруктуры дынных в отсортированный массив 
    for (size_t i = 0; i < len_arr; i++)
        uni_farr_insert_el(farr, i, &data[i], cmp);
    //

    ck_assert_int_eq(if_arr_sorted(farr, len_arr, cmp), 0);

    free_farr(farr, len_arr);
    free_farr(data, len_arr);

} END_TEST

/// @brief Массив вводится отсортированным по году (по возрастанию)
START_TEST (test_sort_up)
{
    int rc = OK;
    struct film_t *farr, *data;
    

    size_t len_arr = 4;
    uni_cmp_t cmp = film_cmp_by_year;

    // Выделяем память под массивы структур
    farr = calloc(len_arr, sizeof(struct film_t));
    assert(farr != NULL);
    //

    char *titles[] = {"interesting film", "amazing film", "dfg", "sd"};
    char *names[] = {"Le man", "q", "wer", "ert"};
    int years[] = {1, 2, 3, 4};

    rc = create_arr_by_data(&data, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // добавляем сруктуры дынных в отсортированный массив 
    for (size_t i = 0; i < len_arr; i++)
        uni_farr_insert_el(farr, i, &data[i], cmp);
    //

    ck_assert_int_eq(if_arr_sorted(farr, len_arr, cmp), 0);

    free_farr(farr, len_arr);
    free_farr(data, len_arr);

} END_TEST

/// @brief Массив вводится отсортированным по году (1 элемент)
START_TEST (test_sort_1_elem)
{
    int rc = OK;
    struct film_t *farr, *data;
    

    size_t len_arr = 1;
    uni_cmp_t cmp = film_cmp_by_year;

    // Выделяем память под массивы структур
    farr = calloc(len_arr, sizeof(struct film_t));
    assert(farr != NULL);
    //

    char *titles[] = {"interesting film"};
    char *names[] = {"Le man"};
    int years[] = {2003};

    rc = create_arr_by_data(&data, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // добавляем сруктуры дынных в отсортированный массив 
    for (size_t i = 0; i < len_arr; i++)
        uni_farr_insert_el(farr, i, &data[i], cmp);
    //

    ck_assert_int_eq(if_arr_sorted(farr, len_arr, cmp), 0);

    free_farr(farr, len_arr);
    free_farr(data, len_arr);

} END_TEST

/// @brief Массив вводится отсортированным по году (рандомный порядок с повторами)
START_TEST (test_sort_with_repeat)
{
    int rc = OK;
    struct film_t *farr, *data;
    

    size_t len_arr = 5;
    uni_cmp_t cmp = film_cmp_by_year;

    // Выделяем память под массивы структур
    farr = calloc(len_arr, sizeof(struct film_t));
    assert(farr != NULL);
    //

    char *titles[] = {"interesting film", "amazing film", "boring film", "wow film", "q"};
    char *names[] = {"a", "c", "b", "q", "we"};
    int years[] = {2003, 3, 1000, 1000, 3};

    rc = create_arr_by_data(&data, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // добавляем сруктуры дынных в отсортированный массив 
    for (size_t i = 0; i < len_arr; i++)
        uni_farr_insert_el(farr, i, &data[i], cmp);
    //

    ck_assert_int_eq(if_arr_sorted(farr, len_arr, cmp), 0);

    free_farr(farr, len_arr);
    free_farr(data, len_arr);

} END_TEST

Suite* unit_farr_insert_el_suite(void)
{
    Suite *s;
    TCase *tc_pos; //, *tc_neg;

    s = suite_create("unit_farr_insert_el");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_sort_year);
    tcase_add_test(tc_pos, test_sort_title);
    tcase_add_test(tc_pos, test_sort_name);
    tcase_add_test(tc_pos, test_sort_2_elem_down);
    tcase_add_test(tc_pos, test_sort_2_elem_up);
    tcase_add_test(tc_pos, test_sort_down);
    tcase_add_test(tc_pos, test_sort_up);
    tcase_add_test(tc_pos, test_sort_1_elem);
    tcase_add_test(tc_pos, test_sort_with_repeat);
    
    // tc_neg = tcase_create("negatives");
    // tcase_add_test(tc_neg, test_addition_neg_diff_size_mtrxs);

    suite_add_tcase(s, tc_pos);
    // suite_add_tcase(s, tc_neg);

    return s;
}

