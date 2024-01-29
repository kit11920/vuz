#include <stdio.h>
#include <string.h>

#include "film_array.h"
#include "film.h"
#include "errs.h"



int uni_farr_isert_el(struct film_t *pfilms, const size_t max_len_arr, size_t *len_arr_now, struct film_t *film, uni_cmp_t cmp)
{
    size_t i = *len_arr_now;
    (*len_arr_now)++;
    if (*len_arr_now <= max_len_arr)
    {
        while (i > 0 && cmp(&pfilms[i - 1], film) > 0)
        {
            pfilms[i] = pfilms[i - 1];
            i--;
        }
        pfilms[i] = *film;
    }
    else
        return ERR_OVERFLOW;
    
    return OK;
}


int uni_farr_read_sorted(FILE *f, struct film_t *pfilms, const size_t max_len_arr, size_t *plen_arr, uni_cmp_t cmp)
{
    struct film_t film;
    size_t len_arr_now = 0; // текущее количество элементов в массиве
    int rc = OK;

    while (rc == OK)
    {
        rc = film_read(f, &film);
        if (rc == OK)
            rc = uni_farr_isert_el(pfilms, max_len_arr, &len_arr_now, &film, cmp);
    }
    *plen_arr = len_arr_now;

    // допустимо что файл закончился пустой строкой
    char tmp[2];
    if (fgets(tmp, sizeof(tmp), f))
        if (tmp[0] != '\n')
            rc = ERR_OVERFLOW;
    //

    // если файл закончился 
    if (feof(f))
        rc = OK;
    //

    if (len_arr_now == 0)
        rc = ERR_IO;

    return rc;
}


// int farr_input_el(struct film_t *pfilms, const size_t max_len_arr, size_t *len_arr_now, struct film_t *film, const char *param_sort)
// {
//     size_t i = *len_arr_now;
//     (*len_arr_now)++;
//     if (*len_arr_now <= max_len_arr)
//     {
//         while (i > 0 && film_cmp_by_param(param_sort, &pfilms[i - 1], film) > 0)
//         {
//             pfilms[i] = pfilms[i - 1];
//             i--;
//         }
//         pfilms[i] = *film;
//     }
//     else
//         return ERR_OVERFLOW;
    
//     return OK;
// }


// int farr_read_sorted(FILE *f, struct film_t *pfilms, const size_t max_len_arr, size_t *plen_arr, const char *param_sort)
// {
//     struct film_t film;
//     size_t len_arr_now = 0; // текущее количество элементов в массиве
//     int rc = OK;

//     while (rc == OK)
//     {
//         rc = film_read(f, &film);
//         if (rc == OK)
//             rc = farr_input_el(pfilms, max_len_arr, &len_arr_now, &film, param_sort);
//     }
//     *plen_arr = len_arr_now;

//     // допустимо что файл закончился пустой строкой
//     char tmp[2];
//     if (fgets(tmp, sizeof(tmp), f))
//         if (tmp[0] != '\n')
//             rc = ERR_OVERFLOW;
//     //

//     // если файл закончился 
//     if (feof(f))
//         rc = OK;
//     //

//     if (len_arr_now == 0)
//         rc = ERR_IO;

//     return rc;
// }

int farr_print(const struct film_t *pfilms, const size_t len_arr)
{
    int rc = OK;
    for (size_t i = 0; i < len_arr; i++)
    {
        rc = film_print(&pfilms[i]);
        if (rc != OK)
            return rc;
    }
    return rc;
}


// int find_film_by_key_title(const struct film_t *pfilms, const size_t len_arr, const char *key)
// {
//     int r, l, m;
//     l = -1;
//     r = len_arr;

//     while (r - l > 1)
//     {
//         m = (r + l) / 2;
//         if (strcmp(pfilms[m].title, key) < 0)
//             l = m;
//         else
//             r = m;
//     }

//     if (r == (int) len_arr || strcmp(pfilms[r].title, key) != 0)
//         return -1;
//     else
//         return r;
// }

// int find_film_by_key_name(const struct film_t *pfilms, const size_t len_arr, const char *key)
// {
//     int r, l, m;
//     l = -1;
//     r = len_arr;

//     while (r - l > 1)
//     {
//         m = (r + l) / 2;
//         if (strcmp(pfilms[m].name, key) < 0)
//             l = m;
//         else
//             r = m;
//     }
//     // printf("%d %zu\n", r, len_arr);
//     // printf("%s\n", pfilms[m].name);
//     if (r == (int) len_arr || strcmp(pfilms[r].name, key) != 0)
//         return -1;
//     else
//         return r;
// }

// int find_film_by_key_year(const struct film_t *pfilms, const size_t len_arr, const int key)
// {
//     int r, l, m;
//     l = -1;
//     r = len_arr;

//     while (r - l > 1)
//     {
//         m = (r + l) / 2;
//         if (pfilms[m].year < key)
//             l = m;
//         else
//             r = m;
//     }

//     if (r == (int) len_arr || pfilms[r].year != key)
//         return -1;
//     else
//         return r;
// }


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
