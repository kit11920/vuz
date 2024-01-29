#ifndef OPERATIONS_H__
#define OPERATIONS_H__

#include <stddef.h>
#include "inits.h"
#include "errs.h"

/// @brief Производит операцию стожения матрицы 1 и 2, записывет результат в матрицу mtrx_res
/// Выделяет память под матрицу mtrx_res
/// Если функция возвращает ошибку, то никаую память после нее очищать не надо
/// @param [in] mtrx1 - структура матрицы 1 (указатель)
/// @param [in] mtrx2 - структура матрицы 2 (указатель)
/// @param [out] mtrx_res - структура матрицы суммы (указатель)
/// @return код ошибки
int addition(struct mtrx_t *mtrx1, struct mtrx_t *mtrx2, struct mtrx_t *mtrx_res);

/// @brief Производит операцию умножения матрицы 1 и 2, записывет результат в матрицу mtrx_res
/// Выделяет память под матрицу mtrx_res
/// Если функция возвращает ошибку, то никаую память после нее очищать не надо
/// @param [in] mtrx1 - структура матрицы 1 (указатель)
/// @param [in] mtrx2 - структура матрицы 2 (указатель)
/// @param [out] mtrx_res - структура матрицы произведения (указатель)
/// @return код ошибки
int multiplication(struct mtrx_t *mtrx1, struct mtrx_t *mtrx2, struct mtrx_t *mtrx_res);

/// @brief Переставляет строки в матрицах так 
/// чтобы элемент с индексом [id, id] матрицы 1 имел ненулевое значение
/// @param [in out] mtrx1 - структура матрицы 1, у которой смотрим диагональный элемент (указатель)
/// @param [out] mtrx2 - структура матрицы у которой меняем строки в зависимости от матрицы 1 (указатель)
/// @param [in] id - индекс диагонального элемента
void make_nonzero_diadonal_el(struct mtrx_t *mtrx1, struct mtrx_t *mtrx2, size_t id);

/// @brief Заполняет диагональ матрицв единицами а ост нулями
/// @param [out] mtrx_res - структура матрицы произведения (указатель) 
void fill_id_1(struct mtrx_t *mtrx_res);

// /// @brief Приводим строки матрицы в изначальное состояние 
// /// (сортируем индексы строк матрицы по возрастанию, методом пузырек с флагом)
// /// @param [out] mtrx - структура матрицы (указатель)
// void rows_to_normal(struct mtrx_t *mtrx);

/// @brief Выделяем память под результирующую матрицу
/// Находит обратную матрицу методом элементарных преобразований
/// Если функция возвращает ошибку, то никаую память после нее очищать не надо
/// @param [in] mtrx1 - структура матрицы 1 (указатель) 
/// @param [out] mtrx_res - структура обратной матрицы (указатель)
/// @return код ошибки
int invert(struct mtrx_t *mtrx1, struct mtrx_t *mtrx_res);

/// @brief Сравнивает матрицы
/// @param [in] l_mtrx1 - структура матрицы (указатель) 
/// @param [in] r_mtrx - структура матрицы (указатель) 
/// @return Если матрицы однаковые возвращает - 0, если нет - 1
int compare_mtrxs(struct mtrx_t *l_mtrx1, struct mtrx_t *r_mtrx);

/// @brief Проверяет является ли матрица единичной
/// @param [in] mtrx - структура матрицы (указатель) 
/// @return Если да то возвращает - 0, если нет - 1
int if_mtrx_e(struct mtrx_t *mtrx);

#endif