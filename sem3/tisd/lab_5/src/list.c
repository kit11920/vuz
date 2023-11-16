#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "list.h"
#include "errs.h"
#include "time_system.h"
#include "free_adresses_arr.h"


#define PRINT 0

void init_list_queue(list_queue_t *queue)
{
    queue->pout = NULL;
    queue->pin = NULL;
    queue->len = 0;
    queue->last_time_pushed = 0.0;
}

int just_push_list_queue(list_queue_t *queue, double req_time)
{
    // Проверка переполнения
    if (queue->len == MAX_LEN_LIST_QUEUE)
        return ERR_RANGE_LONG;
    //

    // Выделяем память под новый узел
    node_t *tmp = malloc(sizeof(node_t));
    if (tmp == NULL)
        return ERR_MEM;
    tmp->time = req_time;
    tmp->next = NULL;
    //

    // Изменяем указатель pin
    if (queue->pin != NULL)
        queue->pin->next = tmp;
    else
        queue->pout = tmp;
    queue->pin = tmp;
    //

    queue->len++;

    return OK;
}

int push_list_queue(list_queue_t *queue, double req_time, free_adresses_t *arr)
{
    // Проверка переполнения
    if (queue->len == MAX_LEN_LIST_QUEUE)
        return ERR_RANGE_LONG;
    //

    // Выделяем память под новый узел
    node_t *tmp = malloc(sizeof(node_t));
    if (tmp == NULL)
        return ERR_MEM;
    tmp->time = req_time;
    tmp->next = NULL;
    //

    // Изменяем указатель pin
    if (queue->pin != NULL)
        queue->pin->next = tmp;
    else
        queue->pout = tmp;
    queue->pin = tmp;
    //

    // Удаляем адрес нового элемента из массива свободных членов если надо
    del_elem_free_adresses_arr(arr, tmp);
    //

    queue->len++;

    return OK;
}

int just_pop_list_queue(list_queue_t *queue, double *req_time)
{
    // Проверка если массив пуст
    if (queue->len == 0)
        return ERR_RANGE_EMPTY;
    //
    *req_time = queue->pout->time;

    queue->len--;
    // Сдвигаем индекс pout
    node_t *tmp = queue->pout;
    if (queue->len == 0)
    {
        queue->pout = NULL;
        queue->pin = NULL;
    }
    else
        queue->pout = queue->pout->next;
    free(tmp);
    //

    return OK;
}

int pop_list_queue(list_queue_t *queue, double *req_time, free_adresses_t *arr)
{
    // Проверка если массив пуст
    if (queue->len == 0)
        return ERR_RANGE_EMPTY;
    //
    *req_time = queue->pout->time;

    queue->len--;
    // Сдвигаем индекс pout
    node_t *tmp = queue->pout;
    if (queue->len == 0)
    {
        queue->pout = NULL;
        queue->pin = NULL;
    }
    else
        queue->pout = queue->pout->next;
    free(tmp);
    //

    // Добавляем освободишийся адресс в массив свободных членов
    add_elem_free_adresses_arr(arr, tmp);
    //

    return OK;
}

void print_list_queue(list_queue_t *queue)
{
    printf("Очередь в виде списка (максимальная длина - %d): \n", MAX_LEN_LIST_QUEUE);
    if (queue->len == 0)
        printf("Очередь пуста\n");
    else
    {
        node_t *tmp = queue->pout;

        while (tmp != NULL)
        {
            printf(" %lf", tmp->time);
            tmp = tmp->next;
        }
        printf("\n");
    }
    printf("\n");
}

void free_queue(list_queue_t *queue)
{
    double tmp;
    while (queue->len != 0)
        just_pop_list_queue(queue, &tmp);
    
}

int process_list_queue(time_params_t *tp)
{
    int rc = OK;
    list_queue_t queue1, queue2;
    init_list_queue(&queue1);
    init_list_queue(&queue2);

    free_adresses_t arr;
    init_free_adresses_arr(&arr);

    double time_now = 0.0;
    int count_prcs1_in = 0, count_prcs2_in = 0;
    int count_prcs1_out = 0, count_prcs2_out = 0;
    size_t sum_len_queue1 = 0, sum_len_queue2 = 0;
    double mid_len_queue1, mid_len_queue2;
    double sum_time_in_queue1 = 0.0, sum_time_in_queue2 = 0.0;
    double real_non_work_time = 0, real_work_time = 0;
    int count_info_printed = 0;

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
            
            rc = push_list_queue(&queue1, time, &arr);
            if (rc != OK)
                return rc;
            count_prcs1_in++;
            queue1.last_time_pushed = time;
            
            if (time_now < time)
                good_range_time = 0;
        }
        // while (queue1.len == 0 || good_range_time)
        // {
        //     double time = receive_time_1(tp) + queue1.last_time_pushed;
        //     if (queue1.len == 0 || time <= time_now)
        //     {
        //         rc = push_list_queue(&queue1, time, &arr);
        //         if (rc != OK)
        //             return rc;
        //         count_prcs1_in++;
        //         queue1.last_time_pushed = time;
        //     }
        //     else
        //         good_range_time = 0;
        // }
        if (PRINT)
        {
            printf("1 ");
            print_list_queue(&queue1);
        }

        good_range_time = 1;
        while ((good_range_time && queue2.last_time_pushed < time_now) || fabs(queue2.last_time_pushed) < EPS)
        {
            double receive2 = receive_time_2(tp);
            // time2 += receive2;
            // count_time2++;
            double time = receive2 + queue2.last_time_pushed;

            rc = push_list_queue(&queue2, time, &arr);
            if (rc != OK)
                return rc;
            count_prcs2_in++;
            queue2.last_time_pushed = time;

            if (time_now < time)
                good_range_time = 0;
        }
        // while (queue2.len == 0 || good_range_time)
        // {
        //     double time = receive_time_2(tp) + queue2.last_time_pushed;
        //     if (queue2.len == 0 || time <= time_now)
        //     {
        //         rc = push_list_queue(&queue2, time, &arr);
        //         if (rc != OK)
        //             return rc;
        //         count_prcs2_in++;
        //         queue2.last_time_pushed = time;
        //     }
        //     else
        //         good_range_time = 0;
        // }
        if (PRINT)
        {
            printf("2 ");
            print_list_queue(&queue2);
        }
        //

        // if (*queue1.pout > time_now && *queue2.pout < *queue1.pout)
        if (queue1.pout->time > time_now && queue1.pout->time > queue2.pout->time)
        {
            double time, process_time;

            // Извлекаем заявку из очереди 2
            rc = pop_list_queue(&queue2, &time, &arr);
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
        else
        {
            double time, process_time;

            // Извлекаем заявку из очереди 1
            rc = pop_list_queue(&queue1, &time, &arr);
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
        sum_len_queue1 += queue1.len;
        sum_len_queue2 += queue2.len;

        // каждые 100 выполненных заявок типа 1 выводим информацию о системе
        if (count_prcs1_out != 0 && count_prcs1_out % 100 == 0 && count_prcs1_out / 100 > count_info_printed)
        {
            mid_len_queue1 = (double) sum_len_queue1 / (count_prcs1_out + count_prcs2_out);
            mid_len_queue2 = (double) sum_len_queue2 / (count_prcs1_out + count_prcs2_out);
            printf("Обработано процессов типа 1: %d\n", count_prcs1_out);
            printf("Длина сейчас очереди 1: \t\t\t%zu\n", queue1.len);
            printf("Средняя длина очереди 1:\t\t\t%lf\n", mid_len_queue1);
            // printf("\n");
            printf("Длина сейчас очереди 2: \t\t\t%zu\n", queue2.len);
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
    print_free_adresses_arr(&arr);
    printf("\n");
    
    print_mid_koef();

    free_queue(&queue1);
    free_queue(&queue2);
    free(arr.a);
    return OK;
}


