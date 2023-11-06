#ifndef CHECK_H__
#define CHECK_H__

#include <stdlib.h>

/// @brief Проверяет верность сложения матриц в сжатом виде
/// @param rows - кол-во рядов в матрицах
/// @param cols - кол-во столбцов в матрицах
/// @param percent1 - процент заполненности матрицы 1
/// @param percent2 - процент заполненности матрицы 2
/// @param failed - кол-во проваленых тестов (увеличивает на 1 если данное сложение прошло не верно)
/// @return код ошибки
int check_addition(size_t rows, size_t cols, int percent1, int percent2, int *failed);

/// @brief Проверяет верность сложения матриц в сжатом виде для нескольких вариантов 
/// размерности матриц и заполненности их по процентам
/// @return код ошибки
int check_main(void);




#endif
