#include "stdio.h"

#include "errs.h"


int print_err(int rc)
{
    switch (rc)
    {
    case OK:
        break;
    case ERR_COUNT_V:
        printf("ERR_COUNT_V: ошибка количества узлов");
        break;
    case ERR_COUNT_EDGE:
        printf("ERR_COUNT_EDGE: ошибка количества ребер");
        break;
    case ERR_EDGE:
        printf("ERR_EDGE: ошибка ввода ребра");
        break;
    case ERR_EXIST_EDGE:
        printf("ERR_EXIST_EDGE: такое ребро уже существует");
        break;
    case ERR_FILE:
        printf("ERR_FILE: ошибка в файле");
        break;
    case ERR_NO_EULER_PATH:
        printf("ERR_NO_EULER_PATH: в данном графе нет эйлерова пути");
        break;
    case ERR_NAME:
        printf("ERR_NAME: ошибка в названии страны");
        break;
    case ERR_NOT_CONNECTED:
        printf("ERR_NOT_CONNECTED: граф не связный");
        break;
    case ERR_TYPE_GRAPH:
        printf("ERR_TYPE_GRAPH: введен неверный тип графа");
        break;
    
    case ERR_MEM:
        printf("ERR_MEM: ошибка памяти");
        break;
    
    default:
        printf("ERR");
        break;
    }
    printf("\n\n");

    return rc;
}











