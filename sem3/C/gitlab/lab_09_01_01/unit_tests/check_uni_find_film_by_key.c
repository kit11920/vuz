#include <stdlib.h>
#include <check.h>
#include <assert.h>


#include "errs.h"
#include "film_array.h"
#include "film.h"
#include "check_uni_find_film_by_key.h"
#include "help_func_check.h"


/// @brief Поиск элемента по году 
START_TEST (test_search_by_year)
{
    int rc = OK;
    struct film_t film, *farr;
    film_init_null(&film);
    int index, exp_index;

    size_t len_arr = 5;
    uni_cmp_t cmp = film_cmp_by_year;

    char *titles[] = {"interesting film", "boring film", "qboring film", "eboring film", "aboring film"};
    char *names[] = {"Le man", "Le man", "Le man", "Le man", "Le man"};
    int years[] = {1, 2, 3, 4, 4};

    rc = create_arr_by_data(&farr, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // Инициализируем искомое поле
    rc = film_init_content(&film, "qwe", "qwe", 3);
    exp_index = 2;
    //

    index = uni_find_film_by_key(farr, len_arr, &film, cmp);
    ck_assert_int_eq(index, exp_index);

    free_farr(farr, len_arr);
    free_film(&film);

} END_TEST

/// @brief Поиск элемента по названию 
START_TEST (test_search_by_title)
{
    int rc = OK;
    struct film_t film, *farr;
    film_init_null(&film);
    int index, exp_index;

    size_t len_arr = 5;
    uni_cmp_t cmp = film_cmp_by_title;

    char *titles[] = {"a interesting film", "boring film", "cwow film", "d eboring film", "e aboring film"};
    char *names[] = {"Le man", "Le man", "Le man", "Le man", "Le man"};
    int years[] = {100, 232, 3, 4, 4};

    rc = create_arr_by_data(&farr, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // Инициализируем искомое поле
    rc = film_init_content(&film, "cwow film", "qwe", 3);
    exp_index = 2;
    //

    index = uni_find_film_by_key(farr, len_arr, &film, cmp);
    ck_assert_int_eq(index, exp_index);

    free_farr(farr, len_arr);
    free_film(&film);

} END_TEST

/// @brief Поиск элемента по имени 
START_TEST (test_search_by_name)
{
    int rc = OK;
    struct film_t film, *farr;
    film_init_null(&film);
    int index, exp_index;

    size_t len_arr = 5;
    uni_cmp_t cmp = film_cmp_by_name;

    char *titles[] = {"interesting film", "boring film", "qboring film", "eboring film", "aboring film"};
    char *names[] = {"aLe man", "b Le man", "cLe man", "d", "eLe man"};
    int years[] = {109, 92, 43, 4, 4};

    rc = create_arr_by_data(&farr, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // Инициализируем искомое поле
    rc = film_init_content(&film, "cwow film", "d", 3);
    exp_index = 3;
    //

    index = uni_find_film_by_key(farr, len_arr, &film, cmp);
    ck_assert_int_eq(index, exp_index);

    free_farr(farr, len_arr);
    free_film(&film);

} END_TEST

/// @brief Искомый элемент в начале 
START_TEST (test_searching_elem_at_beg)
{
    int rc = OK;
    struct film_t film, *farr;
    film_init_null(&film);
    int index, exp_index;

    size_t len_arr = 4;
    uni_cmp_t cmp = film_cmp_by_title;

    char *titles[] = {"ainteresting film", "boring film", "cqboring film", "deboring film"};
    char *names[] = {"aLe man", "b Le man", "cLe man", "d"};
    int years[] = {109, 92, 43, 4};

    rc = create_arr_by_data(&farr, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // Инициализируем искомое поле
    rc = film_init_content(&film, "ainteresting film", "d", 3);
    exp_index = 0;
    //

    index = uni_find_film_by_key(farr, len_arr, &film, cmp);
    ck_assert_int_eq(index, exp_index);

    free_farr(farr, len_arr);
    free_film(&film);

} END_TEST

/// @brief Искомый элемент в середине
START_TEST (test_searching_elem_at_middle)
{
    int rc = OK;
    struct film_t film, *farr;
    film_init_null(&film);
    int index, exp_index;

    size_t len_arr = 4;
    uni_cmp_t cmp = film_cmp_by_title;

    char *titles[] = {"ainteresting film", "bcca", "cqboring film", "deboring film"};
    char *names[] = {"aLe man", "b Le man", "cLe man", "d"};
    int years[] = {109, 92, 43, 4};

    rc = create_arr_by_data(&farr, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // Инициализируем искомое поле
    rc = film_init_content(&film, "bcca", "d", 3);
    exp_index = 1;
    //

    index = uni_find_film_by_key(farr, len_arr, &film, cmp);
    ck_assert_int_eq(index, exp_index);

    free_farr(farr, len_arr);
    free_film(&film);

} END_TEST

/// @brief Искомый элемент в конце
START_TEST (test_searching_elem_at_end)
{
    int rc = OK;
    struct film_t film, *farr;
    film_init_null(&film);
    int index, exp_index;

    size_t len_arr = 4;
    uni_cmp_t cmp = film_cmp_by_title;

    char *titles[] = {"ainteresting film", "bcca", "cqboring film", "ded"};
    char *names[] = {"aLe man", "b Le man", "cLe man", "d"};
    int years[] = {109, 92, 43, 4};

    rc = create_arr_by_data(&farr, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // Инициализируем искомое поле
    rc = film_init_content(&film, "ded", "d", 3);
    exp_index = 3;
    //

    index = uni_find_film_by_key(farr, len_arr, &film, cmp);
    ck_assert_int_eq(index, exp_index);

    free_farr(farr, len_arr);
    free_film(&film);

} END_TEST

/// @brief Искомых элементов несколько, вернет индекс первого
START_TEST (test_searching_elem_repeats)
{
    int rc = OK;
    struct film_t film, *farr;
    film_init_null(&film);
    int index, exp_index;

    size_t len_arr = 6;
    uni_cmp_t cmp = film_cmp_by_title;

    char *titles[] = {"ainteresting film", "bqwe", "casd", "zen", "zen", "zen"};
    char *names[] = {"aLe man", "b Le man", "cLe man", "d", "sdf", "er"};
    int years[] = {109, 92, 43, 4, 5, 3};

    rc = create_arr_by_data(&farr, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // Инициализируем искомое поле
    rc = film_init_content(&film, "zen", "d", 3);
    exp_index = 3;
    //

    index = uni_find_film_by_key(farr, len_arr, &film, cmp);
    ck_assert_int_eq(index, exp_index);

    free_farr(farr, len_arr);
    free_film(&film);

} END_TEST

/// @brief Искомых элементов нет
START_TEST (test_searching_elem_not)
{
    int rc = OK;
    struct film_t film, *farr;
    film_init_null(&film);
    int index, exp_index;

    size_t len_arr = 6;
    uni_cmp_t cmp = film_cmp_by_title;

    char *titles[] = {"ainteresting film", "bqwe", "casd", "zen", "zen", "zen"};
    char *names[] = {"aLe man", "b Le man", "cLe man", "d", "sdf", "er"};
    int years[] = {109, 92, 43, 4, 5, 3};

    rc = create_arr_by_data(&farr, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // Инициализируем искомое поле
    rc = film_init_content(&film, "zenny", "d", 3);
    exp_index = -1;
    //

    index = uni_find_film_by_key(farr, len_arr, &film, cmp);
    ck_assert_int_eq(index, exp_index);

    free_farr(farr, len_arr);
    free_film(&film);

} END_TEST

/// @brief В массиве 1 элемент
START_TEST (test_searching_elem_1)
{
    int rc = OK;
    struct film_t film, *farr;
    film_init_null(&film);
    int index, exp_index;

    size_t len_arr = 1;
    uni_cmp_t cmp = film_cmp_by_title;

    char *titles[] = {"interesting film"};
    char *names[] = {"aLe man"};
    int years[] = {109};

    rc = create_arr_by_data(&farr, titles, names, years, len_arr);
    ck_assert_int_eq(rc, OK);

    // Инициализируем искомое поле
    rc = film_init_content(&film, "zenny", "d", 3);
    exp_index = -1;
    //

    index = uni_find_film_by_key(farr, len_arr, &film, cmp);
    ck_assert_int_eq(index, exp_index);

    free_farr(farr, len_arr);
    free_film(&film);

} END_TEST

Suite* uni_find_film_by_key_suite(void)
{
    Suite *s;
    TCase *tc_pos; //, *tc_neg;

    s = suite_create("uni_find_film_by_key");

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_search_by_year);
    tcase_add_test(tc_pos, test_search_by_title);
    tcase_add_test(tc_pos, test_search_by_name);
    tcase_add_test(tc_pos, test_searching_elem_at_beg);
    tcase_add_test(tc_pos, test_searching_elem_at_middle);
    tcase_add_test(tc_pos, test_searching_elem_at_end);
    tcase_add_test(tc_pos, test_searching_elem_repeats);
    tcase_add_test(tc_pos, test_searching_elem_not);
    tcase_add_test(tc_pos, test_searching_elem_1);
    
    // tc_neg = tcase_create("negatives");
    // tcase_add_test(tc_neg, test_addition_neg_diff_size_mtrxs);

    suite_add_tcase(s, tc_pos);
    // suite_add_tcase(s, tc_neg);

    return s;
}
