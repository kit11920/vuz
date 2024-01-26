#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_NO_ELEM 3

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

// Проверка если первая и последняя цифра числа одинаковые
bool if_equal_start_end(int num)
{
    int st, end;
    num = abs(num);
    st = num % 10;
    //printf("%d \n", st);
    end = num;

    while (end >= 10)
    {
        end /= 10;
        //printf("%d ", end);
    }
    //printf("\n");
    return (st == end);
}

/* Формирует массив,
в котором скопированны элементы исходного массива,
которые начинаются и заканчиваются на одну и ту же цифру */
void form_array(const int a[], size_t a_size, int b[], size_t *b_size)
{
    *b_size = 0;
    for (size_t i = 0; i < a_size; i++)
        if (if_equal_start_end(a[i]))
        {
            b[*b_size] = a[i];
            (*b_size)++;
        }
}

int main(void)
{
    int a[N], b[N];
    size_t a_size, b_size;
    int res = input(a, &a_size);
    if (res != OK)
        return res;

    form_array(a, a_size, b, &b_size);
    if (b_size == 0)
        return ERR_NO_ELEM;
    print(b, b_size);

    return OK;
}
