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

// Возвращает индекс максимального элементы
size_t max_elem_ind(const int a[], size_t a_size)
{
    size_t max_el_ind = 0;
    for (int i = a_size - 1; i >= 0; i--)
        if (*(a + i) > *(a + max_el_ind))
            max_el_ind = i;
    return max_el_ind;
}

// Сортировка выбором
void selection_sort(int a[], size_t a_size)
{
    int tmp;
    size_t mn;
    for (size_t i = a_size - 1; i > 0; i--)
    {
        mn = max_elem_ind(a, i + 1);
        tmp = *(a + i);
        *(a + i) = *(a + mn);
        *(a + mn) = tmp;
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
    selection_sort(a, LEN_ARR);
    end = ms_now();

    //print(a, LEN_ARR);

    a[0] = a[1];
    a[1] = 1234;

    printf("%llu\n", end - beg);

    return 0;
}




