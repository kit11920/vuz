// gnu99
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <x86gprintrin.h>
#include <math.h>

#define N_REPS 500
#define N_ITER 10

// tms - время в милисекундах
int delay(uint32_t tms)
{
    time_t tv_sec = tms / 1000;
    long tv_nsec = (tms % 1000) * 1000000L;
    const struct timespec req = {.tv_sec = tv_sec, .tv_nsec = tv_nsec};

    return nanosleep(&req, NULL);
}

// вычисляет разность времени в микросекундах
unsigned long long calc_elapsed_time(const struct timespec *beg, const struct timespec *end)
{
    return ((unsigned long long)
        (end->tv_sec - beg->tv_sec) * 1000 * 1000 * 1000 +
                        (end->tv_nsec - beg->tv_nsec)) / 1000;
}


void mid_time_clock_gettime(int delay_now)
{
    //printf("%d\n", delay_now);
    if (delay_now >= 500)
    {

        struct timespec t_beg, t_end;
        unsigned long long data[N_REPS], sum = 0;
        double rse = 100, mid, s2;
        int count_rep = 0;

        for (size_t i = 0; rse > 5.0 || i < 2; i++)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
            delay(delay_now);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

            data[i] = calc_elapsed_time(&t_beg, &t_end);

            // rse
            s2 = 0.0;
            sum += data[i];
            mid = (double) sum / (i + 1);
            for (size_t j = 0; j <= i; j++)
                s2 += (data[i] - mid) * (data[i] - mid);
            s2 /= (double) i;
//            printf("%f\n", s2);
//            printf("%f %f\n", sqrt(s2), sqrt(i + 1));
            rse = ((sqrt(s2) / sqrt(i + 1)) / mid) * 100;

            count_rep = i + 1;

//            printf("%d\t%d\t%d\t%d\t\n", delay_now, (int)mid, count_rep, (int)rse);
        }

        int abs_err;
        double otn_err;

        abs_err = (int)mid - delay_now * 1000;
        otn_err = (double) abs_err / (delay_now * 1000);
        printf("%d\t%d\t%d\t%.2f\t%d\t%.2f\n", delay_now, (int)mid, count_rep, rse, abs_err, otn_err);
    }
    else
    {

        struct timespec t_beg, t_end;
        unsigned long long data[N_REPS], sum = 0;
        double rse = 100, mid, s2;
        int count_rep = 0;

        for (size_t i = 0; rse > 5.0 || i < 2; i++)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &t_beg);
            for (size_t i = 0; i < N_ITER; i++)
                delay(delay_now);
            clock_gettime(CLOCK_MONOTONIC_RAW, &t_end);

            data[i] = calc_elapsed_time(&t_beg, &t_end) / N_ITER;

            // rse
            s2 = 0.0;
            sum += data[i];
            mid = (double) sum / (i + 1);
            for (size_t j = 0; j <= i; j++)
                s2 += (data[i] - mid) * (data[i] - mid);
            s2 /= (double) i;
//            printf("%f\n", s2);
//            printf("%f %f\n", sqrt(s2), sqrt(i + 1));
            rse = ((sqrt(s2) / sqrt(i + 1)) / mid) * 100;

            count_rep = i + 1;

//            printf("%d\t%d\t%d\t%d\t\n", delay_now, (int)mid, count_rep, (int)rse);
        }

        int abs_err;
        double otn_err;

        abs_err = (int)mid - delay_now * 1000;
        otn_err = (double) abs_err / (delay_now * 1000);
        printf("%d\t%d\t%d\t%.2f\t%d\t%.2f\n", delay_now, (int)mid, count_rep, rse, abs_err, otn_err);
    }
}

// вычисляет разность времени в микросекундах
unsigned long long calc_elapsed_time2(const struct timeval *beg, const struct timeval *end)
{
    return ((unsigned long long)
        (end->tv_sec - beg->tv_sec) * 1000 * 1000 +
                        (end->tv_usec - beg->tv_usec));
}

void mid_time_clock_gettimeofday(int delay_now)
{
    //printf("%d\n", delay_now);
    if (delay_now >= 500)
    {
        struct timeval t_beg, t_end;
        unsigned long long data[N_REPS], sum = 0;
        double rse = 100, mid, s2;
        int count_rep = 0;

        for (size_t i = 0; rse > 5.0 || i < 2; i++)
        {
            gettimeofday(&t_beg, NULL);
            delay(delay_now);
            gettimeofday(&t_end, NULL);

            data[i] = calc_elapsed_time2(&t_beg, &t_end);

            // rse
            s2 = 0.0;
            sum += data[i];
            mid = (double) sum / (i + 1);
            for (size_t j = 0; j <= i; j++)
                s2 += (data[i] - mid) * (data[i] - mid);
            s2 /= (double) i;
//            printf("%f\n", s2);
//            printf("%f %f\n", sqrt(s2), sqrt(i + 1));
            rse = ((sqrt(s2) / sqrt(i + 1)) / mid) * 100;

            count_rep = i + 1;

//            printf("%d\t%d\t%d\t%d\t\n", delay_now, (int)mid, count_rep, (int)rse);

        }
        int abs_err;
        double otn_err;

        abs_err = (int)mid - delay_now * 1000;
        otn_err = (double) abs_err / (delay_now * 1000);
        printf("%d\t%d\t%d\t%.2f\t%d\t%.2f\n", delay_now, (int)mid, count_rep, rse, abs_err, otn_err);

    }
    else
    {
        struct timeval t_beg, t_end;
        unsigned long long data[N_REPS], sum = 0;
        double rse = 100, mid, s2;
        int count_rep = 0;

        for (size_t i = 0; rse > 5.0 || i < 2; i++)
        {
            gettimeofday(&t_beg, NULL);
            for (size_t i = 0; i < N_ITER; i++)
                delay(delay_now);
            gettimeofday(&t_end, NULL);

            data[i] = calc_elapsed_time2(&t_beg, &t_end) / N_ITER;

            // rse
            s2 = 0.0;
            sum += data[i];
            mid = (double) sum / (i + 1);
            for (size_t j = 0; j <= i; j++)
                s2 += (data[i] - mid) * (data[i] - mid);
            s2 /= (double) i;
//            printf("%f\n", s2);
//            printf("%f %f\n", sqrt(s2), sqrt(i + 1));
            rse = ((sqrt(s2) / sqrt(i + 1)) / mid) * 100;

            count_rep = i + 1;
        }
        int abs_err;
        double otn_err;

        abs_err = (int)mid - delay_now * 1000;
        otn_err = (double) abs_err / (delay_now * 1000);
        printf("%d\t%d\t%d\t%.2f\t%d\t%.2f\n", delay_now, (int)mid, count_rep, rse, abs_err, otn_err);
    }
}


void mid_time_clock(int delay_now)
{
    //printf("%d\n", delay_now);
    if (delay_now >= 500)
    {
        clock_t t_beg, t_end;
        unsigned long long data[N_REPS], sum = 0;
        double rse = 100, mid, s2;
        int count_rep = 0;

        for (size_t i = 0; rse > 5.0 || i < 2; i++)
        {
            t_beg = clock();
            delay(delay_now);
            t_end = clock();
//            printf("%f %f\n", (double) t_beg / (double) CLOCKS_PER_SEC, (double) t_end / CLOCKS_PER_SEC);

            data[i] = (unsigned long long) (((double) (t_end - t_beg) / (double)CLOCKS_PER_SEC) * 1000 * 1000);

            // rse
            s2 = 0.0;
            sum += data[i];
            mid = (double) sum / (i + 1);
            for (size_t j = 0; j <= i; j++)
                s2 += (data[i] - mid) * (data[i] - mid);
            s2 /= (double) i;
//            printf("%f\n", s2);
//            printf("%f %f\n", sqrt(s2), sqrt(i + 1));
            rse = ((sqrt(s2) / sqrt(i + 1)) / mid) * 100;

            count_rep = i + 1;

        }

        long long abs_err;
        double otn_err;
        abs_err = (long long) mid - delay_now * 1000;
        otn_err = (- abs_err) / (double) (delay_now * 1000);
        printf("%d\t%llu\t%d\t%.2f\t%lld\t%.2f\n", delay_now, (long long unsigned)mid, count_rep, rse, abs_err, otn_err);
    }
    else
    {
        clock_t t_beg, t_end;
        unsigned long long data[N_REPS], sum = 0;
        double rse = 100, mid, s2;
        int count_rep = 0;

        for (size_t i = 0; rse > 5.0 || i < 2; i++)
        {
            t_beg = clock();
            for (size_t i = 0; i < N_ITER; i++)
                delay(delay_now);
            t_end = clock();

            data[i] = (unsigned long long) (((double) (t_end - t_beg) / CLOCKS_PER_SEC / N_ITER) * 1000 * 1000);

            // rse
            s2 = 0.0;
            sum += data[i];
            mid = (double) sum / (i + 1);
            for (size_t j = 0; j <= i; j++)
                s2 += (data[i] - mid) * (data[i] - mid);
            s2 /= (double) i;
//            printf("%f\n", s2);
//            printf("%f %f\n", sqrt(s2), sqrt(i + 1));
            rse = ((sqrt(s2) / sqrt(i + 1)) / mid) * 100;

            count_rep = i + 1;

        }

        long long abs_err;
        double otn_err;
        abs_err = (long long) mid - delay_now * 1000;
        otn_err = (- abs_err) / (double) (delay_now * 1000);
        printf("%d\t%llu\t%d\t%.2f\t%lld\t%.2f\n", delay_now, (long long unsigned)mid, count_rep, rse, abs_err, otn_err);
    }
}

void mid_time_rdtsc(int delay_now)
{
    //printf("%d\n", delay_now);
    if (delay_now >= 500)
    {
        long long unsigned t_beg, t_end;
        long long unsigned data[N_REPS], sum = 0;
        double rse = 100, mid, s2;
        int count_rep = 0;


        for (size_t i = 0; rse > 5.0 || i < 2; i++)
        {
            t_beg = __rdtsc();
            delay(delay_now);
            t_end = __rdtsc();

            data[i] = t_end - t_beg;

            // rse
            s2 = 0.0;
            sum += data[i];
            mid = (double) sum / (i + 1);
            for (size_t j = 0; j <= i; j++)
                s2 += (data[i] - mid) * (data[i] - mid);
            s2 /= (double) i;
//            printf("%f\n", s2);
//            printf("%f %f\n", sqrt(s2), sqrt(i + 1));
            rse = ((sqrt(s2) / sqrt(i + 1)) / mid) * 100;
            count_rep = i + 1;
        }

        printf("%d\t%llu\t%d\t%.2f\t-\t-\n", delay_now, (long long unsigned)mid, count_rep, rse);
    }
    else
    {
        long long unsigned t_beg, t_end;
        long long unsigned data[N_REPS], sum = 0;
        double rse = 100, mid, s2;
        int count_rep = 0;


        for (size_t i = 0; rse > 5.0 || i < 2; i++)
        {
            t_beg = __rdtsc();
            for (size_t i = 0; i < N_ITER; i++)
                delay(delay_now);
            t_end = __rdtsc();

            data[i] = (t_end - t_beg) / N_ITER;

            // rse
            s2 = 0.0;
            sum += data[i];
            mid = sum / (i + 1);
            for (size_t j = 0; j <= i; j++)
                s2 += (data[i] - mid) * (data[i] - mid);
            s2 /= i;
//            printf("%f\n", s2);
//            printf("%f %f\n", sqrt(s2), sqrt(i + 1));
            rse = ((sqrt(s2) / sqrt(i + 1)) / mid) * 100;

            count_rep = i + 1;
        }

        printf("%d\t%d\t%d\t%.2f\t-\t-\n", delay_now, (int)mid, count_rep, rse);
    }
}






int main(void)
{
    printf("clock_gettime\n");
    printf("Задержка\tРезультат_задержки\tКол-во_повторов\tRSE\tАюсолютная_ошибка\tОтносительная_ошибка\n");
    mid_time_clock_gettime(1000);
    mid_time_clock_gettime(100);
    mid_time_clock_gettime(50);
    mid_time_clock_gettime(10);

    printf("gettimeofday\n");
    printf("Задержка\tРезультат_задержки\tКол-во_повторов\tRSE\tАюсолютная_ошибка\tОтносительная_ошибка\n");
    mid_time_clock_gettimeofday(1000);
    mid_time_clock_gettimeofday(100);
    mid_time_clock_gettimeofday(50);
    mid_time_clock_gettimeofday(10);

    printf("clock\n");
    printf("Задержка\tРезультат_задержки\tКол-во_повторов\tRSE\tАюсолютная_ошибка\tОтносительная_ошибка\n");
    mid_time_clock(1000);
    mid_time_clock(100);
    mid_time_clock(50);
    mid_time_clock(10);

    printf("rdtsc\n");
    printf("Задержка\tРезультат_задержки\tКол-во_повторов\tRSE\tАюсолютная_ошибка\tОтносительная_ошибка\n");
    mid_time_rdtsc(1000);
    mid_time_rdtsc(100);
    mid_time_rdtsc(50);
    mid_time_rdtsc(10);

    return 0;
}











