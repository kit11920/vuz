#ifndef ACTIONS_H__
#define ACTIONS_H__

#include "mtrx.h"

/// @brief Заполнение матрицы, с выбором способа ввода
/// @param [out] mtrx - структура матрицы в стандартной форме (указатель)
/// @return код ошибки
int act_input_mtrx(struct standard_mtrx *mtrx);

/// @brief Осужествляет действие сложения матриц, взаимодействуя с пользователем
/// @return код ошибки
int act_addition();


#endif
