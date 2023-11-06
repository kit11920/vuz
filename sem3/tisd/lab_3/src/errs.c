#include <stdio.h>

#include "errs.h"


void print_err(int rc)
{
    switch (rc)
    {
        case OK:
            break;
        case ERR_IO:
            printf("ERR_IO: ошибка ввода\n");
            break;
        case ERR_MEM:
            printf("ERR_MEM: ошибка выделения памяти\n");
            break;
        case ERR_NUM_ACT_INPUT:
            printf("ERR_NUM_ACT_INPUT: введен неверный номер действия\n");
            break;
        case ERR_COUNT_REPEAT_TIME_SMALL:
            printf("ERR_COUNT_REPEAT_TIME_SMALL: колво повторений недостаточно\n");
            break;
        case ERR_RANGE:
            printf("ERR_RANGE: выход за пределы массива\n");
            break;
    }
}


