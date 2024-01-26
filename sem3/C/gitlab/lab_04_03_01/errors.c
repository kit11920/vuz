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
// с данными условиями ошибка не вызывается
//        case ERR_TOO_MUCH_WORDS:
//            printf("слишком много слов");
            break;
        case ERR_NO_DIFF_WORDS:
            printf("все слова одинаковые");
            break;
        case ERR_ONLY_ONE_WORD:
            printf("введено строка только из одного слова");
            break;
        case ERR_ONLY_DELIMS:
            printf("в введены только разделительные символы");
            break;
        default:
            printf("неизвестная ошибка");
            break;
    }
    printf("\n");
}
