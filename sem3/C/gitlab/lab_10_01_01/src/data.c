#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_list.h"
#include "list.h"
#include "data.h"
#include "errs.h"


int input_str(FILE *f, char **str)
{
    int rc = OK;
    *str = NULL;
    size_t len = 0;
    ssize_t read = 0;

    if ((read = getline(str, &len, f)) == -1)
        rc = ERR_IO;
    else if (read != 0 && (*str)[read - 1] == '\n')
    {
        (*str)[read - 1] = 0;
        read--;
    }
    if (rc == OK && read == 0)
        rc = ERR_RANGE;

    if (rc != OK)
    {
        free(*str);
        *str = NULL;   
    }

    return rc;
}

// int input_country(FILE *f, country_t *country)
// {
//     int rc = OK;
//     int visa_int;

//     // Вводим название страны
//     if ((rc = input_str(f, &country->name)) != OK)
//         return rc;
//     //

//     // Вводим название столица
//     rc = input_str(f, &country->capital);
//     //

//     if (rc == OK)
//     {
//         // Вводим нужна ли виза
//         if (fscanf(f, "%d", &visa_int) != 1)
//             rc = ERR_IO;
//         else if (visa_int == 1)
//             country->visa = true;
//         else if (visa_int == 0)
//             country->visa = false;
//         else
//             rc = ERR_RANGE;
//         getc(f);
//         //

//         if (rc == OK)
//         {
//             // Вводим время полета до страны
//             if (fscanf(f, "%d", &country->time) != 1)
//                 rc = ERR_IO;
//             else if (country->time < 0)
//                 rc = ERR_RANGE;
//             //

//             // Вводим винимальную стоимость отдыха в стране
//             else if (fscanf(f, "%d", &country->cost_min) != 1)
//                 rc = ERR_IO;
//             else if (country->cost_min < 0)
//                 rc = ERR_RANGE;
//             //
//             getc(f);
//         }
//     }
//     getc(f);

//     if (rc != OK)
//     {
//         free(country->name);
//         country->name = NULL;

//         free(country->capital);
//         country->capital = NULL;
//     }

//     return rc;
// }

// int alloc_country(country_t **country)
// {
//     country_t *tmp = malloc(sizeof(country_t));

//     if (tmp == NULL)
//         return ERR_MEM;
//     *country = tmp;

//     return OK;
// }

int create_country(FILE *f, country_t **country_out)
{
    int rc = OK;
    int visa_int;
    *country_out = NULL;

    country_t *country = malloc(sizeof(country_t));
    if (country == NULL)
        return ERR_MEM;

    // Вводим название страны
    if ((rc = input_str(f, &country->name)) != OK)
    {
        free(country);
        return rc;
    }
    //

    // Вводим название столица
    rc = input_str(f, &country->capital);
    //

    if (rc == OK)
    {
        // Вводим нужна ли виза
        if (fscanf(f, "%d", &visa_int) != 1)
            rc = ERR_IO;
        else if (visa_int == 1)
            country->visa = true;
        else if (visa_int == 0)
            country->visa = false;
        else
            rc = ERR_RANGE;
        getc(f);
        //

        if (rc == OK)
        {
            // Вводим время полета до страны
            if (fscanf(f, "%d", &country->time) != 1)
                rc = ERR_IO;
            else if (country->time < 0)
                rc = ERR_RANGE;
            //

            // Вводим винимальную стоимость отдыха в стране
            else if (fscanf(f, "%d", &country->cost_min) != 1)
                rc = ERR_IO;
            else if (country->cost_min < 0)
                rc = ERR_RANGE;
            //
            getc(f);
        }
    }
    getc(f);

    if (rc != OK)
    {
        free(country->name);
        country->name = NULL;

        free(country->capital);
        country->capital = NULL;

        free(country);
    }
    else
        *country_out = country;

    return rc;
}

void print_country(FILE *f, void *vcountry)
{
    country_t *country = vcountry;
    fprintf(f, "%s\n", country->name);
    fprintf(f, "%s\n", country->capital);
    if (country->visa)
        fprintf(f, "%d\n", 1);
    else
        fprintf(f, "%d\n", 0);
    fprintf(f, "%d\n", country->time);
    fprintf(f, "%d\n", country->cost_min);
    fprintf(f, "\n");
}


void free_country(void *vcountry)
{
    country_t *country = vcountry;
    free(country->name);
    free(country->capital);
    free(country);
}

int find_by_country_name(char *name, node_t *head, node_t **node)
{
    int rc = OK;
    country_t search_country;

    search_country.name = strdup(name);
    if (search_country.name == NULL)
        rc = ERR_MEM;
    else
    {
        *node = find(head, &search_country, cmp_name);
        free(search_country.name);
    }
    
    return rc;
}

int cmp_name(const void *l, const void *r)
{
    // printf("cmp:  %p  %p\n", l, r);
    // const node_t *nl = l, *nr = r;
    const country_t *cl = l, *cr = r;
    return strcmp(cl->name, cr->name);
}

int read_file_list(char *filename, node_t **head)
{
    int rc = OK;
    FILE *f;
    country_t *tmp_country = NULL;
    node_t *tmp_node = NULL;
    *head = NULL;

    f = fopen(filename, "r");
    if (f == NULL)
        return ERR_FILE;
    
    while (rc == OK)
    {
        rc = create_country(f, &tmp_country);
        if (rc == OK)
        {
            tmp_node = create_node(tmp_country); 
            if (tmp_node == NULL)
                rc = ERR_MEM;
            else
                *head = add_tail_list(*head, tmp_node);
        }
    }
    
    if (feof(f))
        rc = OK;
    else
    {
        free_data_list(*head, free_country);
        free_list(*head);
    }

    fclose(f);
    return rc;
}
