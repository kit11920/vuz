#include <stdlib.h>
#include <check.h>

#include "array.h"


/// @brief массив из 1 элемента
START_TEST(test_sort_arr_len_1)
{
    int exp_arr[1] = {1};
    int arr[1] = {1};
    size_t len_arr = 1;
    size_t elem_size = sizeof(int);

    mysort(arr, len_arr, elem_size, cmp_int);

    ck_assert_mem_eq(exp_arr, arr, len_arr * elem_size);
}
END_TEST

/// @brief массив из 2х элементов по возрастанию
START_TEST(test_sort_arr_len_2_sorted_up)
{
    int exp_arr[2] = {1, 2};
    int arr[2] = {1, 2};
    size_t len_arr = 2;
    size_t elem_size = sizeof(int);

    mysort(arr, len_arr, elem_size, cmp_int);

    ck_assert_mem_eq(exp_arr, arr, len_arr * elem_size);
}
END_TEST

/// @brief массив из 2х элементов по убыванию
START_TEST(test_sort_arr_len_2_sorted_down)
{
    int exp_arr[2] = {1, 2};
    int arr[2] = {2, 1};
    size_t len_arr = 2;
    size_t elem_size = sizeof(int);

    mysort(arr, len_arr, elem_size, cmp_int);

    ck_assert_mem_eq(exp_arr, arr, len_arr * elem_size);
}
END_TEST

/// @brief упорядоченный по возрастанию массив
START_TEST(test_sort_arr_sorted_up)
{
    int exp_arr[5] = {1, 2, 3, 4, 5};
    int arr[5] = {1, 2, 3, 4, 5};
    size_t len_arr = 5;
    size_t elem_size = sizeof(int);

    mysort(arr, len_arr, elem_size, cmp_int);

    ck_assert_mem_eq(exp_arr, arr, len_arr * elem_size);
}
END_TEST

/// @brief упорядоченный по убыванию массив
START_TEST(test_sort_arr_sorted_down)
{
    int exp_arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    size_t len_arr = 9;
    size_t elem_size = sizeof(int);

    mysort(arr, len_arr, elem_size, cmp_int);

    ck_assert_mem_eq(exp_arr, arr, len_arr * elem_size);
}
END_TEST

/// @brief случайный без повторов
START_TEST(test_sort_arr_unsorted_all_elems_diff)
{
    int exp_arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int arr[8] = {7, 8, 2, 1, 3, 5, 4, 6};
    size_t len_arr = 8;
    size_t elem_size = sizeof(int);

    mysort(arr, len_arr, elem_size, cmp_int);

    ck_assert_mem_eq(exp_arr, arr, len_arr * elem_size);
}
END_TEST

/// @brief случайный с повторами
START_TEST(test_sort_arr_unsorted_elems_not_all_diff)
{
    int exp_arr[9] = {-1, -1, 2, 2, 2, 3, 8, 9, 9};
    int arr[9] = {-1, 9, 8, -1, 9, 2, 3, 2, 2};
    size_t len_arr = 9;
    size_t elem_size = sizeof(int);

    mysort(arr, len_arr, elem_size, cmp_int);

    ck_assert_mem_eq(exp_arr, arr, len_arr * elem_size);
}
END_TEST

/// @brief сортирует строку
START_TEST(test_sort_arr_str)
{
    char arr[] = "ba";
    size_t len_arr = 2;
    size_t elem_size = sizeof(char);
    char exp_arr[] = "ab";

    mysort(arr, len_arr, elem_size, cmp_str);

    ck_assert_mem_eq(exp_arr, arr, len_arr * elem_size);
}
END_TEST


// Функции-тесты группируются в тестовые случаи (test case, TCase), а несколько
// тестовых случаев образуют тестовый набор (test suite, Suite).
Suite* mysort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции mysort
    s = suite_create("mysort");

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    // mysort для корректных параметров
    tc_pos = tcase_create("positives");

    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_sort_arr_len_1);
    tcase_add_test(tc_pos, test_sort_arr_len_2_sorted_up);
    tcase_add_test(tc_pos, test_sort_arr_len_2_sorted_down);
    tcase_add_test(tc_pos, test_sort_arr_sorted_up);
    tcase_add_test(tc_pos, test_sort_arr_sorted_down);
    tcase_add_test(tc_pos, test_sort_arr_unsorted_all_elems_diff);
    tcase_add_test(tc_pos, test_sort_arr_unsorted_elems_not_all_diff);

    tcase_add_test(tc_pos, test_sort_arr_str);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}


