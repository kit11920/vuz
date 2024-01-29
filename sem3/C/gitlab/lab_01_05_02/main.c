#include <stdio.h>
#include <limits.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

// Возвращает код ошибки
int fib(int *fibn, int n)
{
    int last = 0;
    int fib = 1;

    if (n == 0)
        *fibn = 0;
    else if (n == 1)
        *fibn = 1;
    else
    {
        int n_now = 2;
        int save;

        while (n_now <= n)
        {
            save = fib;

            if (INT_MAX - fib < last)
            {
                // printf("Overflow\n");
                return ERR_RANGE;
            }

            fib += last;

            last = save;
            n_now++;
        }
        *fibn = fib;
    }
    return OK;
}


int main(void)
{
    int n;

    printf("Введите число n: ");
    if (scanf("%d", &n) != 1)
    {
        printf("IO error\n");
        return ERR_IO;
    }

    if (n < 0)
    {
        printf("Negative n\n");
        return ERR_RANGE;
    }

    int fibn = -1;
    if (fib(&fibn, n) != OK)
    {
        printf("Overflow\n");
        return ERR_RANGE;
    }
    else
    {
        printf("%d\n", fibn);
        return OK;
    }
}
