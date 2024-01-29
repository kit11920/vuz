#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

#include "errs.h"

/// @brief Сдвигает циклически массив влево на 1
/// @param [in out] arr массив
/// @param [in] len_arr длина массива
static void left_one_shift_arr(int arr[], size_t len_arr)
{
    assert(arr != NULL && len_arr != 0);

    int tmp = arr[0];
    for (size_t i = 0; i < len_arr - 1; i++)
        arr[i] = arr[i + 1];
    arr[len_arr - 1] = tmp;
}

/// @brief Сдвигает циклически массив вправо на 1
/// @param [in out] arr массив
/// @param [in] len_arr длина массива
static void right_one_shift_arr(int arr[], size_t len_arr)
{
    assert(arr != NULL && len_arr != 0);

    int tmp = arr[len_arr - 1];
    for (int i = len_arr - 1; i > 0; i--)
        arr[i] = arr[i - 1];
    arr[0] = tmp;
}


int k_shift_arr(int arr[], size_t len_arr, int k)
{
    if (arr == NULL || len_arr == 0)
        return ERR_PARAM;
    if (k == 0 || len_arr == 1)
        return OK;

    // if (k > 0)
    //     for (size_t i = 0; i < k; i++)
    //         left_one_shift_arr(arr, len_arr);
    // else
    //     for (size_t i = 0; i < -k; i++)
    //         right_one_shift_arr(arr, len_arr);
    for (size_t i = 0; i < abs(k); i++)
    {
        if (k > 0)
            left_one_shift_arr(arr, len_arr);
        else
            right_one_shift_arr(arr, len_arr); 
    }

    
    return OK;
}

/// @brief Определяет является ли число полным квадратом
/// @param [in] num число
/// @return да/нет
static bool if_sqrt(int num)
{
    if (num == 1)
        return true;
    for (size_t d = 2; d < num / 2 + 1; d++)
        if (num % d == 0 && d * d == num)
            return true;
    return false;
}

/// @brief Считает сколько чисел являющихся полным квадратом в массве
/// @param [in] arr массив
/// @param [in] len_arr длина массива 
/// @return сколько чисел являющихся полным квадратом в массве
static size_t count_sqrt(int arr[], size_t len_arr)
{
    size_t count = 0;
    for (size_t i = 0; i < len_arr; i++)
        if (arr[i] > 0 && if_sqrt(arr[i]))
            count++;
    return count;
}

int make_sqrt_arr(int src[], size_t len_src, int dst[], size_t *len_dst)
{
    int rc = OK;
    if (src == NULL || len_src == 0)
        return ERR_PARAM;
    
    size_t count = count_sqrt(src, len_src);
    if (count > *len_dst)
        rc = ERR_NOT_ENOUPH_MEM;
    *len_dst = count;
    if (dst == NULL)
        return ERR_NOT_ENOUPH_MEM;

    size_t j = 0;
    for (size_t i = 0; i < len_src && j < count; i++)
        if (src[i] > 0 && if_sqrt(src[i]))
        {
            dst[j] = src[i];
            j++;
        }

    return rc;
}





































