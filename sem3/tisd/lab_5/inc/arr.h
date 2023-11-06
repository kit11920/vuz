#ifndef ARR_H__
#define ARR_H__

#include "stddef.h"
#include "time_system.h"

#define MAX_LEN_ARR_QUEUE 10000


typedef struct stuct_arr_queue
{
    double data[MAX_LEN_ARR_QUEUE]; // элемент массива - время поступления этого элемента (запроса)
    double *pin;
    double *pout;
    size_t len_arr;
    double *plast;
    double last_time_pushed;
} arr_queue_t;

/// @brief Инициализирует очередь как пустую
/// @param queue 
void init_arr_queue(arr_queue_t *queue);

/// @brief Добавление элемента в очередь
/// @param queue 
int push_arr_queue(arr_queue_t *queue, double req_time);

/// @brief Исключение элемента из очереди, 
/// значение исключенного элемента помещается в переменную req_time
/// @param queue 
/// @param req_time 
/// @return 
int pop_arr_queue(arr_queue_t *queue, double *req_time);

/// @brief Выводит очередь
/// @param queue 
void print_arr_queue(arr_queue_t *queue);

int process_arr_queue(time_params_t *tp);

#endif
