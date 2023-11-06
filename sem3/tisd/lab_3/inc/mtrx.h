#ifndef MTRX_ALLOC_H__
#define MTRX_ALLOC_H__

#include "stdlib.h"

struct standard_mtrx
{
    int **mtrx;
    size_t rows;
    size_t cols;
};

struct sparse_mtrx
{
    int *a;         // len_a
    int *ia;     // len_a
    int *ja;        // len - cols
    size_t len_a;
    size_t rows;
    size_t cols;
};


/// @brief Освобождает память из под динамической матрицы
/// @param [in] data - указатель на динамическую матрицу
/// @param [in] len_data - колво строк в динамической матице
void mtrx_free(int **data, size_t len_data);

/// @brief Выделение памяти под динамическую матрицу
/// @param [in] rows - кол-во строк в матрице
/// @param [in] cols - кол-во столбцов в матрице
/// @return указатель на динамическую матрицу
/// Возвращает NULL если память выделить не удалось
int **mtrx_alloc(size_t rows, size_t cols);

/// @brief Освобождение памяти из под структуры sparse_mtrx
/// @param sp_mtrx - структура sparse_mtrx (структура разреженной матрицы)
void sp_mtrx_free(struct sparse_mtrx *sp_mtrx);

/// @brief Выделение памяти под структуру разреженной матрицы
/// @param [out] sp_mtrx - структура разреженной матрицы (указатель)
/// @param [in] len_a_ia - длина массива a и ia в sp_mtrx (указатель)
/// @param [in] len_ja - длина массива j в sp_mtrx (указатель)
/// @return код ошибки
int sp_mtrx_alloc(struct sparse_mtrx *sp_mtrx, size_t len_a_ia, size_t len_ja);

/// @brief Заполнение структуры разреженной матрицы основываясь на временных частях той же структуры
/// @param [out] sp_mtrx - структура разреженной матрицы (указатель)
/// @param [in] a - массив значащих элементов матрицы
/// @param [in] ia - массив индексов строк значащих элементов матрицы соответствующий а 
/// @param [in] ja - массив индексов из массива а, где индекс элемента является элементов начала столбца матрицы )
/// @param [in] len_a_ia - длина массива a и ia 
/// @param [in] rows - колво строк в матрице всего
/// @param [in] cols - колво столбцов в матрице всего
void sp_mtrx_full_on_tmp_parts(struct sparse_mtrx *sp_mtrx, int *a, size_t *ia, int *ja, size_t len_a_ia, size_t rows, size_t cols);

/// @brief Выделение памяти под части структуры разреженной матрицы
/// Если выделить память под одну из частей не получилось то остальные очищаются автоматически
/// @param [in] rows - колво строк в матрице всего
/// @param [in] cols - колво столбцов в матрице всего
/// @param [out] a - массив значащих элементов матрицы (указатель)
/// @param [out] ia - массив индексов строк значащих элементов матрицы соответствующий а (указатель)
/// @param [out] ja - массив индексов из массива а, где индекс элемента является элементов начала столбца матрицы (указатель)
/// @return код ошибки
int alloc_tmp_max_size_sp_mtrx_parts(size_t rows, size_t cols, int **a, size_t **ia, int **ja);

/// @brief Заполнение частей структуры разреженной матрицы
/// @param [in] mtrx - структура разреженной матрицы (указатель)
/// @param [out] a - массив значащих элементов матрицы (указатель)
/// @param [out] ia - массив индексов строк значащих элементов матрицы соответствующий а (указатель)
/// @param [out] ja - массив индексов из массива а, где индекс элемента является элементов начала столбца матрицы (указатель)
/// @param [out] len_a_ia - длина массива a и ia (указатель)
void full_tmp_max_size_sp_mtrx_parts(struct standard_mtrx *mtrx, int *a, size_t *ia, int *ja, size_t *len_a_ia);

/// @brief Создает структуру разреженной матрицы (хранение матрицы в 3х обьектах) из структуры стандартной матрицы
/// Если функция вернула код ошибки то память после нее очищать не надо
/// @param [in] mtrx - структура стандартной матрицы (указатель)
/// @param [out] sp_mtrx - структура разреженной матрицы
/// @return код ошибки
int standard_mtrx_to_sparse(struct standard_mtrx *mtrx, struct sparse_mtrx *sp_mtrx);

/// @brief Переводит структуру рахраженной матрицы в стандарнтую матрицу
/// @param [in] sp_mtrx - структура разреженной матрицы (указатель)
/// @param [out] mtrx - структура стандартной матрицы (указатель)
void sparse_mtrx_to_standard(struct sparse_mtrx *sp_mtrx, struct standard_mtrx *mtrx);

#endif

