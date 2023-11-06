#include <stdio.h>

#include "errs.h"


void print_err(int rc)
{
    switch (rc)
    {
    case OK:
        break;
    case ERR_RANGE_LONG:
        printf("ERR_RANGE_LONG: нельзя добавить элемент, так как стек уже заполнен\n");
        break;
    case ERR_IO:
        printf("ERR_IO: ошибка ввода нового элемента стека\n");
        break;
    case ERR_RANGE_EMPTY:
        printf("ERR_RANGE_EMPTY: нельзя удалить элемент из пустого стека\n");
        break;
    case ERR_NUM_ACT_INPUT:
        printf("ERR_NUM_ACT_INPUT: введен неверный номер действия\n");
        break;
    case ERR_MEM:
        printf("ERR_MEM: ошибка выделения памяти (стек переполнен)\n");
        break;
    case ERR_COUNT_REPEAT_TIME_SMALL:
        printf("ERR_COUNT_REPEAT_TIME_SMALL: колво повторений недостаточно\n");
        break;
    
    default:
        printf("ERR_UNKNOWN\n");
        break;
    }
}




