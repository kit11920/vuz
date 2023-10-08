#include <stdio.h>

#include "errs.h"


void print_error(const int rc)
{
    switch (rc)
    {
    case OK:
        break;
    case ERR_IO:
    {
        printf("ERR_IO: ошибка формата ввода\n");
        break;
    }
    case ERR_RANGE_STR:
    {
        printf("ERR_RANGE_STR: длина введенной строки слишком большая или строка пуста\n");
        break;
    }
    case ERR_NO_MANTISSA:
    {
        printf("ERR_NO_MANTISSA: введено 0 значащих цифр\n");
        break;
    }
    case ERR_RANGE_MANTISSA:
    {
        printf("ERR_RANGE_MANTISSA: длина мантисы слишком большая\n");
        break;
    }
    case ERR_ORDER_OVERFLOW:
    {
        printf("ERR_ORDER_OVERFLOW: переполнение порядка\n");
        break;
    }
    case ERR_DIVISION_ZERO:
    {
        printf("ERR_DIVISION_ZERO: деление на 0\n");
        break;
    }
    default:
    {
        printf("ERROR\n");
        break;
    }
    }
}
