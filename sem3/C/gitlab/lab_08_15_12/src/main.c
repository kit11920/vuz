#include "stdio.h"
#include "stddef.h"
#include "string.h"

#include "inits.h"
#include "errs.h"
#include "in_output.h"
#include "alloc_mtrx.h"
#include "operations.h"



int main(int argc, char **argv)
{
    int rc = OK;
    struct mtrx_t mtrx1, mtrx_res;

    if (argc == 5 && (strcmp(argv[1], "a") == 0 || strcmp(argv[1], "m") == 0))
    {
        struct mtrx_t mtrx2;

        rc = create_mtrx(argv[2], &mtrx1);
        if (rc != OK)
            return rc;
        rc = create_mtrx(argv[3], &mtrx2);
        if (rc != OK)
        {
            free_mtrx(&mtrx1);
            return rc;
        }

        if (strcmp(argv[1], "a") == 0)
        {
            rc = addition(&mtrx1, &mtrx2, &mtrx_res);
            if (rc == OK)
            {
                rc = print_mtrx_coord_file(argv[4], &mtrx_res);
                // print_mtrx_standart(&mtrx_res);
                // print_mtrx_coord(stdout, &mtrx_res);
                free_mtrx(&mtrx_res);
            }
        }
        else if (strcmp(argv[1], "m") == 0)
        {
            rc = multiplication(&mtrx1, &mtrx2, &mtrx_res);
            if (rc == OK)
            {
                rc = print_mtrx_coord_file(argv[4], &mtrx_res);
                // print_mtrx_standart(&mtrx_res);
                // print_mtrx_coord(stdout, &mtrx_res);
                free_mtrx(&mtrx_res);
            }
        }

        free_mtrx(&mtrx1);
        free_mtrx(&mtrx2);
    }
    else if (argc == 4 && strcmp(argv[1], "o") == 0)
    {
        rc = create_mtrx(argv[2], &mtrx1);
        if (rc != OK)
            return rc;

        rc = invert(&mtrx1, &mtrx_res);
        if (rc == OK)
        {
            rc = print_mtrx_coord_file(argv[3], &mtrx_res);
            // print_mtrx_standart(&mtrx_res);
            // print_mtrx_coord(stdout, &mtrx_res);
            free_mtrx(&mtrx_res);
        }

        free_mtrx(&mtrx1);
    }
    else
        return ERR_ARGS;

    return rc;
}







