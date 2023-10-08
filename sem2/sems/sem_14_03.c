// Дан целочисленные массив, удалить элементы массива которые являются простыми числами

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

#define N 10

// ввод элементов массива, возвращает код ошибки, с доп переменной n
int input_n(int a[], size_t *a_size)
{
    size_t n;
    printf("Input n: ");
    if (scanf("%zu", &n) != 1)
        return ERR_IO;
    if (n <= 0 || n > N)
        return ERR_RANGE;

    for (size_t i = 0; i < n; i ++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    *a_size = (size_t)n;

    return OK;
}

// ввод элементов массива, возвращает код ошибки
int input(int a[], size_t *a_size)
{
    printf("Input n: ");
    if (scanf("%zu", a_size) != 1)
        return ERR_IO;
    if (*a_size > N || *a_size == 0)
        return ERR_RANGE;

    for (size_t i = 0; i < *a_size; i ++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;

    return OK;
}

// вывод элементов массива, КАК НАДО ВЫВОДИТЬ МАССИВ
void print(const int a[], size_t a_size)
{
    printf("Array: \n");
    for (size_t i = 0; i < a_size; i++)
        printf("%d ", a[i]);
    printf("\n");
}


// проверка на простоту
bool is_simple(int num)
{
    if (num <= 1)
        return false;

    for (int i = 2; i < num; i++)
        if (num % i == 0)
            return false;

    return true;
}

// проверка на простоту
bool is_simple_my(int num)
{
    for (int d = 2; d < (int)sqrt(num); d++)
        if (num % d == 0)
            return false;

    return true;
}

// удаление элементов по индексу, возвращает код ошибки
int delete_class(int a[], size_t *a_size, size_t index)
{
    if (index >= *a_size)
        return ERR_RANGE;

    for (size_t i = index + 1; i < *a_size; i++)
        a[i - 1] = a[i];
    (*a_size)--;

    return OK;
}

// удаление элементов по индексу, возвращает код ошибки
int delete(int a[], size_t *a_size, size_t index)
{
    size_t n = *a_size;
    if (index >= n)
        return ERR_RANGE;

    for (size_t i = index; i < n - 1; i++)
        a[i] = a[i + 1];
    n--;
    *a_size = n;

    return OK;
}

// удаление всех простых чисел, возращает код ошибки
int delete_simple_class(int a[], size_t *a_size)
{
    size_t i = 0;
    int rc = OK;
    while (rc == OK && i < *a_size)
        if (is_simple(a[i]))
            rc = delete(a, a_size, i);
        else
            i++;

    return rc;
}

// удаление всех простых чисел, возращает код ошибки
int delete_simple(int a[], size_t *a_size)
{
    size_t i = 0;
    while (i < *a_size)
    {
        if (is_simple(a[i]))
        {
            // printf("|%d|", a[i]);
            int res = delete(a, a_size, i);
            if (res != OK)
                return res;
        }
        else
            i++;
    }
    return OK;
}

// удаление всех простых чисел, возращает код ошибки
// за один цикл (индекс чтения и инлекс записи)
int delete_simple_2(int a[], size_t *a_size)
{
    size_t ind_write = 0;
    for (size_t ind_read = 0; ind_read < *a_size; ind_read++)
        if (! is_simple(a[ind_read]))
        {
            a[ind_write] = a[ind_read];
            ind_write++;
        }
    *a_size = ind_write;

    return OK;
}


int main(void)
{
    int a[N];
    size_t a_size;
    int res;
    res = input(a, &a_size);
    if (res != OK)
        return res;

    res = delete_simple_2(a, &a_size);
    if (res != OK)
        return res;

    print(a, a_size);
    return OK;
}

