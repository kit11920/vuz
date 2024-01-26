#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "film.h"
#include "errs.h"


int input_str(FILE *f, char *str, size_t size_str, int max_len_str)
{
    int str_len = 0;

    if (!fgets(str, size_str, f))
        return ERR_IO;

    str_len = strlen(str);
    if (str_len && str[str_len - 1] == '\n')
    {
        str[str_len - 1] = 0;
        str_len--;
    }
    if (!str_len || str_len > max_len_str)
        return ERR_IO;
    
    return OK;
}


int film_read(FILE *f, struct film_t *pfilm)
{
    char title[TITLE_MAX_LEN + 2];
    char name[NAME_MAX_LEN + 2];
    char tmp[2];
    int year;
    int rc;

    // обработка ввода строки title
    rc = input_str(f, title, sizeof(title), TITLE_MAX_LEN);
    if (rc != OK)
        return rc;
    //

    // обработка ввода строки name
    rc = input_str(f, name, sizeof(name), NAME_MAX_LEN);
    if (rc != OK)
        return rc;
    //

    //  ввод года
    if (fscanf(f, "%d", &year) != 1)
        return ERR_IO;
    if (year <= 0)
        return ERR_RANGE;
    //

    // считываем ненужный backspace после числа и после окончания структуры
    fgets(tmp, sizeof(tmp), f);
    //

    // переносим считанные данные в структуру
    strcpy(pfilm->title, title);
    strcpy(pfilm->name, name);
    pfilm->year = year;
    // 

    return OK;
}


int film_print(const struct film_t *pfilm)
{
    puts(pfilm->title);
    puts(pfilm->name);
    printf("%d\n", pfilm->year);
    return OK;
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

// int film_cmp_by_param(const char param_sort[], const struct film_t *pl, const struct film_t *pr)
// {
//     assert(strcmp(param_sort, TITLE) == 0 || strcmp(param_sort, NAME) == 0 || strcmp(param_sort, YEAR) == 0);
//     if (strcmp(param_sort, TITLE) == 0)
//         return film_cmp_by_title(pl, pr);
//     else if (strcmp(param_sort, NAME) == 0)
//         return film_cmp_by_name(pl, pr);
//     else
//         return film_cmp_by_year(pl, pr);
// }
