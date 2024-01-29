#include <stdio.h>
#include "get_array.h"
#include "input_output.h"
#include "errors.h"

int main(void)
{
    int matrix[N][M];
    size_t matrix_n, matrix_m;
    int res = input_matrix(matrix, &matrix_n, &matrix_m);
    if (res != OK)
        return res;

    int arr[N];
    get_array(matrix, matrix_n, matrix_m, arr);
    print_array(arr, matrix_m);

    return OK;
}
