#ifndef GET_ARRAY_H
#define GET_ARRAY_H

#include <stdio.h>
#include <stdbool.h>
#include "input_output.h"

/**
@brief Чередуются ли в k-ом столбце положительные и отрицательные элементы
@param
a[][M] - матрица
a_n - количество строк матрицы
k - номер столбца который проверяем
Этот номер всегда не больше чем солбцов матрицы
@return true/false */
bool if_plus_minus_col(int a[][M], size_t a_n, size_t k);

/**
@brief k-тому элементу массива arr присваивается 1
если выполняется условие if_plus_minus_col и 0 если нет
@param
matrix[][M] - матрица
matrix_n - количество строк матрицы
matrix_m - количество столбцов матрицы
arr[] - массив
@return код ошибки
*/
void get_array(int matrix[][M], size_t matrix_n, size_t matrix_m, int arr[]);

#endif // GET_ARRAY_H
