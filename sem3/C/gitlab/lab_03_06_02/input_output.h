#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>

#define N 10
#define M 10

/**
@brief Выводит матрицу
@param a[N][M] - выводимая матрица
*/
void print_matrix(int a[][M], size_t a_n, size_t a_m);

/**
@brief Водит количество строк и стобцов
@param a_n - ссылка на количества строк
a_m - ссылка на количества столбцов
*/
int input_mtrx_nm(size_t *a_n, size_t *a_m);

#endif // INPUT_OUTPUT_H
