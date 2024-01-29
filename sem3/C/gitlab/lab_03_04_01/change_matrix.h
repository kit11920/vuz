#ifndef CHANGE_MATRIX_H
#define CHANGE_MATRIX_H

#include <stdio.h>
#include "input_output.h"

/**
@brief Меняет местами элементы массивов начиная с элемента с индексом st и заканчивая индексом end включительно
Предполагается что
- индексы st, end входят в размер массивов a[], b[]
- массивы a[], b[] существуют
@param
a[], b[] - массивы
st - индекс начала изменений
end - индекс конца изменений
*/
void change_arrs_st_end(int a[], int b[], size_t st, size_t end);

/**
@brief Меняет местами элементы частей строк матрицы над диагоналями и под
@param
mtrx[][M] - изменяемая матрица
n - колво строк матрицы
*/
void change_matrix(int mtrx[][M], size_t n);

#endif // CHANGE_MATRIX_H
