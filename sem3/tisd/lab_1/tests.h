#ifndef TESTS_H__
#define TESTS_H__

#include "number.h"


/// @brief Записывает число в строку в нормальном виде
/// @param [in] num - структура числа
/// @param [out] buf - строка
void print_num_to_str(const struct number_t *num, char *buf);


/// @brief Сравнивает результат функции get_number_from_str с ожидаемым при подаче на вход строки input_str
/// @param [in] input_str Строка поданная на вход
/// @param [in] expected_output Ожидаемая строка на выходе
/// @param [in] expected_rc Ожидаемый код возврата
void test_get_number_from_str(const char *input_str, const char *expected_output, int expected_rc);


/// @brief Проводит тестирование функции get_number_from_str
void all_tests_get_number_from_str();


#endif
