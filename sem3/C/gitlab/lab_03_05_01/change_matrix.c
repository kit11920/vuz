#include <stdio.h>
#include "change_matrix.h"
#include "errors.h"


int sum_digits(int num)
{
    int sum = 0;
    if (num < 0)
        num *= -1;
    while (num / 10 != 0)
    {
        sum += num % 10;
        num /= 10;
    }
    sum += num;
    return sum;
}


void shift_elems(int a[], size_t a_n, int count_pos)
{
    int tmp;
    for (int k = 0; k < count_pos; k++)
    {
        tmp = a[0];
        for (size_t i = 0; i < a_n - 1; i++)
            a[i] = a[i + 1];
        a[a_n - 1] = tmp;
    }
}


int change_mtrx(int mtrx[][M], size_t n, size_t m)
{
    int a[N * M];
    size_t k = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (sum_digits(mtrx[i][j]) > 10)
            {
                a[k] = mtrx[i][j];
                k++;
            }
    if (k == 0)
        return ERR_NO_ELEM;

    int count_pos = 3;
    shift_elems(a, k, count_pos);
    k = 0;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (sum_digits(mtrx[i][j]) > 10)
            {
                mtrx[i][j] = a[k];
                k++;
            }
    return OK;
}








