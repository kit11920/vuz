#include <stdio.h>
#include <string.h>

#include "errs.h"
#include "input_output.h"
#include "array.h"


int main(int argc, char **argv)
{
    FILE *in_f, *out_f;
    int rc = OK;

    if (argc == 3 || (argc == 4 && strcmp(argv[3], "f") == 0))
    {
        in_f = fopen(argv[1], "r");
        if (in_f == NULL)
            return ERR_FILE_IN_NOT_EXIST;

        out_f = fopen(argv[2], "w");
        if (out_f == NULL)
        {
            fclose(in_f);
            return ERR_CANNOT_OPEN_FILE_OUT; // проблема good
        }

        size_t len_arr;
        rc = count_elems_in_arr(in_f, &len_arr);
        if (rc == OK && len_arr != 0)
        {
            // if (len_arr == 0)
            //     rc = ERR_FILE_IN_EMPTY;
                //return ERR_FILE_IN_EMPTY; // проблема

            int *arr = NULL;
            arr = malloc(len_arr * sizeof(int));

            if (arr != NULL)
            {
                rewind(in_f);
                rc = fill_arr(in_f, arr, arr + len_arr);

                // Фильтруем массив, в итоге arr будет указывать на новый массив
                if (rc == OK && argc == 4 && strcmp(argv[3], "f") == 0)
                {
                    // Запускаем функцию фильтра и создаем новый массив
                    int *pb_farr, *pe_farr;
                    rc = key(arr, arr + len_arr, &pb_farr, &pe_farr);
                    //

                    // указать arr теперь указывает на новый массив, а память со старым массивом освободилась
                    if (rc == OK)
                    {
                        free(arr);
                        arr = pb_farr;
                        len_arr = pe_farr - pb_farr;
                    }
                    //
                }
                //

                // Сортируем массив
                if (rc == OK)
                {
                    //output_arr(out_f, arr, arr + len_arr);
                    mysort(arr, len_arr, sizeof(int), cmp_int);
                    output_arr(out_f, arr, arr + len_arr);
                }
                //

                free(arr);
            }
            else
                rc = ERR_DYNAMIC_MEMORY;
        }
        if (len_arr == 0)
            rc = ERR_FILE_IN_EMPTY;
        fclose(in_f);
        fclose(out_f);
    }
    else
        rc = ERR_BAD_PARAM;

    return rc;
}
