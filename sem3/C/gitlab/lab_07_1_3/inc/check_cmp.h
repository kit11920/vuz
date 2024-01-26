#ifndef CHECK_CMP_H__
#define CHECK_CMP_H__

#include <check.h>


/* Тесты
test_cmp_int_l_more_r 
test_cmp_int_l_eq_r
test_cmp_int_l_less_r
*/
/// @brief Тестирование функции сравнения целых чисел
/// @return тестовый набор

Suite *cmp_int_suite(void);


/* Тесты
test_cmp_str_l_more_r  
test_cmp_str_l_eq_r 
test_cmp_str_l_less_r 
*/
/// @brief Тестирование функции сравнения строк
/// @return тестовый набор

Suite *cmp_str_suite(void);


#endif

