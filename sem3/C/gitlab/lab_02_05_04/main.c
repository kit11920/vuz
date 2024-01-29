#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

#define N 10

// ввод элементов массива, возвращает код ошибки
int input(int *const pba, int *const pea)
{
    int elem;
    printf("Введите массив: ");
    for (int *pcur = pba; pcur < pea; pcur++)
    {
        if (scanf("%d", &elem) != 1)
            return ERR_IO;
        *pcur = elem;
    }
    return OK;
}

// проверяет есть ли элемент в массиве, который передан в виде указателей на начало и конец
bool if_elem_in_arr(const int *pba, const int *pea, int elem)
{
    for (const int *pi = pba; pi < pea; pi++)
        if (*pi == elem)
            return true;
    return false;
}

// Возвращает количество уникальных элементов в массиве
int find_count_unic_elem(const int *const pba, const int *const pea)
{
    bool elem_in;
    int count_unic_elem = 1;
    for (const int *pi = pba + 1; pi < pea; pi++)
    {
        elem_in = if_elem_in_arr(pba, pi, *pi);

        if (! elem_in)
            count_unic_elem++;
    }
    return count_unic_elem;
}


/*
// Возвращает количество уникальных элементов в массиве
int find_count_unic_elem(const int *const pba, const int *const pea)
{
    bool elem_in;
    int count_unic_elem = 1;
    for (const int *pi = pba + 1; pi < pea; pi++)
    {
        elem_in = false;
        for (const int *pj = pi - 1; pj >= pba; pj--)
            if (*pi == *pj)
            {
                elem_in = true;
                break;
            }
        if (! elem_in)
            count_unic_elem++;
    }
    return count_unic_elem;
}

*/

int main(void)
{
    int a[N];
    size_t a_size;
    printf("Введите размер массива: ");
    if (scanf("%zu", &a_size) != 1)
        return ERR_IO;
    if (a_size > N || a_size == 0)
        return ERR_RANGE;

    int res = input(a, a + a_size);
    if (res != OK)
        return res;

    int count_unic_elem = find_count_unic_elem(a, a + a_size);
    printf("Количество уникальных элементов - %d \n", count_unic_elem);

    return OK;
}
