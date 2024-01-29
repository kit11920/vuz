#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define ERR_ARITHM 3

double calc_s(double x, double eps)
{
    double s, sn;
    int m = 1;  // индекс степени в элементе
    sn = x;
    s = 0;
    while (fabs(sn) >= eps)
    {
        s += sn;
        sn *= x * x * m * m / ((m + 1) * (m + 2));
        //printf("%lf\n", sn);
        m += 2;
    }
    return s;
}

int main(void)
{
    double x, eps;
    const double eps2 = 0.000001;

    printf("Введите значения x, eps: ");
    if (scanf("%lf%lf", &x, &eps) != 2)
    {
        printf("ERR_IO\n");
        return ERR_IO;
    }

    if (!(fabs(x) <= 1 && 0 < eps && eps <= 1))
    {
        printf("Need |x| <= 1 and 0 < eps <= 1\n");
        return ERR_RANGE;
    }

    if (fabs(x) < eps2)
    {
        printf("Div zero\n");
        return ERR_ARITHM;
    }


    double f, s, absolute_er, relative_er;

    f = asin(x);
    s = calc_s(x, eps);
    absolute_er = fabs(f - s);
    relative_er = fabs(f - s) / fabs(f);

    printf("Приближенное значение s = %.6lf\n", s);
    printf("Точное значение f %.6lf\n", f);
    printf("Абсолютная погрешность = %.6f\n", absolute_er);
    printf("Отностительная погрешность = %.6f\n", relative_er);

    return OK;
}
