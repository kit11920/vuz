#include <stdio.h>

#include "errs.h"
#include "country_struct.h"


void print_err(int rc)
{
    switch (rc)
    {
    case OK:
        return;
    case ERR_STR_INPUT:
        printf("ERR_STR_INPUT: ошибка ввода строки\n");
        break;
    case ERR_STR_LEN:
        printf("ERR_STR_LEN: строка неподходящей длины\n");
        break;
    case ERR_NAME_INPUT:
        printf("ERR_NAME_INPUT: ошибка ввода названия страны\n");
        break;
    case ERR_CAPITAL_INPUT:
        printf("ERR_CAPITAL_INPUT: ошибка ввода столицы\n");
        break;
    case ERR_CONTINENT_INPUT:
        printf("ERR_CONTINENT_INPUT: ошибка ввода континента\n");
        break;
    case ERR_VISE_INPUT:
        printf("ERR_VISE_INPUT: если виза нужна вводится - 1, если нет - 0, \
        другие значения не принимаются");
        break;
    case ERR_TIME_INPUT:
        printf("ERR_TIME_INPUT: ошибка ввода времени полета до страны\n");
        break;
    case ERR_COST_MIN_INPUT:
        printf("ERR_COST_MIN_INPUT: ошибка ввода минимальной стоимости отдыха\n");
        break;
    case ERR_TYPE_TOURISM_INPUT:
        printf("ERR_TYPE_TOURISM_INPUT: ошибка ввода вида туризма. Нужно ввести одно из чисел - (%d, %d, %d)\n", EXCURSION_TOURISM, BEACH_TOURISM, SPORT_TOURISM);
        break;
    case ERR_SIGHTS_INPUT:
        printf("ERR_SIGHTS_INPUT: ошибка ввода вида достопримечательностей\n");
        break;
    case ERR_COUNT_SIGHTS_INPUT:
        printf("ERR_COUNT_SIGHTS_INPUT: ошибка ввода количества достопримечательностей в экскурсионном туризме\n");
        break;
    case ERR_SEASON_INPUT:
        printf("ERR_SEASON_INPUT: ошибка ввода сезона\n");
        break;
    case ERR_AIR_TEMPERATURE_INPUT:
        printf("ERR_AIR_TEMPERATURE_INPUT: ошибка ввода температуры воздуха в пляжном туризме\n");
        break;
    case ERR_WATER_TEMPERATURE_INPUT:
        printf("ERR_WATER_TEMPERATURE_INPUT: ошибка ввода температуры воды в пляжном туризме\n");
        break;
    case ERR_TYPE_SPORT_INPUT:
        printf("ERR_TYPE_SPORT_INPUT: ошибка ввода вида спорта\n");
        break;
    case ERR_NUM_ACT_INPUT:
        printf("ERR_NUM_ACT_INPUT: вы ввели неверный код поля\n");
        break;


    case ERR_FILE_NOT_EXIST:
        printf("ERR_FILE_NOT_EXIST: Файл с таким названием не существует\n");
        break;
    case ERR_BAD_FILE:
        printf("ERR_BAD_FILE: файл неверного содержимого\n");
        break;
    case ERR_DYNAMIC_MEMORY:
        printf("ERR_DYNAMIC_MEMORY: ошибка выделения динамической памяти\n");
        break;


    case ERR_NO_COUNTRY_IN_TABLE:
        printf("ERR_NO_COUNTRY_IN_TABLE: попытка удалить страну которой нет в таблице\n");
        break;
    case ERR_TOO_MANY_COUNTIES:
        printf("ERR_TOO_MANY_COUNTIES: записей в таблице слишком много\n");
        break;
    case ERR_WRONG_INDEX:
        printf("ERR_WRONG_INDEX: введен неверный индекс\n");
        break;
    case ERR_ADD:
        printf("ERR_ADD: нельзя добавить запись: количество записей в таблице уже максимально\n");
        break;
    case ERR_DEL:
        printf("ERR_DEL: нельзя удалить запись: в таблице должна быть хотябы одна запись\n");
        break;

    
    default:
        printf("ERROR: unknown error\n");
        break;
    }
}