// gnu99
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

// вычисляет разность времени в микросекундах
unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long)
        (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 +
                        (end->tv_nsec - beg->tv_nsec)) / 1000; 
}

// tms - время в милисекундах
int delay(uint32_t tms)
{
    time_t tv_sec = tms / 1000;
    long tv_nsec = (tms % 1000) * 1000000L;
    const struct timespec req = {.tv_sec = tv_sec, .tv_nsec = tv_nsec};
    
    return nanosleep(&req, NULL);
}

#define N_REPS 15
#define N_ITER 10
#define DELAY  500

int main(void)
{
    {
        struct timespec t_beg, t_end;
        unsigned long long datas[N_REPS];
    
        for (size_t i = 0; i < N_REPS; i++)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

            delay(DELAY);
    
            clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

            datas[i] = calc_elapsed_time(&t_beg, &t_end);
        }

        (void) datas;
    }

    {
        struct timespec t_beg, t_end;
        unsigned long long datas[N_REPS];

        for (size_t i = 0; i < N_REPS; i++)
        {
             clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

             for (size_t i = 0; i < N_ITER; i++)
                 delay(DELAY);
    
             clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

             datas[i] = calc_elapsed_time(&t_beg, &t_end);
        }
 
        (void) datas;   
    }

    return 0;
}

