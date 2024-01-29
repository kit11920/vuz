#include <stdio.h>

#define OK 0

int main(void)
{
    int all_s;
    int h, m, s;
    const int sec_in_hour = 3600;
    const int sec_in_min = 60;

    printf("Введите время в секундах: ");
    scanf("%d", &all_s);

    h = all_s / sec_in_hour;
    all_s %= sec_in_hour;
    m = all_s / sec_in_min;
    all_s %= sec_in_min;
    s = all_s;

    printf("%d hours %d minuts %d seconds\n", h, m, s);
    return OK;
}
