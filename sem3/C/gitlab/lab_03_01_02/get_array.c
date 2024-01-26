#include <stdio.h>
#include <stdbool.h>
#include "get_array.h"

#include "errors.h"


bool if_plus_minus_col(int a[][M], size_t a_n, size_t k)
{
    if (a_n == 1)
        return false;
    for (size_t i = 1; i < a_n; i++)
        if (a[i - 1][k] * a[i][k] >= 0)
            return false;
    return true;
}


void get_array(int matrix[][M], size_t matrix_n, size_t matrix_m, int arr[])
{
    for (size_t k = 0; k < matrix_m; k++)
    {
        if (if_plus_minus_col(matrix, matrix_n, k))
            arr[k] = 1;
        else
            arr[k] = 0;
    }
}
