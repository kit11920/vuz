#include <stdio.h>
#include <string.h>

#include "errs.h"
#include "film_array.h"


int main(int argc, char **argv)
{
    FILE *f;
    int rc = OK;

    if (argc == 3 || argc == 4)
    {
        struct film_t films[MAX_LEN_ARRAY];
        size_t len_farr;

        f = fopen(argv[1], "r");
        if (f != NULL)
        {
            if (strcmp(argv[2], TITLE) == 0 || 
                strcmp(argv[2], NAME) == 0 || strcmp(argv[2], YEAR) == 0)
            {
                if (strcmp(argv[2], TITLE) == 0)
                    rc = uni_farr_read_sorted(f, films, MAX_LEN_ARRAY, &len_farr, film_cmp_by_title);
                else if (strcmp(argv[2], NAME) == 0)
                    rc = uni_farr_read_sorted(f, films, MAX_LEN_ARRAY, &len_farr, film_cmp_by_name);
                else
                    rc = uni_farr_read_sorted(f, films, MAX_LEN_ARRAY, &len_farr, film_cmp_by_year);
                    
                if (rc == OK)
                {
                    if (argc == 3)
                        rc = farr_print(films, len_farr);
                    else
                    {
                        int index_x;
                        struct film_t tmp_film;

                        if (strcmp(argv[2], TITLE) == 0)
                        {
                            strcpy(tmp_film.title, argv[3]);
                            index_x = uni_find_film_by_key(films, len_farr, &tmp_film, film_cmp_by_title);
                        }
                        else if (strcmp(argv[2], NAME) == 0)
                        {
                            strcpy(tmp_film.name, argv[3]);
                            index_x = uni_find_film_by_key(films, len_farr, &tmp_film, film_cmp_by_name);
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

    // printf("params %d\n", argc);
    // printf("\n%s\n %s\n %s\n %s\n", argv[0], argv[1], argv[2], argv[3]);
    return rc;
}
