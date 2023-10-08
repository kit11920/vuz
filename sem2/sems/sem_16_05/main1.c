//Вычисление относительной стандартной ошибки

#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_NO_EL 2

// расчет среднего
int calc_avg(FILE *f, double *avg, size_t *n)
{
    double el, sum = 0;

    while (fscanf(f, "%lf", &el) == 1)
    {
        sum += el;
        (*n)++;
    }

    // т к в тестирующей стистеме функция считывает сколько может и
    // если считает не весь файл жто не ошибка
//    if (!feof(f))
//        return ERR_IO;

    if ((*n) == 0)
        return ERR_NO_EL;

    (*avg) = sum / (*n);

    return OK;
}

// расчет дисперсии
int calc_s_sq(FILE *f, double avg, size_t n, double *s_sq)
{
    double el, sum_sq = 0;
    int cur_n = 0;

    if (n == 0 || n - 1 == 0)
        return ERR_NO_EL;


    while (fscanf(f, "%lf", &el) == 1)
    {
        sum_sq += (el - avg) * (el - avg);
        cur_n++;
    }

    if (cur_n != n)
        return ERR_IO;

    *s_sq = sum_sq / (n - 1);

    return OK;
}


int main(int argc, char **argv)
{
    FILE *f;

    if (argc != 2)
    {
        fprintf(stderr, "app.exe file_name\n");
        return ERR_IO;
    }

    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Файла не существует\n");
        return ERR_IO;
    }
    // ТОЛЬКО ОДНА ТОЧКА ВЫХОДА

    int rc = OK;
    double avg, s_sq;
    int n;

    rc = calc_avg(f, &avg, &n);
    if (rc == OK)
        // каждый ра делаем влоденность
        // не забыть перенести указатель файла в начало

}
























