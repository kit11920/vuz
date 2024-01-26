#include <stdio.h>
#include "find_num.h"
#include "input_output.h"
#include "errors.h"

int main(void)
{
    int mtrx[N][N];
    int rc;
    size_t n, m;
    if ((rc = input_matrix(mtrx, &n, &m)) != OK)
        return rc;
    if (n != m)
        return ERR_SQUARE_MATRIX;

    int max_num;
    if ((rc = find_max_num_end_5(mtrx, n, m, &max_num)) != OK)
        return rc;

    printf("%d", max_num);

    return OK;
}
