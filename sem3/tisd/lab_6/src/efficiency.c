#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <assert.h>


// возвращает время в мкс
unsigned long long ms_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return -1ULL;

    // return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
    return val.tv_sec * 1000000ULL + val.tv_usec;
}

double get_tavg(unsigned long long *t, size_t len_t)
{
    assert(len_t != 0);
    unsigned long long sum = 0;
    double tavg;

    for (size_t i = 0; i < len_t; i++)
    {
        sum += t[i];
    }

    if (sum == 0)
        tavg = 0.0;
    else
        tavg = sum / len_t;

    assert( tavg >= 0);
    return tavg;
}

double get_rse(unsigned long long *t, size_t len_t)
{
    double tavg;
    double s, rse, eps = 1e-5;

    tavg = get_tavg(t, len_t);
    if (fabs(tavg) < eps)
        return 0.0;

    for (size_t i = 0; i < len_t; i++)
    {
        s = (t[i] - tavg) * (t[i] - tavg);
    }
    s = sqrt(s / (len_t - 1));
    rse = s / (sqrt(len_t) * tavg) * 100;

    return rse;
}














