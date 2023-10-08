// в каждой строке матрица посчитать колво минимальных элементов

#include <stdio.h>

#define N 10
#define M 10

#define OK 0
#define ERR_EMPTY_ARRAY 1


// колво минимальных элементов в массиве
// return код ошибки
int get_min_count(const int a[], size_t a_n, size_t *n)
{
    if (a_n == 0)
        return ERR_EMPTY_ARRAY;

    int min_el = a[0];
    *n = 1;
    for (int i = 1; i < a_n; i++)
    {
        if (a[i] == min_el)
        {
            (*n)++;
        }
        else if (a[i] < min_el)
        {
            min_el = a[i];
            *n = 1;
        }
    }

    return OK;
}


int main(void)
{
    int a[N][M];
    size_t a_n, a_m;
    size_t count;
    int res;

    for (size_t i = 0; i < a_n; i++)
    {
        res = get_min_count(a[i], a_m, &count);
        if (res != OK)
        {
            printf("ERROR");
            continue;
        }
        printf("Count %zu", count);
    }
}
