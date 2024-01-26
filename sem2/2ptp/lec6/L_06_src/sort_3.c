#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

// Получение времени в миллисекундах
unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

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

#define N         (5 * 1024)
#define N_REPS    15

int main(void)
{
    unsigned long long datas[N_REPS];
    int a[N], src[N];
    size_t n = sizeof(a) / sizeof(a[0]);
    long long unsigned beg, end;
    
    srand(time(NULL));
    
    for (size_t i = 0; i < n; i++)
        src[i] = rand();
    
    for (int i = 0; i < N_REPS; i++)
    {
        memcpy(a, src, sizeof(src));

        beg = milliseconds_now();

        sort_bubble(a, n);
    
        end = milliseconds_now();
        
        datas[i] = end - beg;
    }
    
    double avg = 0.0;
    
    for (size_t i = 0; i < N_REPS; i++)
        avg += datas[i];
        
    avg /= N_REPS;

    double s_sq = 0.0;
    
    for (size_t i = 0; i < N_REPS; i++)
        s_sq += (datas[i] - avg) * (datas[i] - avg);
        
    s_sq /= (N_REPS - 1);
 
    double s = sqrt(s_sq);
 
    double std_err = s / sqrt(N_REPS);

    double rse = std_err / avg * 100;
    
    printf("Time %f ms (%.2f%%)\n", avg, rse);
    
    return 0;
}

