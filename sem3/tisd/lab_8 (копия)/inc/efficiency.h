#ifndef EFFICIENCY_H__
#define EFFICIENCY_H__

#include <stdlib.h>

/// @brief Возвращает время сейчас в мкс
/// @return время сейчас в мкс
unsigned long long ms_now(void);

/// @brief Считает среднее в массиве
/// @param t массив замеров времени
/// @param len_t размер массива
/// @return среднее
double get_tavg(unsigned long long *t, size_t len_t);

/// @brief Считает RSE
/// @param t массив замеров времени
/// @param len_t размер массива
/// @return RSE
double get_rse(unsigned long long *t, size_t len_t);











#endif

