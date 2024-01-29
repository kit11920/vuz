#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "film.h"
#include "errs.h"

void film_init_null(struct film_t *film)
{
    film->title = NULL;
    film->name = NULL;
    film->year = 0;
}

int init_str(char **dst, char *src)
{
    char *tmp = strdup(src);
    if (tmp == NULL)
        return ERR_MEM;
    free(*dst);
    *dst = tmp;

    return OK;
}

int film_init_content(struct film_t *film, char *title, char *name, int year)
{
    int rc = OK;

    rc = init_str(&film->title, title);
    if (rc != OK)
        return rc;
    
    rc = init_str(&film->name, name);
    if (rc != OK)
    {
        free(film->title);
        return rc;
    }
    film->year = year;

    return OK;
}

int film_copy(struct film_t *dst, struct film_t *src)
{
    return film_init_content(dst, src->title, src->name, src->year);
}

void free_film(struct film_t *film)
{
    free(film->title);
    film->title = NULL;
    free(film->name);
    film->name = NULL;
}

int input_str(FILE *f, char **str)
{
    int rc = OK;
    size_t len = 0;
    ssize_t read;

    if ((read = getline(str, &len, f)) == -1)
        rc = ERR_IO;
    
    if (rc == OK && read != 0 && (*str)[read - 1] == '\n')
    {
        (*str)[read - 1] = 0;
        read--;
    }
    if (read == 0)
    {
        // printf("read 0\n");
        rc = ERR_IO;
    }
    // printf("%s - %ld\n", *str, read);

    if (rc != OK)
        free(*str);

    return rc;
}

int film_read(FILE *f, struct film_t *pfilm)
{
    int rc = OK;
    char *title = NULL, *name = NULL;
    int year;
    // char tmp[2];

    // обработка ввода строки title
    rc = input_str(f, &title);
    if (rc != OK)
        return rc;
    //

    // обработка ввода строки name
    rc = input_str(f, &name);
    if (rc != OK)
    {
        free(title);
        return rc;
    }
    //

    //  ввод года
    if (fscanf(f, "%d\n", &year) != 1)
        rc = ERR_IO;
    if (rc == OK && year <= 0)
        rc = ERR_RANGE;
    //
    
    if (rc == OK)
    {
        // без переменнно tmp    def
        // считываем ненужный backspace после числа и после окончания структуры
        // fgets(tmp, sizeof(tmp), f);
        // getc(f);

        rc = film_init_content(pfilm, title, name, year);
    }

    free(title);
    free(name);
    return rc;
}


void film_print(const struct film_t *pfilm)
{
    puts(pfilm->title);
    puts(pfilm->name);
    printf("%d\n", pfilm->year);
}

int film_cmp_by_title(const struct film_t *pl, const struct film_t *pr)
{
    return strcmp(pl->title, pr->title);
}


int film_cmp_by_name(const struct film_t *pl, const struct film_t *pr)
{
    return strcmp(pl->name, pr->name);
}

int film_cmp_by_year(const struct film_t *pl, const struct film_t *pr)
{
    if (pl->year > pr->year)
        return 1;
    else if (pl->year == pr->year)
        return 0;
    else
        return -1;
}

