#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "country_struct.h"
#include "work_table.h"
#include "errs.h"
#include "in_output.h"


int cmp_country_name(const struct country_t *l, const struct country_t *r);
int cmp_country_capital(const struct country_t *l, const struct country_t *r);
int cmp_country_continent(const struct country_t *l, const struct country_t *r);
int cmp_country_visa(const struct country_t *l, const struct country_t *r);
int cmp_country_time(const struct country_t *l, const struct country_t *r);
int cmp_country_cost_min(const struct country_t *l, const struct country_t *r);
int cmp_country_exrsn_trsm_count_sights(const struct country_t *l, const struct country_t *r);
int cmp_country_exrsn_trsm_type_sights(const struct country_t *l, const struct country_t *r);
int cmp_country_beach_trsm_season(const struct country_t *l, const struct country_t *r);
int cmp_country_beach_trsm_air_tempr(const struct country_t *l, const struct country_t *r);
int cmp_country_beach_trsm_water_tempr(const struct country_t *l, const struct country_t *r);
int cmp_country_sport_trsm_sport_type(const struct country_t *l, const struct country_t *r);


void find_country(const struct country_t table[], const size_t len_table, 
                const struct country_t *searching, cmp_country_t cmp, int ind_arr[], size_t *len_ind_arr)
{
    *len_ind_arr = 0;

    for (size_t i = 0; i < len_table; i++)
    {
        if (cmp == cmp_country_exrsn_trsm_count_sights || cmp == cmp_country_exrsn_trsm_type_sights)
        {
            if (table[i].type_tourism == EXCURSION_TOURISM && cmp(&table[i], searching) == 0)
            {
                ind_arr[*len_ind_arr] = i;
                (*len_ind_arr)++;
            }
        }
        else if (cmp == cmp_country_beach_trsm_season || cmp == cmp_country_beach_trsm_air_tempr ||
                cmp == cmp_country_beach_trsm_water_tempr)
        {
            if (table[i].type_tourism == BEACH_TOURISM && cmp(&table[i], searching) == 0)
            {
                ind_arr[*len_ind_arr] = i;
                (*len_ind_arr)++;
            }
        }
        else if (cmp == cmp_country_sport_trsm_sport_type)
        {
            if (table[i].type_tourism == SPORT_TOURISM && cmp(&table[i], searching) == 0)
            {
                ind_arr[*len_ind_arr] = i;
                (*len_ind_arr)++;
            }
        }
        else
        {
            if (cmp(&table[i], searching) == 0)
            {
                ind_arr[*len_ind_arr] = i;
                (*len_ind_arr)++;
            }
        }
    }
}

void file_write_country(FILE *f, const struct country_t *country)
{
    fprintf(f, "%s\n", country->name);
    fprintf(f, "%s\n", country->capital);
    fprintf(f, "%s\n", country->continent);
    if (country->visa)
        fprintf(f, "%d\n", 1);
    else 
        fprintf(f, "%d\n", 0);
    fprintf(f, "%d\n", country->time);
    fprintf(f, "%d\n", country->cost_min);
    if (country->type_tourism == EXCURSION_TOURISM)
    {
        fprintf(f, "%d\n", EXCURSION_TOURISM);
        fprintf(f, "%d\n", country->tourism.excursion_tourism.count_sights);
        fprintf(f, "%s\n", country->tourism.excursion_tourism.type_sights);
    }
    else if (country->type_tourism == BEACH_TOURISM)
    {
        fprintf(f, "%d\n", BEACH_TOURISM);
        fprintf(f, "%s\n", country->tourism.beach_tourism.season);
        fprintf(f, "%d\n", country->tourism.beach_tourism.air_tempr);
        fprintf(f, "%d\n", country->tourism.beach_tourism.water_tempr);
    }
    else 
    {
        fprintf(f, "%d\n", SPORT_TOURISM);
        fprintf(f, "%s\n", country->tourism.sport_type);
    }
    fprintf(f, "\n");
}

int file_write_table(char *filename, const struct country_t table[], const size_t len_table)
{
    FILE *f;
    f = fopen(filename, "w");
    if (f == NULL)
        return ERR_FILE_NOT_EXIST;
    
    for (size_t i = 0; i < len_table; i++)
    {
        file_write_country(f, &table[i]);
    }
    fclose(f);

    return OK;
}

int del_country(struct country_t table[], size_t *len_table, const int ind_searching)
{
    if (ind_searching < 0 || ind_searching >= (int) *len_table)
        return ERR_NO_COUNTRY_IN_TABLE;
    
    for (size_t i = ind_searching; i < *len_table - 1; i++)
    {
        assert(table[i + 1].ind - table[i].ind == 1);
        table[i] = table[i + 1];
        table[i].ind--;
    }
    (*len_table)--;

    return OK;
}

int cmp_country_name(const struct country_t *l, const struct country_t *r)
{
    return strcmp(l->name, r->name);
}

int cmp_country_capital(const struct country_t *l, const struct country_t *r)
{
    return strcmp(l->capital, r->capital);
}

int cmp_country_continent(const struct country_t *l, const struct country_t *r)
{
    return strcmp(l->continent, r->continent);
}

int cmp_country_visa(const struct country_t *l, const struct country_t *r)
{
    return (int) l->visa - (int) r->visa;
}

int cmp_country_time(const struct country_t *l, const struct country_t *r)
{
     return l->time - r->time;
}

int cmp_country_cost_min(const struct country_t *l, const struct country_t *r)
{
     return l->cost_min - r->cost_min;
}

int cmp_country_exrsn_trsm_count_sights(const struct country_t *l, const struct country_t *r)
{
    assert(l->type_tourism == EXCURSION_TOURISM && r->type_tourism == EXCURSION_TOURISM);
    return l->tourism.excursion_tourism.count_sights - r->tourism.excursion_tourism.count_sights;
}

int cmp_country_exrsn_trsm_type_sights(const struct country_t *l, const struct country_t *r)
{
    if (r->type_tourism != EXCURSION_TOURISM)
        printf("QWEEEEEEEE\n");
    assert(l->type_tourism == EXCURSION_TOURISM && r->type_tourism == EXCURSION_TOURISM);
    return strcmp(l->tourism.excursion_tourism.type_sights, r->tourism.excursion_tourism.type_sights);
}

int cmp_country_beach_trsm_season(const struct country_t *l, const struct country_t *r)
{
    assert(l->type_tourism == BEACH_TOURISM && r->type_tourism == BEACH_TOURISM);
    return strcmp(l->tourism.beach_tourism.season, r->tourism.beach_tourism.season);
}

int cmp_country_beach_trsm_air_tempr(const struct country_t *l, const struct country_t *r)
{
    assert(l->type_tourism == BEACH_TOURISM && r->type_tourism == BEACH_TOURISM);
    return l->tourism.beach_tourism.air_tempr - r->tourism.beach_tourism.air_tempr;
}

int cmp_country_beach_trsm_water_tempr(const struct country_t *l, const struct country_t *r)
{
    assert(l->type_tourism == BEACH_TOURISM && r->type_tourism == BEACH_TOURISM);
    return l->tourism.beach_tourism.water_tempr - r->tourism.beach_tourism.water_tempr;
}

int cmp_country_sport_trsm_sport_type(const struct country_t *l, const struct country_t *r)
{
    assert(l->type_tourism == SPORT_TOURISM && r->type_tourism == SPORT_TOURISM);
    return strcmp(l->tourism.sport_type, r->tourism.sport_type);
}











