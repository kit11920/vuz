#ifndef CHANGE_MATRIX_H
#define CHANGE_MATRIX_H

#include <stdio.h>
#include "input_output.h"

/**
@brief Заполняет матрицу ходом быка, так чтобы внизу было минимальное число
Числа идут последовательно по нечетным слева столбцам вверх, а по четным вниз
Алгоритм:
Последовательно проходит по столбцам матрицы с конца и заполняет их:
Если direction = 1 то натуральные числа идут последовательно снизу вверх
если direction = -1 то натуральные числа идут последовательно сверху вниз
@param mtrx[N][M] - заполняемая матрица
*/
void input_matrix(int mtrx[][M], size_t n, size_t m);

#endif // CHANGE_MATRIX_H
