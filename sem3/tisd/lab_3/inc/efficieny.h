#ifndef EFFICIENCY_H__
#define EFFICIENCY_H__

#include <stddef.h>

/// @brief Определяет время в мс в данный момент
/// @return время в мс в данный момент
unsigned long long ms_now(void);

/// @brief Определяет среднее значение в массиве t
/// @param [in] t - массив
/// @param [in] len_t - длина массива t
/// @return среднее значение в массиве t
double get_tavg(unsigned long long *t, size_t len_t);

/// @brief Определяет значение rse для значений записанный в массиве t
/// @param [in] t - массив
/// @param [in] len_t - длина массива t
/// @return rse
double get_rse(unsigned long long *t, size_t len_t);

/// @brief Определяет время затрачиваемое на сложение двух матриц в стандартном виде
/// @param [in] mtrx1 - матрица в стандартном виде
/// @param [in] mtrx2 - матрица в стандартном виде
/// @param [in] mtrx_res - матрица в стандартном виде результат сложения 1 и 2 матриц
/// @param [in] t - вспомагательный массив времени для сохранения результатов
/// @param [in] len_t - длина массива t
/// @param [out] time - время затрачиваемое на сложение двух матриц в стандартном виде
/// @return код ошибки
int gettime_addition_standart_mtrx(struct standard_mtrx *mtrx1, struct standard_mtrx *mtrx2, struct standard_mtrx *mtrx_res, unsigned long long *t, size_t len_t, long long *time);

/// @brief Определяет время затрачиваемое на сложение двух матриц в сжатом виде
/// @param [in] mtrx1 - матрица в сжатом виде
/// @param [in] mtrx2 - матрица в сжатом виде
/// @param [in] mtrx_res - матрица в сжатом виде результат сложения 1 и 2 матриц
/// @param [in] t - вспомагательный массив времени для сохранения результатов
/// @param [in] len_t - длина массива t
/// @param [out] time - время затрачиваемое на сложение двух матриц в сжатом виде
/// @return код ошибки
int gettime_addition_sparse_mtrx(struct sparse_mtrx *mtrx1, struct sparse_mtrx *mtrx2, struct sparse_mtrx *mtrx_res, unsigned long long *t, size_t len_t, long long *time);

/// @brief Считает сколько байтов занимает struct standard_mtrx
/// @param [in] rows - кол-во строк в матрице
/// @param [in] cols - кол-во столбцов в матрице
/// @return сколько байтов занимает struct standard_mtrx
size_t count_st_mtrx_bytes(size_t rows, size_t cols);

/// @brief Считает сколько байтов занимает struct sparse_mtrx
/// @param [in] mtrx - матрица в сжатом виде
/// @return сколько байтов занимает struct sparse_mtrx
size_t count_sp_mtrx_bytes(struct sparse_mtrx *mtrx);

/// @brief Выводит таблицу эффективности сложения матриц в сжатом и в стандартном виде 
/// по времени и по обьему занимаемой память 
/// @return код ошибки
int make_compare_table(void);

#endif
