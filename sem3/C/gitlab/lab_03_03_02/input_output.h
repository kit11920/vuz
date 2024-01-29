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
int input_matrix(int mtrx[][M], size_t *n, size_t *m);

/**
@brief Выводит матрицу
@param
mtrx[][M] - матрица
n - количество строк
m - колчество столбцов
*/
void print_matrix(int mtrx[][M], size_t n, size_t m);

#endif // INPUT_OUTPUT_H
