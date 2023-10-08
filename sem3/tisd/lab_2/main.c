#include <stdio.h>
#include <string.h>

#include "errs.h"
#include "country_struct.h"
#include "in_output.h"
#include "work_table.h"
#include "sorts.h"
#include "interface.h"
#include "action.h"
#include "efficiency.h"


#define MAIN_40_DATA_FILE "data_table.txt"
#define BIG_100_DATA_FILE "big_data_table.txt"



#define NOW_DATA_FILE MAIN_40_DATA_FILE
#define PRINT_INPUT true

int main(void)
{
    struct country_t table[TABLE_LEN];
    struct key_table_t key_table[TABLE_LEN];
    size_t len_table;
    int rc = OK;

    // Заполняем таблицу данными из файла
    rc = read_table(NOW_DATA_FILE, table, &len_table, TABLE_LEN);
    if (rc != OK)
    {
        print_err(rc);
        if (rc % 10 == END_STOP_ERR)
            return rc;
        else if (rc % 10 == END_INPUT_ERR)
        {
            char c = getchar();
            while (c != '\n')
                c = getchar();
        }
    }
    //

    // Создаем таблицу ключей
    make_key_table(table, len_table, key_table);
    //

    int act = -1;
    // Вывод описания программы
    printf(GREETING);
    //

    while (act != 0)
    {
        printf(FEATURES);
        // Запрос действия
        // char c = 'a';
        while (scanf("%d", &act) != 1 || !(0 <= act && act <= 10))  
        {
            print_err(ERR_NUM_ACT_INPUT);
            printf(FEATURES);
            char c = getchar();
            while (c != '\n')
                c = getchar();
        }
        getchar();
        //

        if (act == 1)
        {
            // Произвести поиск информации по вариантному полю
            rc = act_find_and_print_countries(table, len_table);
            if (rc != OK)
            {
                print_err(rc);
                if (rc % 10 == END_STOP_ERR)
                    return rc;
                else if (rc % 10 == END_INPUT_ERR)
                {
                    char c = getchar();
                    while (c != '\n')
                        c = getchar();
                }
            }
        }
        else if (act == 2)
        {
            // Добавить запись в конец таблицы
            if (len_table == TABLE_LEN)
                print_err(ERR_ADD);
            else
            {
                rc = act_add_country(NOW_DATA_FILE, table, &len_table);
                if (rc != OK)
                {
                    print_err(rc);
                    if (rc % 10 == END_STOP_ERR)
                        return rc;
                    else if (rc % 10 == END_INPUT_ERR)
                    {
                        char c = getchar();
                        while (c != '\n')
                            c = getchar();
                    }
                }
            }

            // Обновление таблицы ключей
            make_key_table(table, len_table, key_table);
        }
        else if (act == 3)
        {
            // Удаление записи по занчению любого поля
            if (len_table == 1)
                print_err(ERR_DEL);
            else 
            {
                rc = act_del_country(NOW_DATA_FILE, table, &len_table);
                if (rc != OK)
                {
                    print_err(rc);
                    if (rc % 10 == END_STOP_ERR)
                        return rc;
                    else if (rc % 10 == END_INPUT_ERR)
                    {
                        char c = getchar();
                        while (c != '\n')
                            c = getchar();
                    }
                }
            }

            // Обновление таблицы ключей
            make_key_table(table, len_table, key_table);
        }
        else if (act == 4)
        {
            // Вывести исходную таблицу
            printf("Исходная таблица: \n");
            print_table(table, len_table);
        }
        else if (act == 5)
        {
            // Вывести таблицу ключей
            printf("Таблица ключей: \n");
            print_key_table(key_table, len_table);
        }
        else if (act == 6)
        {
            // Отсортировать таблицу ключей
            merge_sort_key_table(key_table, 0, len_table - 1);
            printf("Отсортированная таблица ключей: \n");
            print_key_table(key_table, len_table);
        }
        else if (act == 7)
        {
            // Вывести исходную таблицу в упорядоченном виде, используя упорядоченную
            // таблицу ключей (выполняется сортировка таблицы ключей)
            
            // Перезаписываем таблицу из файла, чтобы она имела изначальные неотсортированный вид и индексы таюлицы ключей воспадали
            rc = read_table(NOW_DATA_FILE, table, &len_table, TABLE_LEN);
            if (rc != OK)
                return rc;
            //

            merge_sort_key_table(key_table, 0, len_table - 1);
            printf("Исходная таблица в упорядоченном виде, по таблице ключей: \n");
            print_table_based_on_key_table(table, len_table, key_table);
        }
        else if (act == 8)
        {
            // Отсортировать исходную таблицу
            merge_sort_orig_table(table, 0, len_table - 1);
            printf("Упорядоченная исходная таблица: \n");
            print_table(table, len_table);
        }
        else if (act == 9)
        {
            // Вывести список стран на выбранном материке, со стоимостью ниже указанной, где
            // можно заняться указанным видом спорта
            rc = act_find_and_print_special_country(table, len_table);
            if (rc != OK)
            {
                print_err(rc);
                if (rc % 10 == END_STOP_ERR)
                    return rc;
                else if (rc % 10 == END_INPUT_ERR)
                {
                    char c = getchar();
                    while (c != '\n')
                        c = getchar();
                }
            }
        }
        else if (act == 10)
        {
            rc = make_compare_table(BIG_100_DATA_FILE);
            if (rc != OK)
            {
                print_err(rc);
                if (rc % 10 == END_STOP_ERR)
                    return rc;
                else if (rc % 10 == END_INPUT_ERR)
                {
                    char c = getchar();
                    while (c != '\n')
                        c = getchar();
                }
            }
        }
    }
    
    return OK;
}