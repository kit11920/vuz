#include <stdio.h>
#include "sort_matrix.h"
#include "input_output.h"
#include "errors.h"

int main(void)
{
    int mtrx[N][M];
    size_t n, m;
    int rc;
    if ((rc = input_matrix(mtrx, &n, &m)) != OK)
        return rc;

    sort_matrix(mtrx, n, m);

    print_matrix(mtrx, n, m);

    return OK;
}
