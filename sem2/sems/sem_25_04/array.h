#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdio.h>
#include "errors.h"

#define COUNT_MARKS 4

/**
@brief Считывает массив целых чисел
@param a[] - массив
@param a_n -длина массива
@return код ошибки
*/
int arr_read(int a[], size_t a_n);

/**
@brief Выводит массив целых чисел
@param a[] - массив
@param a_n -длина массива
*/
void arr_print(const int a[], size_t a_n);

/**
@brief Считает среднее значение массива целых чисел
@param a[] - массив
@param a_n -длина массива
@return Среднее значение
*/
double arr_calc_avg(const int a[], size_t a_n);

#endif
