#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1

int gx(double *g_link)
{
    double x, g;
    g = *g_link;
    printf("Вводите последовательность неотрицательных элементов, конец - отрицательный элемент: ");
    if (scanf("%lf", &x) != 1)
    {
        //printf("ERR_IO\n");
        return ERR_IO;
    }
    if (x < 0)
    {
        //printf("Empty array\n");
        return ERR_IO;
    }

    int n = 0;
    while (x >= 0)
    {
        n++;
        g += sqrt(n + x);

        if (scanf("%lf", &x) != 1)
        {
            //printf("ERR_IO\n");
            return ERR_IO;
        }
    }
    g = g / n;
    *g_link = g;
    return OK;
}


int main(void)
{
    double g = 0;
    if (gx(&g) == OK)
    {
        printf("g(x) = %lf\n", g);
        return OK;
    }
    else
    {
        printf("error\n");
        return ERR_IO;
    }
}
