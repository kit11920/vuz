#ifndef SORT_MATRIX_H
#define SORT_MATRIX_H

#include <stdio.h>
#include "input_output.h"

/**
@brief Присваивает массиву a массив b, поэлементно
массивы не пустые и имеют одинаковый рамер
@param массив a, массив b, их рамер n
*/
/*
void assigning_arr_to_arr(int a[], const int b[], size_t n);
*/

/**
@brief Меняем местами значения двух матриц
@param
a[], b[] - матрицы у которых менем значения
m - размер этих матриц
*/
void change_place_arrs(int a[], int b[], size_t m);

/**
@brief Находит произведение элементов массива
@param Массив a, его рамер a_n
@return Произведение элементов массива
*/
int product_of_arr_nums(const int a[], size_t a_n);

/**
@brief сортирует строки матрицы (метод пузырьком)
@param
mtrx[][M] - матрица
n - количество строк
m - колчество столбцов
*/
void sort_matrix(int mtrx[][M], size_t n, size_t m);

#endif // SORT_MATRIX_H
