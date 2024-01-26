#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort_bubble(int *a, size_t n)
{
    for (size_t i = 1; i < n; i++)
        for (size_t j = 0; j < n - i; j++)
            if (a[j] > a[j + 1])
            {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
}

void print(const int *a, size_t n)
{
    printf("Array:\n");
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

#define N    (5 * 1024)

int main(void)
{
    int a[N];
    size_t n = sizeof(a) / sizeof(a[0]);
    
    srand(time(NULL));
    
    for (size_t i = 0; i < n; i++)
        a[i] = rand();
    
    sort_bubble(a, n);
    
    //print(a, n);
    
    return 0;
}

