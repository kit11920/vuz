#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "country_struct.h"
#include "work_table.h"
#include "interface.h"
#include "errs.h"
#include "in_output.h"


int get_field_and_cmp(struct country_t *searching, cmp_country_t *cmp)
{
    int rc = OK;
    int field = -1;

    // Запрос поля по которому будем искать
    printf(ASK_FIELD_SEARCH);
    if (scanf("%d", &field) != 1 || !(1 <= field && field <= 12))  
        return ERR_NUM_ACT_INPUT;
    getchar(); // считываем \n т к потом будем считывать строки
    //

    if (field == 1)
    {
        *cmp = cmp_country_name;
        rc = input_name(stdin, true, searching->name);
    }
    else if (field == 2)
    {
        *cmp = cmp_country_capital;
        rc = input_capital(stdin, true, searching->capital);
    }
    else if (field == 3)
    {
        *cmp = cmp_country_continent;
        rc = input_continent(stdin, true, searching->continent);
    }
    else if (field == 4)
    {
        *cmp = cmp_country_visa;
        rc = input_visa(stdin, true, &searching->visa);
    }
    else if (field == 5)
    {
        *cmp = cmp_country_time;
        rc = input_time(stdin, true, &searching->time);
    }
    else if (field == 6)
    {
        *cmp = cmp_country_cost_min;
        rc = input_cost_min(stdin, true, &searching->cost_min);
    }
    else if (field == 7)
    {
        *cmp = cmp_country_exrsn_trsm_count_sights;
        searching->type_tourism = EXCURSION_TOURISM;
        rc = input_exrsn_trsm_count_sights(stdin, true, &searching->tourism.excursion_tourism.count_sights);
    }
    else if (field == 8)
    {
        *cmp = cmp_country_exrsn_trsm_type_sights;
        searching->type_tourism = EXCURSION_TOURISM;
        rc = input_exrsn_trsm_type_sights(stdin, true, searching->tourism.excursion_tourism.type_sights);
    }
    else if (field == 9)
    {
        *cmp = cmp_country_beach_trsm_season;
        searching->type_tourism = BEACH_TOURISM;
        rc = input_beach_trsm_season(stdin, true, searching->tourism.beach_tourism.season);
    }
    else if (field == 10)
    {
        *cmp = cmp_country_beach_trsm_air_tempr;
        searching->type_tourism = BEACH_TOURISM;
        rc = input_beach_trsm_air_temp(stdin, true, &searching->tourism.beach_tourism.air_tempr);
    }
    else if (field == 11)
    {
        *cmp = cmp_country_beach_trsm_water_tempr;
        searching->type_tourism = BEACH_TOURISM;
        rc = input_beach_trsm_water_temp(stdin, true, &searching->tourism.beach_tourism.water_tempr);
    }
    else if (field == 12)
    {
        *cmp = cmp_country_sport_trsm_sport_type;
        searching->type_tourism = SPORT_TOURISM;
        rc = input_sport_type(stdin, true, searching->tourism.sport_type);
    }

    return rc;
}

int act_find_and_print_countries(const struct country_t table[], const size_t len_table)
{
    struct country_t searching;
    cmp_country_t cmp;
    int ind_arr[TABLE_LEN];
    size_t len_ind_arr = 0;
    int rc = OK;

    rc = get_field_and_cmp(&searching, &cmp);
    if (rc != OK)
        return rc;
    
    find_country(table, len_table, &searching, cmp, ind_arr, &len_ind_arr);
    if (len_ind_arr == 0)
        printf("\nТакой страны нет в таблице\n");
    else
    {
        printf("\nНайдены страны:\n");

        ft_table_t *tab = ft_create_table();
        ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
        print_header_tab(tab);

        for (size_t i = 0; i < len_ind_arr; i++)
            print_country(tab, &table[ind_arr[i]]);

        printf("%s\n", ft_to_string(tab));
        ft_destroy_table(tab);
    }

    return OK;
}

int act_add_country(char *filename, struct country_t table[], size_t *len_table)
{
    struct country_t new;
    FILE *f;
    int rc = OK;

    if (*len_table + 1 > TABLE_LEN)
        return ERR_TOO_MANY_COUNTIES;

    printf("Введите данные о стране которую хотите добавить: \n");
    rc = input_country(stdin, &new, *len_table + 1, true);
    if (rc != OK)
        return rc;
    
    // Записываем страну в конец файла
    f = fopen(filename, "a");
    if (f == NULL)
        return ERR_FILE_NOT_EXIST;

    file_write_country(f, &new);

    fclose(f);
    //
    table[*len_table] = new;
    (*len_table)++;
    printf("Страна добавлена в конец таблицы\n\n");

    return OK;
}

int act_del_country(char *filename, struct country_t table[], size_t *len_table)
{
    struct country_t searching;
    cmp_country_t cmp;
    int ind_arr[TABLE_LEN];
    size_t len_ind_arr;
    size_t ind_searching;
    int rc = OK;

    // Перезаписываем таблицу из файла, чтобы потом записать обновленную с удаленным элементом в том же порядке
    rc = read_table(filename, table, len_table, TABLE_LEN);
    if (rc != OK)
        return rc;
    //

    rc = get_field_and_cmp(&searching, &cmp);
    if (rc != OK)
        return rc;
    
    find_country(table, *len_table, &searching, cmp, ind_arr, &len_ind_arr);
    if (len_ind_arr == 0)
    {
        printf("\nТакой страны нет в таблице\n");
        return OK;
    }
    else if (len_ind_arr == 1)
        ind_searching = ind_arr[0];
    else
    {
        // Выводим таблицу подходящих стран
        ft_table_t *tab = ft_create_table();
        ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
        print_header_tab(tab);

        for (size_t i = 0; i < len_ind_arr; i++)
            print_country(tab, &table[ind_arr[i]]);

        printf("%s\n", ft_to_string(tab));
        ft_destroy_table(tab);
        //
        // Выбор индекса страны
        printf("Найдено несколько подходящих стран\n");
        printf("Введите индекс, страны которую хотите удалить: ");
        if (scanf("%zu", &ind_searching) != 1)
            return ERR_WRONG_INDEX;
        
        rc = ERR_WRONG_INDEX;

        //индекс сначалы был введен как индекс страны в таблице, переведем его в индекс желемнта массива
        for (size_t i = 0; i < len_ind_arr; i++)
            if (table[ind_arr[i]].ind == ind_searching)
            {
                ind_searching = ind_arr[i];
                rc = OK;
            }
        if (rc != OK)
            return rc;
        //
    }

    printf("\nУдалена страна:\n");
    print_one_country(&table[ind_searching]);
    del_country(table, len_table, ind_searching);

    file_write_table(filename, table, *len_table);

    return OK;
}

// Вывести список стран на выбранном материке, со стоимостью ниже указанной, где
// можно заняться указанным видом спорта
int act_find_and_print_special_country(const struct country_t table[], const size_t len_table)
{
    int rc = OK;
    char continent[CONTINENT_LEN + 1];
    int cost_min;
    char sport_type[SPORT_LEN + 1];
    int count_printed = 0;

    rc = input_continent(stdin, true, continent);
    if (rc != OK)
        return rc;
    rc = input_cost_min(stdin, true, &cost_min);
    if (rc != OK)
        return rc;
    rc = input_sport_type(stdin, true, sport_type);
    if (rc != OK)
        return rc;

    printf("\n");

    ft_table_t *tab = ft_create_table();
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    print_header_tab(tab);

    for (size_t i = 0; i < len_table; i++)
    {
        if (table[i].type_tourism == SPORT_TOURISM && strcmp(table[i].tourism.sport_type, sport_type) == 0 &&
        table[i].cost_min < cost_min && strcmp(table[i].continent, continent) == 0)
        {
            print_country(tab, &table[i]);
            count_printed++;
        }
    }

    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);

    if (count_printed == 0)
        printf("Подходящих стран в таблице нет\n");
    else
        printf("Выведено стран: %d\n", count_printed);

    return OK;
}









