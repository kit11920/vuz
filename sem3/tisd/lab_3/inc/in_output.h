#ifndef IN_OUTPUT_H__
#define IN_OUTPUT_H__

#include "mtrx.h"

#define MAX_ROW_COL_TO_PRINT 10

/// @brief Вводит количество строк и столбцов в матрице
/// @param [in] rows - кол-во строк в матрице (указатель)
/// @param [in] cols - кол-во столбцов в матрице (указатель)
/// @return кол ошибки
int input_rows_cols(size_t *rows, size_t *cols);

/// @brief Вводит матрицу
/// @param [out] mtrx - mtrx - структура матрицы в стандартной форме (указатель)
/// @return код ошибки
int input_mtrx_standard(struct standard_mtrx *mtrx);

/// @brief Заполняет матрицу нулями
/// @param [out] mtrx - структура матрицы в стандартной форме (указатель)
void full_mtrx_zero(struct standard_mtrx *mtrx);

/// @brief Заполняет матрицу рандомными числами с процентом заполненности perc
/// @param [out] mtrx - mtrx - структура матрицы в стандартной форме
/// @param [in] perc - процент заполненности матрицы
/// @param [in] num - число для функции rand 
void input_mtrx_random(struct standard_mtrx *mtrx, int perc, unsigned int num);


/// @brief Выводит матрицу
/// @param [in] mtrx - структура матрицы в стандартной форме (указатель)
void print_mtrx_standart(struct standard_mtrx *mtrx);

/// @brief Вывод матрицы разряженного вида
/// @param [in] sp_mtrx - структура разреженной матрицы
void print_mtrx_sparse(struct sparse_mtrx *sp_mtrx);



#endif
