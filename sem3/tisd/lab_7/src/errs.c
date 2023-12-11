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
    case ERR_NODE_EXIST:
        printf("ERR_NODE_EXIST: такой узел уже существует");
        break;
    case ERR_FILE:
        printf("ERR_FILE: ошибка записи в файл");
        break;
    case ERR_NOT_FOUND:
        printf("ERR_NOT_FOUND: элемент не найден");
        break;
    case ERR_NUM_ACT_INPUT:
        printf("ERR_NUM_ACT_INPUT: введен неверный номер действия\n\n");
        break;
    case ERR_EMPTY_TREE:
        printf("ERR_EMPTY_TREE: дерево пустое");
        break;

    case ERR_MEM:
        printf("ERR_MEM: ошибка памяти");
        break;
    
    default:
        break;
    }
    printf("\n");
}











