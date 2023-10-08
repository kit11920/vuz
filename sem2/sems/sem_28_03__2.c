// сумма элементов над главной диагональю включая саму гл диагональ

#include <stdio.h>

#define N 10
#define M 10

#define OK 0
#define ERR_NON_SQRT_MATRIX 1
#define ERR_EMPTY_MATRIX 2

// Считает сумму лементов над главной диагональю включая саму гл диагональ
// \return код ошибки
int calc_sum(int a[][M], size_t a_n, size_t a_m, int *sum)
{
    if (a_n != a_m)
        return ERR_NON_SQRT_MATRIX;
    if (a_n == 0)
        return ERR_EMPTY_MATRIX;

    *sum = 0;
    for (size_t i = 0; i < a_n; i++)
        for (size_t j = i; j < a_m; j++)
            (*sum) += a[i][j];
    return OK;
}

// записать в одномерный массив сначала главную диагональ потом побочную
// возвращает код ошибки
int form_array(int a[][M], size_t a_n, size_t a_m, int arr[], size_t *arr_n)
{
    if (a_n != a_m)
        return ERR_NON_SQRT_MATRIX;
    if (a_n == 0)
        return ERR_EMPTY_MATRIX;

    for (size_t i = 0; i < a_n; i++)
    {
        arr[i] = a[i][i];
        arr[a_n + i] = a[i][a_n - i - 1];
    }
    *arr_n = 2 * a_n;
    return OK;
}







