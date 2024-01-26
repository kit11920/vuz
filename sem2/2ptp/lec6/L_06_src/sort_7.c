// gnu99
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
// !!!
#include <x86gprintrin.h>

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

#define DELAY 100

int main(void)
{
   {
        struct timespec t_beg, t_end;
    
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);

        delay(DELAY);
    
        clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

        printf("Delay %d ms %llu us\n", DELAY, calc_elapsed_time(&t_beg, &t_end));
    }
     
    {
        clock_t t_beg, t_end;

        t_beg = clock();

        delay(DELAY);
 
        t_end = clock();
   
        printf("Delay %d ms %f s\n", DELAY, (double) (t_end - t_beg) / CLOCKS_PER_SEC);
    }
     
    {
        long long unsigned t_beg, t_end;

        t_beg = __rdtsc(); 

        delay(DELAY);
 
        t_end = __rdtsc();    

        printf("Delay %d ms %llu TSC\n", DELAY, t_end - t_beg);
    }
   
    return 0;
}

