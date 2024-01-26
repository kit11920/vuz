#include <stdio.h>
#include "change_matrix.h"
#include "input_output.h"
#include "errors.h"

int main(void)
{
    int mtrx[N][M];
    size_t n, m;
    int rc;
    if ((rc = input_mtrx_nm(&n, &m)) != OK)
        return rc;

    input_matrix(mtrx, n, m);
    print_matrix(mtrx, n, m);

    return OK;
}
