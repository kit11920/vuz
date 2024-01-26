#include <stdio.h>

int main(void)
{
    int rc = 0;
    int a[5], index;
    int b;

    printf("Input index: ");
    if (scanf("%d", &index) == 1)
    {
        printf("a[%d] = %d\n", index, a[index]);

        b = a[index];

        printf("b = %d\n", b);

        if (b > 0)
            printf("b is positive\n");
        else if (b < 0)
            printf("b is negative\n");
        else
            printf("b is zero\n");
    }
    else
    {
        rc = 1;
    }

    return rc;
}

