#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "errs.h"
#include "input_output.h"

int count_elems_in_arr(FILE *f, size_t *len_arr)
{
    *len_arr = 0;
    int elem;

    while (fscanf(f, "%d", &elem) == 1)
        (*len_arr)++;

    if (!feof(f))
        return ERR_IO;

    return OK;
}


int fill_arr(FILE *f, int *const pbeg, int *const pend)
{
    assert(pend - pbeg != 0);

    for (int *pcur = pbeg; pcur < pend; pcur++)
        if (fscanf(f, "%d", pcur) != 1)
            return ERR_IO;
    
    return OK;
}


void output_arr(FILE *f, const int *const pbeg, const int *const pend)
{
    for (const int *pcur = pbeg; pcur < pend; pcur++)
        fprintf(f, "%d ", *pcur);
}
