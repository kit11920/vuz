#include <stdio.h>
//0 0 -1 -2 45 45 -5 -7 -5 45 56 0

#define OK 0
#define ERR_IO 1
#define OVERFLOW 100

#define N 10

// ввод элементов массива, возвращает код ошибки
int input(int a[], size_t *a_size)
{
    printf("Введите массив: ");
    size_t i = 0;
    while (i < N && scanf("%d", &a[i]) == 1)
        i++;

    int el;
    if (i == 0)
        return ERR_IO;
    else if (scanf("%d", &el) == 1)
    {
        *a_size = N;
        return OVERFLOW;
    }

    *a_size = i;
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

// Возвращает индекс максимального элементы
size_t max_elem_ind(const int a[], size_t a_size)
{
    size_t max_el_ind = 0;
    for (size_t i = 1; i < a_size; i++)
        if (a[i] > a[max_el_ind])
            max_el_ind = i;
    return max_el_ind;
}

// Сортировка выбором
void selection_sort(int a[], size_t a_size)
{
    int tmp;
    size_t mn;
    for (size_t end = a_size - 1; end > 0; end--)
    {
        mn = max_elem_ind(a, end + 1);
        tmp = a[end];
        a[end] = a[mn];
        a[mn] = tmp;
    }
}

int main(void)
{
    int a[N];
    size_t a_size;
    int res = input(a, &a_size);
    if (res != OK && res != OVERFLOW)
        return res;
    selection_sort(a, a_size);
    print(a, a_size);

    return res;
}

