#include <stdio.h>
#include "input_output.h"
#include "errors.h"


int input_matrix(int mtrx[][M], size_t *n, size_t *m)
{
    printf("Введите количество строк и столбцов матрицы: ");
    if (scanf("%zu%zu", n, m) != 2)
        return ERR_INPUT;
    if (*n > N || *m > M || *n == 0 || *m == 0)
        return ERR_RANGE;

    printf("Введите матрицу: \n");
    for (size_t i = 0; i < *n; i++)
        for (size_t j = 0; j < *m; j++)
            if (scanf("%d", &mtrx[i][j]) != 1)
                return ERR_INPUT;
    return OK;
}


void print_matrix(int mtrx[][M], size_t n, size_t m)
{
    printf("Матрица: ");
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", mtrx[i][j]);
        printf("\n");
    }
}
