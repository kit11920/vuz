/*
Пермякова ИУ7-22Б
Лаб1 задача 2
Вариант 2
Принять с клавиатуры координаты xa, ya, xb, yb, xc, yc
треугольника abc на плоскости.
Найти и вывести на экран периметр Р треугольника.
*/

#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 1

int main(void)
{
    double xa, ya, xb, yb, xc, yc;
    printf("Введите координаты треугольника abc, xa, ya, xb, yb, xc, yc: ");
    scanf("%lf%lf%lf%lf%lf%lf", &xa, &ya, &xb, &yb, &xc, &yc);

    double a, b, c;
    a = sqrt(pow(xb - xc, 2) + pow(yb - yc, 2));
    b = sqrt(pow(xa - xc, 2) + pow(ya - yc, 2));
    c = sqrt(pow(xb - xa, 2) + pow(yb - ya, 2));

    double p;
    p = a + b + c;

    printf("Периметр треульника: %.6lf\n", p);
    return OK;
}
