#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO_MINUS_EL 3

#define N 10

// ввод элементов массива, возвращает код ошибки
int input(int a[], size_t *a_size)
{
    printf("Введите размер массива: ");
    if (scanf("%zu", a_size) != 1)
        return ERR_IO;
    if (*a_size > N || *a_size == 0)
        return ERR_RANGE;

    printf("Введите массив: ");
    for (size_t i = 0; i < *a_size; i ++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;

    return OK;
}


/*
Находит среднее арифметическое  отрицательных элементов массива

Возвращает код ошибки
*/
int find_mid(const int a[], size_t a_size, float *mid)
{
    int summ = 0, countt = 0;
    for (size_t i = 0; i < a_size; i++)
        if (a[i] < 0)
        {
            summ += a[i];
            countt++;
        }
    if (countt == 0)
        return ERR_NO_MINUS_EL;

    *mid = ((float)summ / countt);
    return OK;
}

/*
// Проверяет есть ли в массиве отрицательные элементы
int if_minus_el(const int a[], const size_t a_size)
{
    int count_minus = 0;
    for (size_t i = 0; i < a_size; i ++)
        if (a[i] < 0)
            count_minus++;

    if (count_minus == 0)
        return ERR_NO_MINUS_EL;
    return OK;
}


// Находит среднее арифметическое  отрицательных элементов массива
float find_mid(const int a[], size_t a_size)
{
    int summ = 0, countt = 0;
    float mid;
    for (size_t i = 0; i < a_size; i++)
    {
        if (a[i] < 0)
        {
            summ += a[i];
            countt++;
        }
    }
//    printf("%d %d\n", summ, countt);
    mid = ((float)summ / countt);

    return mid;
}
*/

int main(void)
{
    int a[N];
    size_t a_size = 0;
    int res;
    res = input(a, &a_size);
    if (res != OK)
        return res;

    float mid;
    res = find_mid(a, a_size, &mid);
    if (res != OK)
        return res;
    printf("Среднее арифметическое отрицательных элементов массива %f\n", mid);

    return OK;
}
