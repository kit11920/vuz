#include <stddef.h>
#include <stdio.h>
#include <math.h>

#include "in_output.h"
#include "alloc_mtrx.h"
#include "errs.h"
#include "inits.h"


int read_mtrx(FILE *f, struct mtrx_t *mtrx)
{
    for (size_t i = 0; i < mtrx->rows; i++)
        for (size_t j = 0; j < mtrx->cols; j++)
            if (fscanf(f, "%lf", &mtrx->data[i][j]) != 1)
                return ERR_IO;
    return OK;
}


int create_mtrx(char *filename, struct mtrx_t *mtrx)
{
    int rc = OK;
    FILE *f;
    int rows, cols;

    f = fopen(filename, "r");
    if (f == NULL)
        return ERR_FILE;

    if (fscanf(f, "%d%d", &rows, &cols) != 2)
        rc = ERR_IO;
    if (rc == OK && (rows <= 0 || cols <= 0))
        rc = ERR_IO;

    if (rc == OK)
    {
        rc = alloc_mtrx_data(mtrx, (size_t) rows, (size_t) cols);
        if (rc == OK)
        {
            rc = read_mtrx(f, mtrx);
            if (rc != OK)
                free_mtrx(mtrx);    
        }
    }

    fclose(f);
    return rc;
}




int print_mtrx_coord_file(char *filename, struct mtrx_t *mtrx)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
        return ERR_FILE;
    print_mtrx_coord(f, mtrx);

    fclose(f);
    return OK;
}

size_t count_nonzero(struct mtrx_t *mtrx)
{
    size_t count = 0;
    for (size_t i = 0; i < mtrx->rows; i++)
        for (size_t j = 0; j < mtrx->cols; j++)
            if (fabs(mtrx->data[i][j]) >= EPS)
                count++;
    return count;
}

void print_mtrx_coord(FILE *f, struct mtrx_t *mtrx)
{
    size_t count = count_nonzero(mtrx);

    if (f == stdout)
        fprintf(f, "Matrix:\n");

    fprintf(f, "%zu %zu %zu\n", mtrx->rows, mtrx->cols, count);
    for (size_t i = 0; i < mtrx->rows; i++)
        for (size_t j = 0; j < mtrx->cols; j++)
            if (fabs(mtrx->data[i][j]) >= EPS)
                fprintf(f, "%zu %zu %lf\n", i + 1, j + 1, mtrx->data[i][j]);
    
    fprintf(f, "\n");
}

void print_mtrx_standart(struct mtrx_t *mtrx)
{
    printf("Matrix:\n");
    for (size_t i = 0; i < mtrx->rows; i++)
    {
        for (size_t j = 0; j < mtrx->cols; j++)
            printf(" %lf", mtrx->data[i][j]);
        printf("\n");
    }
}
