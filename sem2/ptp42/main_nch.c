#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>

#ifndef COLUMNS
#error No COLUMNS here
#endif
#ifndef ROWS
#error No ROWS here
#endif


// вывод матрицы
void print_matrix(int mtrx[][ROWS], size_t n, size_t m)
{
    printf("Матрица: \n");
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf("%d ", mtrx[i][j]);
        printf("\n");
    }
}

// заполнение массива
void fill_matrix(int mtrx[][ROWS], size_t n, size_t m)
{
    srand(time(NULL));
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            mtrx[i][j] = rand() % 1000;
}

// Находит сумму элементов массива
int sum_of_arr_nums(const int a[], size_t a_n)
{
    int sum = 0;
    for (size_t i = 0; i < a_n; i++)
        sum += a[i];
    return sum;
}

//Меняем местами значения двух матриц
void change_place_arrs(int a[], int b[], size_t m)
{
    int tmp[ROWS];
    for (size_t i = 0; i < m; i++)
    {
        tmp[i] = a[i];
        a[i] = b[i];
        b[i] = tmp[i];
    }
}

// сортирует строки матрицы (метод пузырьком)
void sort_matrix(int mtrx[][ROWS], size_t n, size_t m)
{
    if (n == 1)
        return;

    for (size_t i = 0; i < n - 1; i++)
        for (size_t j = 0; j < n - i - 1; j++)
            if (sum_of_arr_nums(mtrx[j], m) > sum_of_arr_nums(mtrx[j + 1], m))
                change_place_arrs(mtrx[j], mtrx[j + 1], m);
}

// возвращает время в мс
unsigned long long ms_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return -1ULL;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}


int main(void)
{
    int mtrx[COLUMNS][ROWS];
    fill_matrix(mtrx, COLUMNS, ROWS);

    //print_matrix(mtrx, COLUMNS, ROWS);

    unsigned long long beg, end;

    if (ROWS > 500)
    {
        beg = ms_now();
        sort_matrix(mtrx, COLUMNS, ROWS);
        end = ms_now();

        printf("%llu\n", end - beg);
    }
    else
    {
        size_t iters = 10;
        beg = ms_now();
        for (size_t i = 0; i < iters; i++)
            sort_matrix(mtrx, COLUMNS, ROWS);
        end = ms_now();

        printf("%llu\n", (end - beg) / iters);
    }

    //print_matrix(mtrx, COLUMNS, ROWS);

    mtrx[0][0] = mtrx[0][1];
    mtrx[0][1] = mtrx[1][1];

    return 0;
}




