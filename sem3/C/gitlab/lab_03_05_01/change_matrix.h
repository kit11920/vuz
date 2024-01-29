#ifndef CHANGE_MATRIX_H
#define CHANGE_MATRIX_H

#include <stdio.h>
#include "input_output.h"

/**
@brief Вычисляет сумму цифрт числа
Если число отрицательное воспринимаем его как положительное
@param Число num
@return Сумма цифр
*/
int sum_digits(int num);

/**
@brief Цикличестки сдвигает элементы массива влево на 3 позиции
@param
a[] - массив
a_n - длина массива
count_pos - количество позиций на который сдвигаем
@return
*/
void shift_elems(int a[], size_t a_n, int count_pos);

/**
@brief Элементы матрицы, сумма цифр которых > 10,
в порядке обхода матрицы по строками помещают в массив,
циклически сдвигают влево на 3, и возврадают элементы в матрицу
Количество подходящих элементов не может превысить размер массива
@param
mtrx[][M] - матрица
n - количество строк
m - колчество столбцов
@return код возврата
*/
int change_mtrx(int mtrx[][M], size_t n, size_t m);

#endif // CHANGE_MATRIX_H
