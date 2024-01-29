#include <stdio.h>
#include "input_output.h"

/*
void change_arrs_st_end(int a[], int b[], size_t st, size_t end)
{
    int tmp;
    for (size_t i = st; i <= end; i++)
    {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

void change_matrix(int mtrx[][M], size_t n)
{
    for (size_t i = 0; i < n / 2; i++)
        change_arrs_st_end(mtrx[i], mtrx[n - i - 1], i, n - i - 1);
}
*/

void change_arrs_st_end(int a[], int b[], size_t n)
{
    int tmp;
    for (size_t i = 0; i < n; i++)
    {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

void change_matrix(int mtrx[][M], size_t n)
{
    for (size_t i = 0; i < n / 2; i++)
        change_arrs_st_end(&mtrx[i][i], &mtrx[n - i - 1][i], n - 2 * i);
}
\


























