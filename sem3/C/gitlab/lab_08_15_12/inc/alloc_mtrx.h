#ifndef ALLOC_MTRX_H__
#define ALLOC_MTRX_H__

#include <stddef.h>
#include "inits.h"
#include "errs.h"

#define ROWS 10
#define COLS 10

// защита
// /// @brief Поиск указателя на начало болка памяти с данными
// /// @param [in] mtrx - структура матрицы (указатель) 
// /// @return указатель на данные
// double *find_pmin(struct mtrx_t *mtrx);

/// @brief Освобождает пармять из под матрицы и обнуляет значения строк и столбцов
/// @param [in out] mtrx - структура матрицы (указатель)
void free_mtrx(struct mtrx_t *mtrx);

/// @brief Выделение памяти под матрицу
/// Если память выделить не удалось, то данных матрицы присваивается значение NULL
/// @param [in out] mtrx - структура матрицы (указатель)
/// @param [in] rows - кол-во строк в матрице 
/// @param [in] cols - кол-во столбцов в матрице 
/// @return код ошибки
int alloc_mtrx_data(struct mtrx_t *mtrx, size_t rows, size_t cols);

/// @brief Копирует матрицы
/// Если память выделить не удалось, то данных матрицы присваивается значение NULL
/// @param [out] dst - структура матрицы куда копировать (указатель)
/// @param [in] src - структура матрицы что копировать (указатель)
/// @return код ошибки
int copy_mtrx(struct mtrx_t *dst, struct mtrx_t *src);

/// @brief Создает динамическую матрицу по статической и выделяет под нее память
/// @param [in] src - статическая матрица
/// @param [in] rows - кол-во строк в матрице src
/// @param [in] cols - кол-во столбцов в матрице src
/// @param [out] dst - структура динамической матрицы
/// @return код ошибки
int static_to_dynamic_mtrx(double src[][COLS], size_t rows, size_t cols, struct mtrx_t *dst);



#endif
