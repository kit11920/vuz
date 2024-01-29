#include <stdio.h>
#include <math.h>

#define OK 0
#define ERR_IO 4
#define IN_TRIANGLE 0
#define BORDER_TRIANGLE 1
#define OUT_TRIANGLE 2

int is_triangle(double xa, double ya, double xb, double yb, double xc, double yc, const double eps)
{
    double k, b;

    // является ли треугольником, лежит ли на прямой y = kx+b
    k = (ya - yb) / (xa - xb);
    b = ya - xa * k;

    if (fabs(yc - (xc * k + b)) < eps || (fabs(xa - xb) < eps && fabs(xa - xc) < eps))
    {
        return ERR_IO;
    }
    else
        return  OK;
}

int where_point(double xa, double ya, double xb, double yb, double xc, double yc, double xp, double yp, const double eps)
{
    double cp_cb, bp_ba, ap_ac;

    cp_cb = (xp - xc) * (yb - yc) - (xb - xc) * (yp - yc);
    bp_ba = (xp - xb) * (ya - yb) - (xa - xb) * (yp - yb);
    ap_ac = (xp - xa) * (yc - ya) - (xc - xa) * (yp - ya);

    if ((cp_cb > 0 && bp_ba > 0 && ap_ac > 0) || (cp_cb < 0 && bp_ba < 0 && ap_ac < 0))
        return IN_TRIANGLE;
    else if (fabs(cp_cb) < eps || fabs(bp_ba) < eps || fabs(ap_ac) < eps)
        return BORDER_TRIANGLE;
    else
        return OUT_TRIANGLE;
}

int main(void)
{
    const double eps = 0.0000001;
    double xa, ya, xb, yb, xc, yc, xp, yp;

    printf("Введите координаты треугольника abc (xa, ya, xb, yb, xc, yc) и точки p (xp, yp): ");
    if (scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &xa, &ya, &xb, &yb, &xc, &yc, &xp, &yp) != 8)
    {
        printf("ERR_IO\n");
        return ERR_IO;
    }

    if (is_triangle(xa, ya, xb, yb, xc, yc, eps) != OK)
    {
        printf("Not triangle\n");
        return ERR_IO;
    }

    int res = where_point(xa, ya, xb, yb, xc, yc, xp, yp, eps);
    printf("%d\n", res);

    return OK;
}
