#include <stdio.h>
#include "sort_matrix.h"
#include "errors.h"

/*
void assigning_arr_to_arr(int a[], const int b[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        a[i] = b[i];
}
*/

int product_of_arr_nums(const int a[], size_t a_n)
{
    int prdct = 1;
    for (size_t i = 0; i < a_n; i++)
        prdct *= a[i];
    return prdct;
}

void change_place_arrs(int a[], int b[], size_t m)
{
    int tmp[M];
    for (size_t i = 0; i < m; i++)
    {
        tmp[i] = a[i];
        a[i] = b[i];
        b[i] = tmp[i];
    }
}

void sort_matrix(int mtrx[][M], size_t n, size_t m)
{
    if (n == 1)
        return;

    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (product_of_arr_nums(mtrx[j], m) > product_of_arr_nums(mtrx[j + 1], m))
            {
                change_place_arrs(mtrx[j], mtrx[j + 1], m);
                /*
                assigning_arr_to_arr(tmp, mtrx[j], m);
                assigning_arr_to_arr(mtrx[j], mtrx[j + 1], m);
                assigning_arr_to_arr(mtrx[j + 1], tmp, m);
                */
            }
}














