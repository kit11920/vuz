#include <stdlib.h>
#include <assert.h>

#include "film.h"
#include "film_array.h"
#include "help_func_check.h"
#include "errs.h"

int film_cmp_films(const struct film_t *pl, const struct film_t *pr)
{
    if (film_cmp_by_title(pl, pr) == 0 && film_cmp_by_name(pl, pr) == 0 && film_cmp_by_year(pl, pr) == 0)
        return 0;
    else
        return 1;
}

// void farr_sort(struct film_t *farr, const size_t len_arr, uni_cmp_t cmp)
// {
//     for (size_t i = 0; i < len_arr - 1; i++)
//         for (size_t j = 0; j < len_arr - i - 1; j++)
//             if (cmp(&farr[j], &farr[j + 1]) > 0)
//             {
//                 struct film_t tmp;
//                 film_init_null(&tmp);
//                 film_copy(&tmp, &farr[j]);
//                 film_copy(&farr[j], &farr[j + 1]);
//                 film_copy(&farr[j + 1], &tmp);
//                 free_film(&tmp);
//             }
// }

int if_arr_sorted(struct film_t *farr, size_t len_arr, uni_cmp_t cmp)
{
    const int yes = 0, no = 1;

    for (size_t i = 0; i < len_arr - 1; i++)
        if (cmp(&farr[i], &farr[i + 1]) > 0)
            return no;
    return yes;
}

int create_arr_by_data(struct film_t **arr, char *titles[], char *names[], int years[], const size_t len_arr)
{
    int rc;

    *arr = calloc(len_arr, sizeof(struct film_t));
    if (*arr == NULL)
        return ERR_MEM;

    for (size_t i = 0; i < len_arr; i++)
    {
        rc = film_init_content(&(*arr)[i], titles[i], names[i], years[i]);
        if (rc != OK)
        {
            free_farr(*arr, len_arr);
            return rc;
        }
    }

    return OK;
}
