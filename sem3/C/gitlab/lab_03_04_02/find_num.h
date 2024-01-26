#include <stdio.h>
#include <stdbool.h>
#include "input_output.h"

#ifndef FIND_NUM_H
#define FIND_NUM_H

/**
@brief Определяет заканчивается ли число на цифру 5
@param Число num
@return true если заканчивается
*/
bool if_num_end_5(int num);

/**
@brief Находит максимальное число заканчивающееся на цифру 5
и расположено под побочной диагональю
@param
mtrx[][M] - матрица
n - количество строк
m - колчество столбцов
max_num - переменная к котрую положим максимальное число
@return код ошибки
*/
int find_max_num_end_5(int mtrx[][M], size_t n, size_t m, int *max_num);

#endif // FIND_NUM_H
