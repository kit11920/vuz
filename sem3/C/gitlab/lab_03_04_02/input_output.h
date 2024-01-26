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

#endif // INPUT_OUTPUT_H
