#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>

#ifndef LEN_ARR
#error No LEN_ARR here
#endif


// вывод элементов массива
void print(const int a[], size_t a_size)
{
    printf("Массив: \n");
    for (size_t i = 0; i < a_size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// заполнение массива
void fill_arr(int *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        a[i] = i;
}

// Возвращает указатель на максимальный элемент
int *max_elem_p(int *pbeg, int *pend)
{
    int *pmax = pbeg;
    for (int *pcur = pend - 1; pcur >= pbeg; pcur--)
        if (*pcur > *pmax)
            pmax = pcur;

    return pmax;
}

// Сортировка выбором
void selection_sort(int *pbeg, int *pend)
{
    int tmp;
    int *pmax;
    for (int *pcur = pend - 1; pcur > pbeg; pcur--)
    {
        pmax = max_elem_p(pbeg, pcur + 1);
        tmp = *pcur;
        *pcur = *pmax;
        *pmax = tmp;
    }
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
    int a[LEN_ARR];
    fill_arr(a, LEN_ARR);

    unsigned long long beg, end;
    //print(a, LEN_ARR);
    beg = ms_now();
    selection_sort(a, a + LEN_ARR);
    end = ms_now();

    //print(a, LEN_ARR);

    a[0] = a[1];
    a[1] = 1234;

    printf("%llu\n", end - beg);

    return 0;
}




