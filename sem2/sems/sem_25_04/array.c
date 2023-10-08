
#include "array.h"


int arr_read(int a[], size_t a_n)
{
    for (size_t i = 0; i < a_n; i++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    return OK;
}

void arr_print(const int a[], size_t a_n)
{
    for (size_t i = 0; i < a_n; i++)
        printf("%d ", a[i]);
    printf("\n");
}


double arr_calc_avg(const int a[], size_t a_n)
{
    double avg;
    int sum = 0;

    for (size_t i = 0; i < a_n; i++)
        sum += a[i];

    avg = (double)sum / a_n;

    return avg;
}




















