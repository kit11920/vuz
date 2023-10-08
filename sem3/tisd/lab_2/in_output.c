#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errs.h"
#include "country_struct.h"

#include "fort.h"


int input_str(FILE *f, char *str, const size_t max_len_str)
{
    char *buf = NULL;
    size_t max_len_buf = max_len_str + 2;
    size_t len_buf = 0;

    buf = malloc(max_len_buf * sizeof(char));
    if (!buf)
        return ERR_DYNAMIC_MEMORY;

    if (!fgets(buf, max_len_buf * sizeof(char), f))
        return ERR_STR_INPUT;

    len_buf = strlen(buf);
    if (len_buf && buf[len_buf - 1] == '\n')
    {
        len_buf--;
        buf[len_buf] = 0;
    }
    //printf("%zu - '%s'\n", len_buf, buf);
    if (!len_buf || len_buf > max_len_str)
        return ERR_STR_LEN;

    strcpy(str, buf);
    free(buf);

    return OK;
}

int input_name(FILE *f, bool print_input_text, char *name)
{
    int rc;
    if (print_input_text)
        printf("Название страны (%d символов): \t", NAME_LEN);
    rc = input_str(f, name, NAME_LEN);
    if (rc != OK)
        return ERR_NAME_INPUT;
    return OK;
}

int input_capital(FILE *f, bool print_input_text, char *capital)
{
    int rc;
    if (print_input_text)
        printf("Столица (%d символов): \t", CAPITAL_LEN);
    rc = input_str(f, capital, CAPITAL_LEN);
    if (rc != OK)
        return ERR_CAPITAL_INPUT;
    return OK;
}

int input_continent(FILE *f, bool print_input_text, char *continent)
{
    int rc;
    if (print_input_text)
        printf("Материк (%d символов): \t", CONTINENT_LEN);
    rc = input_str(f, continent, CONTINENT_LEN);
    if (rc != OK)
        return ERR_CONTINENT_INPUT;
    return OK;
}

int input_visa(FILE *f, bool print_input_text, bool *visa)
{
    int visa_int;
    char tmp[2];

    if (print_input_text)
        printf("Необходимость визы (число 1 - нужна, 0 - не нужна): \t");

    if (fscanf(f, "%d", &visa_int) != 1)
        return ERR_VISE_INPUT;
    if (fgets(tmp, sizeof(tmp), f) && strcmp(tmp, "\n") != 0)
        return ERR_VISE_INPUT;
    if (visa_int == 1)
        *visa = true;
    else if (visa_int == 0)
        *visa = false;
    else
        return ERR_VISE_INPUT;
    return OK;
}

int input_time(FILE *f, bool print_input_text, int *time)
{
    char tmp[2];

    if (print_input_text)
        printf("Время полета до страны (в минутах): \t");
    if (fscanf(f, "%d", time) != 1)
        return ERR_TIME_INPUT;
    if (fgets(tmp, sizeof(tmp), f) && strcmp(tmp, "\n") != 0)
        return ERR_TIME_INPUT;
    if (*time < 0)
        return ERR_TIME_INPUT;
    return OK;
}

int input_cost_min(FILE *f, bool print_input_text, int *cost_min)
{
    char tmp[2];

    if (print_input_text)
        printf("Минимальная стоимость отдыхы (в рублях): \t");
    if (fscanf(f, "%d", cost_min) != 1)
        return ERR_COST_MIN_INPUT;
    if (fgets(tmp, sizeof(tmp), f) && strcmp(tmp, "\n") != 0)
        return ERR_COST_MIN_INPUT;
    if (*cost_min < 0)
        return ERR_COST_MIN_INPUT;
    return OK;
}

int input_type_tourism(FILE *f, bool print_input_text, type_tourism_t *type_tourism)
{
    int type_tourism_int;
    char tmp[2];

    if (print_input_text)
        printf("Вид туризма, введите число (экскурсионный - 0, пляжный - 1, спортивный - 2): \t");
    if (fscanf(f, "%d", &type_tourism_int) != 1)
        return ERR_TYPE_TOURISM_INPUT;
    if (fgets(tmp, sizeof(tmp), f) && strcmp(tmp, "\n") != 0)
        return ERR_TYPE_TOURISM_INPUT;

    *type_tourism = type_tourism_int;
    return OK;
}

int input_exrsn_trsm_count_sights(FILE *f, bool print_input_text, int *count_sights)
{
    char tmp[2];

    if (print_input_text)
        printf("Количество достопримечательностей: \t");

    if (fscanf(f, "%d", count_sights) != 1)
        return ERR_COUNT_SIGHTS_INPUT;
    if (fgets(tmp, sizeof(tmp), f) && strcmp(tmp, "\n") != 0)
        return ERR_COUNT_SIGHTS_INPUT;
    return OK;
}

int input_exrsn_trsm_type_sights(FILE *f, bool print_input_text, char *type_sights)
{
    int rc;
    if (print_input_text)
        printf("Вид достопримечательностей (строка %d символов): \t", TYPE_SIGHTS_LEN);
    rc = input_str(f, type_sights, TYPE_SIGHTS_LEN);
    if (rc != OK)
        return ERR_SIGHTS_INPUT;
    return OK;
}

int input_excursion_tourism(FILE *f, struct excursion_tourism_t *exrsn_trsm, bool print_input_text)
{
    int count_sights;
    char type_sights[TYPE_SIGHTS_LEN + 1];
    int rc = OK;

    if (print_input_text)
        printf("Экскурсионный вид туризма\n");

    rc = input_exrsn_trsm_count_sights(f, print_input_text, &count_sights);
    if (rc != OK)
        return rc;

    rc = input_exrsn_trsm_type_sights(f, print_input_text, type_sights);
    if (rc != OK)
        return rc;

    exrsn_trsm->count_sights = count_sights;
    strcpy(exrsn_trsm->type_sights, type_sights);

    return OK;
}

int input_beach_trsm_season(FILE *f, bool print_input_text, char *season)
{
    int rc;
    if (print_input_text)
        printf("Основной сезон (строка %d символов): \t",SEASON_LEN);
    rc = input_str(f, season, SEASON_LEN);
    if (rc != OK)
        return ERR_SEASON_INPUT;
    return OK;
}

int input_beach_trsm_air_temp(FILE *f, bool print_input_text, int *air_temp)
{
    char tmp[2];

    if (print_input_text)
        printf("Температура воздуха: \t");
    if (fscanf(f, "%d", air_temp) != 1)
        return ERR_AIR_TEMPERATURE_INPUT;
    if (fgets(tmp, sizeof(tmp), f) && strcmp(tmp, "\n") != 0)
        return ERR_AIR_TEMPERATURE_INPUT;

    return OK;
}

int input_beach_trsm_water_temp(FILE *f, bool print_input_text, int *water_temp)
{
    char tmp[2];

    if (print_input_text)
        printf("Температура воды: \t");
    if (fscanf(f, "%d", water_temp) != 1)
        return ERR_WATER_TEMPERATURE_INPUT;
    if (fgets(tmp, sizeof(tmp), f) && strcmp(tmp, "\n") != 0)
        return ERR_WATER_TEMPERATURE_INPUT;

    return OK;
}

int input_beach_tourism(FILE *f, struct beach_tourism_t *beach_trsm, bool print_input_text)
{
    char season[SEASON_LEN + 1];
    int air_temp, water_temp;
    int rc = OK;

    if (print_input_text)
        printf("Пляжный вид туризма\n");
    rc = input_beach_trsm_season(f, print_input_text, season);
    if (rc != OK)
        return rc;
    
    rc = input_beach_trsm_air_temp(f, print_input_text, &air_temp);
    if (rc != OK)
        return rc;
        
    rc = input_beach_trsm_water_temp(f, print_input_text, &water_temp);
    if (rc != OK)
        return rc;

    strcpy(beach_trsm->season, season);
    beach_trsm->air_tempr = air_temp;
    beach_trsm->water_tempr = water_temp;

    return OK;
}

int input_sport_type(FILE *f, bool print_input_text, char *sport_type)
{
    int rc;

    if (print_input_text)
    {
        printf("Спортивный вид туризма\n");
        printf("Вид спорта: \t");
    }
    rc = input_str(f, sport_type, SPORT_LEN);
    if (rc != OK)
        return ERR_TYPE_SPORT_INPUT;
    return OK;
}

int input_country(FILE *f, struct country_t *country, size_t ind, bool print_input_text)
{
    char name[NAME_LEN + 1];
    char capital[CAPITAL_LEN + 1];
    char continent[CONTINENT_LEN + 1];
    bool visa;
    int time;
    int cost_min;
    type_tourism_t type_tourism = -1;
    struct excursion_tourism_t excursion_trsm;
    struct beach_tourism_t beach_trsm;
    char sport_type[SPORT_LEN + 1];
    char tmp[2];
    int rc = OK;


    rc = input_name(f, print_input_text, name);
    if (rc != OK)
        return rc;
    
    rc = input_capital(f, print_input_text, capital);
    if (rc != OK)
        return rc;

    rc = input_continent(f, print_input_text, continent);
    if (rc != OK)
        return rc;
    
    rc = input_visa(f, print_input_text, &visa);
    if (rc != OK)
        return rc;

    rc = input_time(f, print_input_text, &time);
    if (rc != OK)
        return rc;
    
    rc = input_cost_min(f, print_input_text, &cost_min);
    if (rc != OK)
        return rc;

    rc = input_type_tourism(f, print_input_text, &type_tourism);
    if (rc != OK)
        return rc;

    if (type_tourism == EXCURSION_TOURISM)
    {
        rc = input_excursion_tourism(f, &excursion_trsm, print_input_text);
        if (rc != OK)
            return rc;
    } 
    else if (type_tourism == BEACH_TOURISM)
    {
        rc = input_beach_tourism(f, &beach_trsm, print_input_text);
        if (rc != OK)
            return rc;
    }
    else if (type_tourism == SPORT_TOURISM)
    {
        rc = input_sport_type(f, print_input_text, sport_type);
        if (rc != OK)
            return rc;
    }
    else
        return ERR_TYPE_TOURISM_INPUT;
        
    if (print_input_text)
        printf("\n\n");
    // после каждой структуры идет пустая строка
    if (f != stdin)
        fgets(tmp, sizeof(tmp), f);

    country->ind = ind;
    strcpy(country->name, name);
    strcpy(country->capital, capital);
    strcpy(country->continent, continent);
    country->visa = visa;
    country->time = time;
    country->cost_min = cost_min;
    country->type_tourism = type_tourism;
    if (type_tourism == EXCURSION_TOURISM)
        country->tourism.excursion_tourism = excursion_trsm;
    else if (type_tourism == BEACH_TOURISM)
        country-> tourism.beach_tourism = beach_trsm;
    else if (type_tourism == SPORT_TOURISM)
        strcpy(country->tourism.sport_type, sport_type);

    return OK;
}

int input_table(FILE *f, struct country_t table[], size_t *len_table, size_t max_len_table)
{
    int rc = OK;

    size_t i = 0;
    while (i <= max_len_table && (rc = input_country(f, &table[i], i + 1, false)) == OK)
        i++;
    if (i > max_len_table)
        return ERR_TOO_MANY_COUNTIES;
    // print_err(rc);
    *len_table = i;
    if (!feof(f) || *len_table == 0)
        return ERR_BAD_FILE;

    return OK;
}

int read_table(char *filename, struct country_t table[], size_t *len_table, size_t max_len_table)
{
    FILE *f;
    int rc;

    f = fopen(filename, "r");
    if (f == NULL)
        return ERR_FILE_NOT_EXIST;

    rc = input_table(f, table, len_table, max_len_table);
    fclose(f);
    if (rc != OK)
        return rc;
    
    return OK;
}



void visa_to_str(bool visa, char *visa_str)
{
    if (visa)
        strcpy(visa_str,"need");
    else 
        strcpy(visa_str,"no need"); 
}

void type_tourism_to_str(type_tourism_t type, char *str)
{
    if (type == EXCURSION_TOURISM)
        strcpy(str, "excutsion");
    else if (type == BEACH_TOURISM)
        strcpy(str, "beach");
    else
        strcpy(str, "sport");
}

void print_country(ft_table_t *tab, const struct country_t *country)
{
    char visa_str[8];
    char type_tourism_str[10];

    visa_to_str(country->visa, visa_str);
    type_tourism_to_str(country->type_tourism, type_tourism_str);

    if (country->type_tourism == EXCURSION_TOURISM)
    {
        ft_printf_ln(tab, "%zu|%s|%s|%s|%s|%d|%d|%s|%d|%s|%s|%s|%s|%s", country->ind, country->name, country->capital, 
        country->continent, visa_str,  country->time, country->cost_min, type_tourism_str, 
        country->tourism.excursion_tourism.count_sights, country->tourism.excursion_tourism.type_sights, "-", "-", "-", "-");
    } else if (country->type_tourism == BEACH_TOURISM)
    {
        ft_printf_ln(tab, "%zu|%s|%s|%s|%s|%d|%d|%s|%s|%s|%s|%d|%d|%s", country->ind, country->name, country->capital, country->continent, visa_str,
        country->time, country->cost_min, type_tourism_str, "-", "-",
        country->tourism.beach_tourism.season, country->tourism.beach_tourism.air_tempr, country->tourism.beach_tourism.water_tempr, "-");
    }
    else
    {
        ft_printf_ln(tab, "%zu|%s|%s|%s|%s|%d|%d|%s|%s|%s|%s|%s|%s|%s", country->ind, country->name, country->capital, 
        country->continent, visa_str,  country->time, country->cost_min, type_tourism_str, 
        "-", "-", "-", "-", "-", country->tourism.sport_type);
    }
}

void print_header_tab(ft_table_t *tab)
{
    ft_printf_ln(tab, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s", "ind", "name", "capital", "continent", "visa", "time go", 
    "cost min", "tourism", "count_sights", "type_sights", 
    "season", "air t", "water t", "sport_type");
}

void print_table(const struct country_t table[], const size_t len_table)
{
    ft_table_t *tab = ft_create_table();
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    print_header_tab(tab);

    for (size_t i = 0; i < len_table; i++)
    {
        print_country(tab, &table[i]);
    }
    
    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);

    printf("Длина таблицы: %zu\n\n", len_table);
}

void print_one_country(const struct country_t *country)
{
    ft_table_t *tab = ft_create_table();
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    print_header_tab(tab);

    print_country(tab, country);
    
    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);
}

void print_key_table(const struct key_table_t key_table[], const size_t len_table)
{
    ft_table_t *tab = ft_create_table();
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_printf_ln(tab, "%s|%s", "ind", "time go");

    for (size_t i = 0; i < len_table; i++)
        ft_printf_ln(tab, "%zu|%d", key_table[i].ind_orig, key_table[i].time);

    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);

    printf("Длина таблицы: %zu\n\n", len_table);
}

void print_table_based_on_key_table(const struct country_t table[], size_t len_table, const struct key_table_t key_table[])
{
    ft_table_t *tab = ft_create_table();
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    print_header_tab(tab);

    size_t ind_orig;
    for (size_t i = 0; i < len_table; i++)
    {
        ind_orig = key_table[i].ind_orig - 1;
        print_country(tab, &table[ind_orig]);
    }

    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);

    printf("Длина таблицы: %zu\n\n", len_table);
}





