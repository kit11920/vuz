#include "stdio.h"

#include "errs.h"



void print_err(int rc)
{
    switch (rc)
    {
    case OK:
        break;
    case ERR_DATA:
        printf("ERR_DATA: ошибка в данных узла списка");
        break;
    case ERR_MEM:
        printf("ERR_MEM: ошибка памяти");
        break;
    case ERR_NODE_EXIST:
        printf("ERR_NODE_EXIST: такой узел уже существует");
        break;
    case ERR_FILE:
        printf("ERR_FILE: ошибка записи в файл");
        break;
    default:
        break;
    }
    printf("\n");
}











