
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
// uint32_t какие для него спецефикаторы отдельный заголовочный файл
#include <limits.h>
// define CHAR_BIT колво бит в байте
// size_of(uint32_t) * CHAR_BIT

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

// выводит биты числа, его представление в 2 с/с
void bin_print(uint32_t u)
{
    size_t nbits = sizeof(u) * CHAR_BIT;
    uint32_t mask = 1ul << (nbits - 1);

    for (size_t i = 0; i < nbits; i++)
    {
        if (u & mask)
            printf("1");
        else
            printf("0");
        mask >>= 1;
    }
    printf("\n");
}

//побайтовый сдвиг
uint32_t shiftn(uint32_t a, int n)
{
    size_t nbits = sizeof(a) * CHAR_BIT;
    uint32_t mask = 0, left_bit;

    for (int i = 0; i < n; i++)
    {
        mask = 1ul << (nbits - 1);
        if (a & mask)
            left_bit = 1;
        else
            left_bit = 0;

        a = a << 1;
        a = a | left_bit;
    }

    return a;
}

int main(void)
{
    uint32_t a;
    int n;

    printf("Введите беззнаковое целое число длиной 4байт a и целое число n: ");
    if (scanf("%" SCNu32 "%d", &a, &n) != 2)
    {
        printf("Error: ERR_IO\n");
        return ERR_IO;
    }
    // printf("%" PRIu32 "\n", b);
    if (n < 0)
    {
        printf("Error: negative n\n");
        return ERR_RANGE;
    }

    n = n % (sizeof(a) * CHAR_BIT);
    a = shiftn(a, n);
    //printf("%" PRIu32 "\n", a);

    printf("Result: ");
    bin_print(a);
    return OK;
}
