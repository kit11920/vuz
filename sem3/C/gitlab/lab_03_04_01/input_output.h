#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>

#define N 10
#define M 10

/**
@brief Вводит матрицу
@param
mtrx[][M] - матрица
n - указатель на количество строк
m - указатель на колчество столбцов
@return код ошибки
*/
int input_matrix(int a[][M], size_t *a_n, size_t *a_m);

/**
@brief Выводит матрицу
@param
a[][M] - матрица
a_n - количество строк матрицы
a_m - количество столбцов матрицы
*/
void print_matrix(int a[][M], size_t a_n, size_t a_m);

#endif // INPUT_OUTPUT_H
