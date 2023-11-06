#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#include "time_system.h"
#include "errs.h"

#define PRINT 0

double sum_time = 0;
int count_time = 0;

void init_time_params(time_params_t *tp)
{
    tp->t1_min = 1; //1
    tp->t1_max = 5; //5

    tp->t2_min = 0; // 0
    tp->t2_max = 3; // 3

    tp->t3_min = 0; // 0
    tp->t3_max = 4; // 4

    tp->t4_min = 0; // 0
    tp->t4_max = 1; // 1
}

void print_time_params(time_params_t *tp)
{
    printf("Параметры системы:\n");
    printf("%d: интервал поступления заявок в очередь 1 (min) - %lf\n", CHANGE_T1_MIN, tp->t1_min);
    printf("%d: интервал поступления заявок в очередь 1 (max) - %lf\n", CHANGE_T1_MAX, tp->t1_max);
    printf("%d: интервал поступления заявок в очередь 2 (min) -    %lf\n", CHANGE_T2_MIN, tp->t2_min);
    printf("%d: интервал поступления заявок в очередь 2 (max) -    %lf\n", CHANGE_T2_MAX, tp->t2_max);
    printf("%d: время обслуживания заявок из очереди 1 (min)  - %lf\n", CHANGE_T3_MIN, tp->t3_min);
    printf("%d: время обслуживания заявок из очереди 1 (max)  - %lf\n", CHANGE_T3_MAX, tp->t3_max);
    printf("%d: время обслуживания заявок из очереди 2 (min)  -    %lf\n", CHANGE_T4_MIN, tp->t4_min);
    printf("%d: время обслуживания заявок из очереди 2 (max)  -    %lf\n", CHANGE_T4_MAX, tp->t4_max);
    printf("\n");
}

int change_time_params(time_params_t *tp)
{
    int act;
    char c;
    double time;

    print_time_params(tp);
    printf("Введите номер числа, которого хотите изменить: ");
    while (scanf("%d", &act) != 1 || 
    !(act >= CHANGE_T1_MIN && act <= CHANGE_T4_MAX) || (c = getchar()) != '\n')
    {
        printf("\n");
        print_err(ERR_NUM_ACT_INPUT);
        print_time_params(tp);
        printf("Введите номер числа, которого хотите изменить: ");

        c = getchar();
        while (c != '\n')
            c = getchar();
    }

    printf("Введите время: ");
    int rc = OK;
    if (scanf("%lf", &time) != 1)
        rc = ERR_IO;
    if (time < 0)
        rc = ERR_IO;

    c = getchar();
    while (c != '\n')
        c = getchar();
    if (rc != OK)
        return rc;

    
    if (act == CHANGE_T1_MIN && time <= tp->t1_max && !(time < EPS && tp->t1_max < EPS))
        tp->t1_min = time;
    else if (act == CHANGE_T1_MAX && time >= tp->t1_min && !(time < EPS && tp->t1_min < EPS))
        tp->t1_max = time;
    else if (act == CHANGE_T2_MIN && time <= tp->t2_max && !(time < EPS && tp->t2_max < EPS))
        tp->t2_min = time;
    else if (act == CHANGE_T2_MAX && time >= tp->t2_min && !(time < EPS && tp->t2_min < EPS))
        tp->t2_max = time;
    else if (act == CHANGE_T3_MIN && time <= tp->t3_max && !(time < EPS && tp->t3_max < EPS))
        tp->t3_min = time;
    else if (act == CHANGE_T3_MAX && time >= tp->t3_min && !(time < EPS && tp->t3_min < EPS))
        tp->t3_max = time;
    else if (act == CHANGE_T4_MIN && time <= tp->t4_max && !(time < EPS && tp->t4_max < EPS))
        tp->t4_min = time;
    else if (act == CHANGE_T4_MAX && time >= tp->t4_min && !(time < EPS && tp->t4_min < EPS))
        tp->t4_max = time;
    else
        rc = ERR_INTERVAL_RANGE;

    if (rc == OK)
        printf("Интервал был успешно изменен\n\n");
    return rc;
}

double receive_time_1(time_params_t *tp)
{
    double min = tp->t1_min, max = tp->t1_max;
    if (fabs(tp->t1_max - tp->t1_min) < EPS)
        return tp->t1_max;
    srand(rand());
    double t = (double) rand() / RAND_MAX;
    if (PRINT)
    {
        printf("k1: %lf\n", t);
        sum_time += t;
        count_time++;
        double out = (max - min) * t + min;
        double mid = (max + min) / 2;
        if (mid > out)
            printf("k perc: \t%d\n", (int) (100 *(mid - out) / mid));
    }
    return (max - min) * t + min;
}

double receive_time_2(time_params_t *tp)
{
    double min = tp->t2_min, max = tp->t2_max;
    if (fabs(tp->t2_max - tp->t2_min) < EPS)
        return tp->t2_max;
    srand(rand());
    double t = (double) rand() / RAND_MAX;
    if (PRINT)
    {
        printf("k2: %lf\n", t);
        sum_time += t;
        count_time++;
        double out = (max - min) * t + min;
        double mid = (max + min) / 2;
        if (mid > out)
            printf("k perc: \t%d\n", (int) (100 *(mid - out) / mid));
    }
    return (max - min) * t + min;
}

double process_time_1(time_params_t *tp)
{
    double min = tp->t3_min, max = tp->t3_max;
    if (fabs(tp->t3_max - tp->t3_min) < EPS)
        return tp->t3_max;
    srand(rand());
    double t = (double) rand() / RAND_MAX;
    if (PRINT)
    {
        printf("k3: %lf\n", t);
        sum_time += t;
        count_time++;
        double out = (max - min) * t + min;
        double mid = (max + min) / 2;
        if (mid > out)
            printf("k perc: \t%d\n", (int) (100 *(mid - out) / mid));
    }
    return (max - min) * t + min;
}

double process_time_2(time_params_t *tp)
{
    double min = tp->t4_min, max = tp->t4_max;
    if (fabs(tp->t4_max - tp->t4_min) < EPS)
        return tp->t4_max;
    srand(rand());
    double t = (double) rand() / RAND_MAX;
    if (PRINT)
    {
        printf("k4: %lf\n", t);
        sum_time += t;
        count_time++;
        double out = (max - min) * t + min;
        double mid = (max + min) / 2;
        if (mid > out)
            printf("k perc: \t%d\n", (int) (100 *(mid - out) / mid));
    }
    return (max - min) * t + min;
}

void print_mid_koef()
{
    if (PRINT)
        printf("mid koef_t: %lf\n", sum_time / count_time);
}



