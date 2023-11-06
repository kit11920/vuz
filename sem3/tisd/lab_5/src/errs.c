#include <stdio.h>

#include "errs.h"


void print_err(int rc)
{
    switch (rc)
    {
    case OK:
        break;
    case ERR_RANGE_LONG:
        printf("ERR_RANGE_LONG: очередь переполнена\n\n");
        break;
    case ERR_RANGE_EMPTY:
        printf("ERR_RANGE_EMPTY: очередь пуста\n\n");
        break;
    case ERR_MEM:
        printf("ERR_MEM: ошибка выделения памяти (возможно из-за переполнения списка)\n\n");
        break;
    case ERR_NUM_ACT_INPUT:
        printf("ERR_NUM_ACT_INPUT: введен неверный номер действия\n\n");
        break;
    case ERR_IO:
        printf("ERR_IO: неверный способ ввода\n\n");
        break;
    case ERR_INTERVAL_RANGE:
        printf("ERR_INTERVAL_RANGE: неверное соотношения минимального и максимального времени в интервале (так же не может быть от 0 до 0)\n\n");
        break;
    
    default:
        printf("ERR: неизвествая ошибка\n\n");
        break;
    }
}


