#include <stdio.h>
#include "change_matrix.h"
#include "errors.h"



void input_matrix(int mtrx[][M], size_t n, size_t m)
{
    int elem = 1;
    int direction = 1;

    for (int j = m - 1; j >= 0; j--)
    {
        if (direction == 1)
            for (int i = n - 1; i >= 0; i--)
            {
                mtrx[i][j] = elem;
                elem++;
            }
        else
            for (size_t i = 0; i < n; i++)
            {
                mtrx[i][j] = elem;
                elem++;
            }
        direction *= -1;
    }
}

































