#ifndef OPERATIONS_H__
#define OPERATIONS_H__

#include <stddef.h>
#include "mtrx.h"

/// @brief Сложение матриц 1 и 2 в стандартном виде
/// @param [in] mtrx1 - структура стандартной матрицы 1
/// @param [in] mtrx2 - структура стандартной матрицы 2
/// @param [out] out_mtrx - структура стандартной матрицы - результата сложения
void addition_standart_mtrx(struct standard_mtrx *mtrx1, struct standard_mtrx *mtrx2, struct standard_mtrx *out_mtrx);

/// @brief Находит и возвращает индекс в массиве ia, который является первым элементом в следующем столбце после столбца j
/// @param [in] mtrx - структура разреженной матрицы (указатель)
/// @param [in] j - индекс столбца у которого ищем последний элемент
/// @return индекс
size_t find_end_col(struct sparse_mtrx *mtrx, size_t j);

/// @brief Сложение матриц записанных в три элемента (как структура разреженной матрицы)
/// @param [in] mtrx1 - структура разреженной матрицы 1 (указатель)
/// @param [in] mtrx2 - структура разреженной матрицы 2 (указатель)
/// @param [out] out_mtrx - структура разреженной матрицы являющаяся результатом сложения(указатель)
/// @return 
int addition_sparse_mtrx(struct sparse_mtrx *mtrx1, struct sparse_mtrx *mtrx2, struct sparse_mtrx *out_mtrx);

/// @brief Проверяем одинаковые ли матрицы
/// @param [in] mtrx1 - структура стандартной матрицы 1
/// @param [in] mtrx2 - структура стандартной матрицы 2
/// @return 1 - если одинаковые, 0 - если нет
_Bool cmp_mtrx(struct standard_mtrx *mtrx1, struct standard_mtrx *mtrx2);

#endif
