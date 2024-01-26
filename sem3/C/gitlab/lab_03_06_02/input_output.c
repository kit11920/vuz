#include <stdio.h>
#include "input_output.h"
#include "errors.h"


void print_matrix(int a[][M], size_t a_n, size_t a_m)
{
    printf("Матрица: \n");
    for (size_t i = 0; i < a_n; i++)
    {
        for (size_t j = 0; j < a_m; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}


int input_mtrx_nm(size_t *a_n, size_t *a_m)
{
    printf("Введите количество строк и столбцов матрицы: ");
    if (scanf("%zu%zu", a_n, a_m) != 2)
        return ERR_INPUT;
    if (*a_n > N || *a_m > M || *a_n == 0 || *a_m == 0)
        return ERR_RANGE;
    return OK;
}
