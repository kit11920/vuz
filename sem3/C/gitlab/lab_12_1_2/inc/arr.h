#ifndef ARR_H__
#define ARR_H__

#include <stdlib.h>


/// @brief Сдвигает циклически массив влево на k позиций
/// если k < 0, то сдвигается вправо
/// @param [in out] arr массив
/// @param [in] len_arr длина массива
/// @param [in] k на сколько позиций сдвинуть
/// @return код ошибки [ERR_PARAM]
int k_shift_arr(int arr[], size_t len_arr, int k);

/// @brief Из массива src помещает в dst, элементы которые являются полным квадратом
/// если dst == NULL то просто вычисляет размер выходного массива
/// @param src исходный массив
/// @param len_src длина исходного массива
/// @param dst массив полных квадратом
/// @param len_dst длина массива полных квадратов, 
/// преобразуется к размеру массива dst который должен получиться
/// @return код ошибки [ERR_PARAM]
int make_sqrt_arr(int src[], size_t len_src, int dst[], size_t *len_dst);



























#endif


