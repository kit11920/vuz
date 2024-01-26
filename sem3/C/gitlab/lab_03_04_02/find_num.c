#include <stdio.h>
#include <stdbool.h>
#include "find_num.h"
#include "errors.h"

bool if_num_end_5(int num)
{
    if (num < 0)
        num *= -1;
    return num % 10 == 5;
}


int find_max_num_end_5(int mtrx[][M], size_t n, size_t m, int *max_num)
{
    *max_num = -1;
    for (size_t i = 1; i < n; i++)
        for (size_t j = m - 1; j > n - 1 - i; j--)
            if (if_num_end_5(mtrx[i][j]) && (*max_num == -1 || mtrx[i][j] > *max_num))
                *max_num = mtrx[i][j];

    if (*max_num == -1)
        return ERR_NO_NUM_END_5;

    return OK;
}
















