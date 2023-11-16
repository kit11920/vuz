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








int make_compare_table(void);




#endif
