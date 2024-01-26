#include <stdio.h>
#include "change_matrix.h"
#include "input_output.h"
#include "errors.h"

int main(void)
{
    int mtrx[N][M];
    size_t n, m;
    int rc;

    rc = input_matrix(mtrx, &n, &m);
    if (rc != OK)
        return rc;
    if (n != m)
        return ERR_SQUARE_MATRIX;

    change_matrix(mtrx, n);

    print_matrix(mtrx, n, m);

    return OK;
}
