#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "arr.h"
#include "errs.h"
#include "time_system.h"

#define PRINT 0

void init_arr_queue(arr_queue_t *queue)
{
    queue->pin = queue->pout = &queue->data[0];
    queue->len_arr = 0;
    queue->plast = &queue->data[0] + MAX_LEN_ARR_QUEUE;
    queue->last_time_pushed = 0;
}

int push_arr_queue(arr_queue_t *queue, double req_time)
{
    // Проверка переполнения
    if (queue->pin == queue->pout && queue->len_arr != 0)
        return ERR_RANGE_LONG;
    //

    *queue->pin = req_time;

    // Сдвигаем индекс pin
    queue->pin++;
    queue->len_arr++;
    if (queue->pin == queue->plast)
        queue->pin = &queue->data[0];
    //

    return OK;
}

int pop_arr_queue(arr_queue_t *queue, double *req_time)
{
    // Проверка если массив пуст
    if (queue->len_arr == 0)
        return ERR_RANGE_EMPTY;
    //

    *req_time = *queue->pout;

    // Сдвигаем индекс pout
    queue->pout++;
    queue->len_arr--;
    if (queue->pout == queue->plast)
        queue->pout = &queue->data[0];
    //

    return OK;
}

void print_arr_queue(arr_queue_t *queue)
{
    printf("Очередь в виде массива (максимальная длина - %d): \n", MAX_LEN_ARR_QUEUE);
    if (queue->len_arr == 0)
        printf("Очередь пуста\n");
    else
    {
        double *ptmp = queue->pout;

        size_t count_print;
        if (PRINT && queue->len_arr > 10)
            count_print = 10;
        else
            count_print = queue->len_arr;
        for (size_t i = 0; i < count_print; i++)
        {
            printf(" %lf", *ptmp);
            ptmp++;
            if (ptmp == queue->plast)
                ptmp = queue->data;
        }
        printf("\n");   
    }
    printf("\n");
}

int process_arr_queue(time_params_t *tp)
{
    int rc = OK;
    arr_queue_t queue1, queue2;
    init_arr_queue(&queue1);
    init_arr_queue(&queue2);

    double time_now = 0.0;
    int count_prcs1_in = 0;
    int count_prcs2_in = 0;
    int count_prcs1_out = 0, count_prcs2_out = 0;
    size_t sum_len_queue1 = 0, sum_len_queue2 = 0;
    double mid_len_queue1, mid_len_queue2;
    double sum_time_in_queue1 = 0.0, sum_time_in_queue2 = 0.0;
    double real_non_work_time = 0, real_work_time = 0;
    int count_info_printed = 0;

    // tmp
    // double time2 = 0;
    // int count_time2 = 0;
    //

    srand(time(NULL));
    while (count_prcs1_out < 1000)
    {
        // Добавляем запросы в очередь 1 и 2 
        // пока время добавления последнего запроса не превысит время сейчас time_now
        if (PRINT)
            printf("time_now: %lf\n", time_now);
        _Bool good_range_time = 1;
        while ((good_range_time && queue1.last_time_pushed < time_now) || fabs(queue1.last_time_pushed) < EPS)
        {
            double time = receive_time_1(tp) + queue1.last_time_pushed;
            
            rc = push_arr_queue(&queue1, time);
            if (rc != OK)
                return rc;
            count_prcs1_in++;
            queue1.last_time_pushed = time;
            
            if (time_now < time)
                good_range_time = 0;
        }
        if (PRINT)
        {
            printf("1 ");
            print_arr_queue(&queue1);
        }

        good_range_time = 1;
        while ((good_range_time && queue2.last_time_pushed < time_now) || fabs(queue2.last_time_pushed) < EPS)
        {
            double receive2 = receive_time_2(tp);
            // time2 += receive2;
            // count_time2++;
            double time = receive2 + queue2.last_time_pushed;

            rc = push_arr_queue(&queue2, time);
            if (rc != OK)
                return rc;
            count_prcs2_in++;
            queue2.last_time_pushed = time;

            if (time_now < time)
                good_range_time = 0;

            // if (queue1.len_arr == 0 || time_now >= time)
            // {
            //     rc = push_arr_queue(&queue2, time);
            //     if (rc != OK)
            //         return rc;
            //     count_prcs2_in++;
            //     queue2.last_time_pushed = time;
            //     // printf("len - %zu\n", queue2.len_arr);
            //     // printf("time_now - %lf time_add2 - %lf, receive_t - %lf, num - %d\n", time_now, time, receive2, count_prcs2_in);
            // }
            // else
            //     good_range_time = 0;
        }
        if (PRINT)
        {
            printf("2 ");
            print_arr_queue(&queue2);
            printf("last time - %lf\n", queue2.last_time_pushed);
        }
        //

        if (queue2.len_arr != 0 && *queue1.pout > time_now && *queue2.pout < *queue1.pout)
        {
            double time, process_time;

            // Извлекаем заявку из очереди 2
            rc = pop_arr_queue(&queue2, &time);
            if (rc != OK)
                return rc;
            //
            if (PRINT)
                printf("pop 2: %lf\n", time);
            if (time_now > time)
                sum_time_in_queue2 += time_now - time;
            else
            {
                // Учитываем простой
                real_non_work_time += time - time_now;
                time_now = time;
            }
            

            // Выполняем заявку изменяя время сейчас time_now
            process_time = process_time_2(tp);
            time_now += process_time;
            real_work_time += process_time;
            //
            count_prcs2_out++;
        }
        else if (queue1.len_arr != 0)
        {
            double time, process_time;

            // Извлекаем заявку из очереди 1
            rc = pop_arr_queue(&queue1, &time);
            if (rc != OK)
                return rc;
            //
            if (PRINT)
                printf("pop 1: %lf\n", time);
            if (time_now > time)
                sum_time_in_queue1 += time_now - time;
            else
            {
                // Учитываем простой
                real_non_work_time += time - time_now;
                time_now = time;
            }

            // Выполняем заявку изменяя время сейчас time_now
            process_time = process_time_1(tp);
            time_now += process_time;
            real_work_time += process_time;
            //

            count_prcs1_out++;
        }
        sum_len_queue1 += queue1.len_arr;
        sum_len_queue2 += queue2.len_arr;

        // каждые 100 выполненных заявок типа 1 выводим информацию о системе
        if (count_prcs1_out != 0 && count_prcs1_out % 100 == 0 && count_prcs1_out / 100 > count_info_printed)
        {
            mid_len_queue1 = (double) sum_len_queue1 / (count_prcs1_out + count_prcs2_out);
            mid_len_queue2 = (double) sum_len_queue2 / (count_prcs1_out + count_prcs2_out);
            printf("Обработано процессов типа 1: %d\n", count_prcs1_out);
            printf("Длина сейчас очереди 1: \t\t\t%zu\n", queue1.len_arr);
            printf("Средняя длина очереди 1:\t\t\t%lf\n", mid_len_queue1);
            // printf("\n");
            printf("Длина сейчас очереди 2: \t\t\t%zu\n", queue2.len_arr);
            printf("Средняя длина очереди 2:\t\t\t%lf\n", mid_len_queue2);
            // printf("\n");
            printf("Кол-во вошедших заявок в очередь 1:     \t%d\n", count_prcs1_in);
            printf("Кол-во обработанных заявок из очереди 1:\t%d\n", count_prcs1_out);
            // printf("\n");
            printf("Кол-во вошедших заявок в очередь 2:     \t%d\n", count_prcs2_in);
            printf("Кол-во обработанных заявок из очереди 2:\t%d\n", count_prcs2_out);
            // printf("\n");
            printf("Среднее время пребывания заявки в очереди 1:\t%lf\n", sum_time_in_queue1 / count_prcs1_out);
            printf("Среднее время пребывания заявки в очереди 2:\t%lf\n", sum_time_in_queue2 / count_prcs2_out);
            printf("\n");
            
            count_info_printed++;
        }
    }

    printf("Сравнение расчетного времени и получившегося:\n");
    double all_time_calc;
    int perc_diff; 
    // double work_oa_time, non_work_oa_time;
    double t1_mid, t3_mid; //, t2_mid, t4_mid;
    t1_mid = (tp->t1_min + tp->t1_max) / 2;
    // t2_mid = (tp->t2_min + tp->t2_max) / 2;
    t3_mid = (tp->t3_min + tp->t3_max) / 2;
    // t4_mid = (tp->t4_min + tp->t4_max) / 2;
    
    if (t1_mid > t3_mid)
        all_time_calc = t1_mid * 1000;
    else
        all_time_calc = t3_mid * 1000;

    // double count_prcs1_calc = 1000, count_prcs2_calc;
    // double work_time_prcs1_calc, work_time_prcs2_calc, non_work_calc;
    // work_time_prcs1_calc = t3_mid *count_prcs1_calc;
    // count_prcs2_calc = (t1_mid - t3_mid) * count_prcs1_calc * (t1_mid - t3_mid) / t2_mid;
    // work_time_prcs2_calc = count_prcs2_calc * t4_mid;
    // non_work_calc = all_time_calc - work_time_prcs1_calc - work_time_prcs2_calc;

    // work_oa_time = count_prcs1_out * t3_mid + count_prcs2_out * t4_mid;
    // if ((mid_len_queue1 <= 1 || mid_len_queue2 <= 1) && mid_len_queue1 <= 1)
    // {
    //     double time_wait1 = (t1_mid - t3_mid) * count_prcs1_out;
    //     double time_wait2 = (t2_mid - t4_mid) * count_prcs2_out;
    //     if (time_wait1 > time_wait2)
    //         all_time_calc = time_wait1;
    //     else
    //         all_time_calc = time_wait2;
    //     non_work_oa_time = all_time_calc - work_oa_time;
    //     // non_work_oa_time = (t1_mid - t3_mid) * count_prcs1_out - count_prcs2_out * t4_mid;
    //     // non_work_oa_time += (t2_mid - t4_mid) * count_prcs2_out - count_prcs1_out * t3_mid;
    // }
    // else if (mid_len_queue1 <= 1)
    // {
    //     double time_wait2 = (t2_mid - t4_mid) * count_prcs2_out;
    //     all_time_calc = time_wait2;
    //     non_work_oa_time = all_time_calc - work_oa_time;
    // }
    // else if (mid_len_queue2 <= 1)
    // {
    //     double time_wait1 = (t1_mid - t3_mid) * count_prcs1_out;
    //     all_time_calc = time_wait1;
    //     non_work_oa_time = all_time_calc - work_oa_time;
    // }
    // else
    // {
    //     non_work_oa_time = 0;
    //     all_time_calc = work_oa_time + non_work_oa_time;
    // }
    // if (queue1.len_arr == 0 && t1_mid > t3_mid)
    // {
    //     // Все время что оа стоял относительно 1типа заявок, он мог выполнят 2типо
    //     non_work_oa_time = (t1_mid - t3_mid) * count_prcs1_out - count_prcs2_out * t4_mid;
    // }
    // else if (queue2.len_arr == 0 && t2_mid > t4_mid)
    // {
    //     non_work_oa_time = (t2_mid - t4_mid) * count_prcs2_out - count_prcs1_out * t3_mid;
    // }
    // else
    //     non_work_oa_time = 0;
    // if (non_work_oa_time < 0)
    //     non_work_oa_time = 0;

    if (all_time_calc > time_now)
        perc_diff = (int) (100 * (all_time_calc - time_now) / all_time_calc);
    else
        perc_diff = -(int) (100 * (time_now - all_time_calc) / time_now);

    printf("На практике время моделирования: %lf\n", time_now);
    printf("Расчитанное время моделирования: %lf\n", all_time_calc);
    printf("Процент расхождения: %d%%\n", perc_diff);
    printf("\n");
    // printf("Расчитанное Время работы:  %lf\n", work_time_prcs1_calc + work_time_prcs2_calc);
    printf("Время работы:     %lf\n", real_work_time);
    // printf("\n");
    // printf("Расчитанное время простоя: %lf\n", non_work_calc);
    printf("Время простоя:    %lf\n", real_non_work_time);
    printf("\n");

    // printf("time2: %lf\n", time2);
    // printf("mid_time2_receive: %lf\n", time2 / count_time2);
    // printf("sum2: %lf\n", time2);
    
    // print_mid_koef();
    return OK;
}











