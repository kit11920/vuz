#ifndef LIST_H__
#define LIST_H__

#include "stddef.h"
#include "time_system.h"
#include "free_adresses_arr.h"

#define MAX_LEN_LIST_QUEUE 50000

typedef struct struct_node_t
{
    double time;
    struct struct_node_t *next;
} node_t;

typedef struct struct_list_queue_t
{
    node_t *pout; // head
    node_t *pin; // tail
    size_t len;
    double last_time_pushed;
} list_queue_t;


void init_list_queue(list_queue_t *queue);

int just_push_list_queue(list_queue_t *queue, double req_time);

int push_list_queue(list_queue_t *queue, double req_time, free_adresses_t *arr);

int just_pop_list_queue(list_queue_t *queue, double *req_time);

int pop_list_queue(list_queue_t *queue, double *req_time, free_adresses_t *arr);

void print_list_queue(list_queue_t *queue);

void free_queue(list_queue_t *queue);

int process_list_queue(time_params_t *tp);


#endif
