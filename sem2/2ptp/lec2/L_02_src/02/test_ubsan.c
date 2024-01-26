#include <stdio.h>
#include <limits.h>

int main(void)
{
    int a, b = INT_MAX - 5;

    printf("Input a: ");
    if (scanf("%d", &a) == 1)
    {
        printf("%d + %d = %d\n", a, b, a + b);
    }
    else
    {
        printf("Input error\n");
    }

    return 0;
}

