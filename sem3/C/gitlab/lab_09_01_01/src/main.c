#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errs.h"
#include "film_array.h"


int main(int argc, char **argv)
{
    FILE *f;
    int rc = OK;

    if (argc == 3 || argc == 4)
    {
        struct film_t *films;
        size_t len_farr;

        f = fopen(argv[1], "r");
        if (f != NULL)
        {
            if (strcmp(argv[2], TITLE) == 0 || 
                strcmp(argv[2], NAME) == 0 || strcmp(argv[2], YEAR) == 0)
            {
                if (strcmp(argv[2], TITLE) == 0)
                    rc = uni_farr_read_sorted(f, &films, &len_farr, film_cmp_by_title);
                else if (strcmp(argv[2], NAME) == 0)
                    rc = uni_farr_read_sorted(f, &films, &len_farr, film_cmp_by_name);
                else
                    rc = uni_farr_read_sorted(f, &films, &len_farr, film_cmp_by_year);
                    
                if (rc == OK)
                {
                    if (argc == 3)
                        farr_print(films, len_farr);
                    else
                    {
                        int index_x;
                        struct film_t tmp_film;
                        film_init_null(&tmp_film);

                        if (strcmp(argv[2], TITLE) == 0)
                        {
                            init_str(&tmp_film.title, argv[3]);
                            index_x = uni_find_film_by_key(films, len_farr, &tmp_film, film_cmp_by_title);
                            free(tmp_film.title);
                        }
                        else if (strcmp(argv[2], NAME) == 0)
                        {
                            init_str(&tmp_film.name, argv[3]);
                            index_x = uni_find_film_by_key(films, len_farr, &tmp_film, film_cmp_by_name);
                            free(tmp_film.name);
                        }
                        else
                        {
                            if (sscanf(argv[3], "%d", &(tmp_film.year)) == 1)
                                index_x = uni_find_film_by_key(films, len_farr, &tmp_film, film_cmp_by_year);
                            else
                                rc = ERR_BAD_PARAM;
                        }

                        if (rc == OK)
                        {
                            if (index_x == -1)
                                printf("Not found\n");
                            else
                                film_print(&films[index_x]);
                        }
                    }

                    free_farr(films, len_farr);
                }
            }
            else
                rc = ERR_FIELD_NOT_EXIST;
            fclose(f);
        }
        else
            rc = ERR_FILE_NOT_EXIST;
    }
    else
        rc = ERR_BAD_PARAM;

    return rc;
}
