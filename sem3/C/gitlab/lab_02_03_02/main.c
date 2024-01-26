#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO_ELEM 3

#define N 10
#define EPS 0.0000001

// ввод элементов массива, возвращает код ошибки
int input(int a[], size_t *a_size)
{
    printf("Введите размер массива: ");
    if (scanf("%zu", a_size) != 1)
        return ERR_IO;

    if (*a_size > N || *a_size == 0)
        return ERR_RANGE;

    printf("Введите массив: ");
    for (size_t i = 0; i < *a_size; i++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;

    return OK;
}

// вывод элементов массива
void print(const int a[], size_t a_size)
{
    printf("Массив: \n");
    for (size_t i = 0; i < a_size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// Проверяет если число является полным квадратом
bool if_full_sqrt(int num)
{
    if (num == 1)
        return true;
    int i = 2;
    while (i * i < num)
        i++;
    if (i * i == num)
        return true;
    return false;
}


// Удяляет из массива элементы которые являются полным квадратом
void delete_sqrt(int a[], size_t *a_size)
{
    size_t j = 0;
    for (size_t i = 0; i < *a_size; i++)
    {
        // printf("%lf %d \n", sqrt(a[i]), (int)sqrt(a[i]));
        if (a[i] <= 0 || ! if_full_sqrt(a[i]))
        {
            a[j] = a[i];
            j++;
            //printf("%d\n", a[i]);
        }
    }
    *a_size = j;
}


int main(void)
{
    int a[N];
    size_t a_size;
    int res = input(a, &a_size);
    if (res != OK)
        return res;
    delete_sqrt(a, &a_size);
    if (a_size == 0)
        return ERR_NO_ELEM;

    print(a, a_size);
    return OK;
}
