#include <stdio.h>
#include "errors.h"

void print_error(int rc)
{
    printf("ОШИБКА: ");
    switch (rc)
    {
        case ERR_IO:
            printf("ошибка ввода");
            break;
        case ERR_BUF_TOO_SMALL:
            printf("недостаточно буффера");
            break;
        case ERR_TOO_MUCH_WORDS:
            printf("слишком много слов");
            break;
        case ERR_NO_DIFF_WORDS:
            printf("строки одинаковые");
            break;
        case ERR_ONLY_SPACES:
            printf("в введены только разделительные символы");
            break;
        default:
            printf("неизвестная ошибка");
            break;
    }
    printf("\n");
}