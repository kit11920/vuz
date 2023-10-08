#ifndef ARITHMETIC_H__
#define ARITHMETIC_H__

#include <stdlib.h>


/// @brief Выводит мантиссу 
/// @param [in] mantissa - массив мантиссы
/// @param [in] len_arr - длина массива
void print_mantissa(const unsigned short mantissa[], size_t len_arr);


/// @brief Округляет мантиссу числа до LEN_MANTISSA знаков
/// Цифры записываются в мантису в обратном порядке - в массиве старшие разряды расположены справа
/// @param [out] num - массив мантисс
/// @param [out] len_arr - длина массива
/// @param [out] k - указатель на порядок
void round_num(unsigned short num[], size_t *len_arr, int *k);


/// @brief Умножение длинного числа на цифру
/// Цифры записываются в мантису в обратном порядке - в массиве старшие разряды расположены справа
/// @param [in] long_num - массив мантисы длинного числа
/// @param [in] len_long_arr - длина массива long_num
/// @param [in] short_num - короткое число
/// @param [out] res_num - массив мантисы результата умножения
/// @param [out] len_res_arr - длина массива res_num
void multiplication_long_by_short_num(const unsigned short long_num[], const size_t len_long_arr, 
const unsigned short short_num, unsigned short res_num[], size_t *len_res_arr);


/// @brief Сравнение мантисс чисел. Возвращает:
/// >0 - num1 > num2
/// 0 - num1 == num2
/// <0 - num1 < num2
/// Цифры записываются в мантису в обратном порядке - в массиве старшие разряды расположены справа
/// @param [in] num1 - массив мантисы числа num1
/// @param [in] len_arr1 - длина массива num1
/// @param [in] num2 - массив мантисы числа num2
/// @param [in] len_arr2 - длина массива num1
/// @return Результат сравнения
/// >0  num1 > num2
/// 0 - num1 == num2
/// <0 - num1 < num2
int cmp_nums(const unsigned short num1[], const size_t len_arr1, const unsigned short num2[], const size_t len_arr2);


/// @brief  Вычитаем из мантиссы num1 мантиссу num2 и записываем результат в res_num
/// Предполагается что число num1 >= num2
/// @param [in] num1 - массив мантисы числа num1
/// @param [in] len_arr1 - длина массива num1
/// @param [in] num2 - массив мантисы числа num2
/// @param [in] len_arr2 - длина массива num2
/// @param [out] res_num - массив мантисы результата умножения
/// @param [out] len_res_arr - длина массива res_num
void num1_minus_num2(const unsigned short num1[], const size_t len_arr1, const unsigned short num2[], const size_t len_arr2, 
unsigned short res_num[], size_t *len_res_arr);


/// @brief Деление таких чисел что частное это цифра + остаток
/// Цифры записываются в мантису в обратном порядке - в массиве старшие разряды расположены справа
/// @param [in] num1 - массив мантисы числа num1
/// @param [in] len_arr1 длина массива num1
/// @param [in] num2 - массив мантисы числа num2
/// @param [in] len_arr2 длина массива num2
/// @param [out] integer целая часть деления - цифра
/// @param [out] rest  - массив мантисы остатка
/// @param [out] len_rest_arr - длина массива rest
void division_for_one_digit_and_rest(const unsigned short num1[], const size_t len_arr1, 
const unsigned short num2[], const size_t len_arr2, 
unsigned short *integer, unsigned short rest[], size_t *len_rest_arr);


/// @brief Добавляет нули в конец первого числа (делимого) для деления
/// @param [in] num1 - структура числа делимого
/// @param [in] num2 - структура числа делителя
/// @param [out] count_added - количсетво добавленных нулей
void longer_num_for_division(struct number_t *num1, const struct number_t *num2, int *count_added);


/// @brief Добавляет цифру integer в начало массивы мантисы 
/// @param [in out] mantissa - массив мантисы числа
/// @param [in out] len_arr - длина массива mantissa
/// @param [in] integer - добавляемая цифра
void add_integet_to_mantissa(unsigned short mantissa[], size_t *len_arr, const unsigned short integer);


/// @brief Деление длинных чисел: num1 / num2 = num3
/// @param [in] num1 - структура числа делимого
/// @param [in] num2 - структура числа делителя
/// @param [out] num3 - структура числа результата деления
/// @return 
int division(const struct number_t *num1, const struct number_t *num2, struct number_t *num3);


#endif
