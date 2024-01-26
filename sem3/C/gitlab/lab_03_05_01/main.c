#include <stdio.h>
#include "change_matrix.h"
#include "input_output.h"
#include "errors.h"

int main(void)
{
    int mtrx[N][M];
    size_t n, m;
    int rc;
    if ((rc = input_matrix(mtrx, &n, &m)) != OK)
        return rc;

    if ((rc = change_mtrx(mtrx, n, m)) != OK)
        return rc;

    print_matrix(mtrx, n, m);
    return OK;
}
