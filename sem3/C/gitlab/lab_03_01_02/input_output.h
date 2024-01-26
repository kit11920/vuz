#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>

#define N 10
#define M 10

/**
@brief Вводит матрицу
@param
a[][M] - матрица
a_n - указатель на количество строк матрицы
a_m - указатель на количество столбцов матрицы
@return код ошибки*/
int input_matrix(int a[][M], size_t *a_n, size_t *a_m);

/**
@brief Выводит массив
@param
a[a_size] - массив
a_size - размер массва
*/
void print_array(const int a[], size_t a_size);

#endif // INPUT_OUTPUT_H
