#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "film_array.h"
#include "film.h"
#include "errs.h"


int count_elems_farr(FILE *f, size_t *count)
{
    struct film_t elem;
    film_init_null(&elem);
    *count = 0;
    int rc = OK;

    while (rc == OK)
    {
        rc = film_read(f, &elem);
        if (rc == OK)
        {
            (*count)++;
            free_film(&elem);
        }
    }

    if (fgetc(f) == EOF)
        rc = OK;
    // if (feof(f))
    //     rc = OK;
    
    return rc;
}

/*
Поверхностное копирование делать нельзя так как в функции uni_farr_read_sorted
считываются данные во временную переменную структуру и уже потом
данные из этой временной переменной копируются в массив, а потом временная переменная освобождается
Если сделать поверхностное копирование, то данные внутри массива освободяться вместе со временной переменной
*/
void uni_farr_insert_el(struct film_t *farr, size_t ind, struct film_t *film, uni_cmp_t cmp)
{
    size_t i = ind;
    
    while (i > 0 && cmp(&farr[i - 1], film) > 0)
    {
        film_copy(&farr[i], &farr[i - 1]);
        // farr[i] = farr[i - 1];
        i--;
    }
    film_copy(&farr[i], film);
    // farr[i] = *film;
}

void free_farr(struct film_t *farr, size_t len_arr)
{
    for (size_t i = 0; i < len_arr; i++)
        free_film(&farr[i]);
    free(farr);
}

int uni_farr_read_sorted(FILE *f, struct film_t **farr, size_t *len_arr, uni_cmp_t cmp)
{
    struct film_t film;
    film_init_null(&film);
    int rc = OK;

    // Считаем кол-во элементов в массиве
    rc = count_elems_farr(f, len_arr);
    if (rc != OK)
        return rc;
    if (*len_arr == 0)
        return ERR_IO;
    rewind(f);
    //

    // Выделяем память под массив структур
    *farr = calloc(*len_arr, sizeof(struct film_t));
    if (*farr == NULL)
        return ERR_MEM;
    //

    // Зполняем массив структур
    for (size_t i = 0; i < *len_arr; i++)
    {
        rc = film_read(f, &film);
        if (rc != OK)
        {
            free_farr(*farr, *len_arr);
            return rc;
        }
        
        uni_farr_insert_el(*farr, i, &film, cmp);

        free_film(&film);
    }

    return rc;
}

void farr_print(const struct film_t *pfilms, const size_t len_arr)
{
    for (size_t i = 0; i < len_arr; i++)
        film_print(&pfilms[i]);
}

int uni_find_film_by_key(const struct film_t *pfilms, const size_t len_arr, struct film_t *film, uni_cmp_t cmp)
{
    int r, l, m;
    l = -1;
    r = len_arr;


    while (r - l > 1)
    {
        m = (r + l) / 2;

        if (cmp(&pfilms[m], film) < 0)
            l = m;
        else
            r = m;
    }

    if (r == (int) len_arr || cmp(&pfilms[r], film) != 0)
        return -1;
    else
        return r;   
}

