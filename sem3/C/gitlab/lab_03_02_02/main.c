#include <stdio.h>
#include "insert_line.h"
#include "input_output.h"
#include "errors.h"


int main(void)
{
    int a[2 * N][M];
    size_t a_n, a_m;
    int rc;
    if ((rc = input_matrix(a, &a_n, &a_m)) != OK)
        return rc;

    if ((rc = insert_lines(a, &a_n, a_m)) != OK)
        return rc;

    print_matrix(a, a_n, a_m);
    return OK;
}


