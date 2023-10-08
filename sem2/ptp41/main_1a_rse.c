#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <sys/time.h>
#include <time.h>

#ifndef LEN_ARR
#error No LEN_ARR here
#endif

#define MAX_REPS 100


// вывод элементов массива
void print(const int a[], size_t a_size)
{
    printf("Массив: \n");
    for (size_t i = 0; i < a_size; i++)
        printf("%d ", a[i]);
    printf("\n");
}

// заполнение массива
void fill_arr_sorted(int *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        a[i] = i;
}

// заполнение массива
void fill_arr_unsorted(int *a, size_t n)
{
    srand(time(NULL));
    for (size_t i = 0; i < n; i++)
        a[i] = rand() % 1000;
}

// Возвращает индекс максимального элементы
size_t max_elem_ind(const int a[], size_t a_size)
{
    size_t max_el_ind = 0;
    for (int i = a_size - 1; i >= 0; i--)
        if (a[i] > a[max_el_ind])
            max_el_ind = i;
    return max_el_ind;
}

// Сортировка выбором
void selection_sort(int a[], size_t a_size)
{
    int tmp;
    size_t mn;
    for (size_t end = a_size - 1; end > 0; end--)
    {
        mn = max_elem_ind(a, end + 1);
        tmp = a[end];
        a[end] = a[mn];
        a[mn] = tmp;
    }
}

// вычисляет разность времени в микросекундах
unsigned long long calc_elapsed_time(const struct timeval *beg, const struct timeval *end)
{
    return ((unsigned long long)
        (end->tv_sec - beg->tv_sec) * 1000 +
                        (end->tv_usec - beg->tv_usec) / 1000);
}

void get_midtime_countrep_rse(int a[], long long unsigned *mid_out, int *count_rep_out, double *rse_out)
{
    struct timeval t_beg, t_end;
    long long unsigned data[MAX_REPS], sum = 0;
    double rse = 100, mid = -1, s2;
    int count_rep = 0;

    for (size_t i = 0; (rse >= 5.0 || i < 2) && i < MAX_REPS; i++)
    {
        gettimeofday(&t_beg, NULL);
        selection_sort(a, LEN_ARR);
        gettimeofday(&t_end, NULL);

        data[i] = calc_elapsed_time(&t_beg, &t_end);

        // rse
        s2 = 0.0;
        sum += data[i];
        mid = (double) sum / (i + 1);
        if (sum == 0)
            rse = 0.0;
        else
        {
            for (size_t j = 0; j <= i; j++)
                s2 += (data[i] - mid) * (data[i] - mid);
            s2 /= (double) i;
    //        printf("%f\n", s2);
    //        printf("%f %f\n", sqrt(s2), sqrt(i + 1));
            rse = ((sqrt(s2) / sqrt(i + 1)) / mid) * 100;
        }

        count_rep = i + 1;
    }

    *mid_out = (long long unsigned) mid;
    *count_rep_out = count_rep;
    *rse_out = rse;
}


int main(void)
{
    int a[LEN_ARR];
    long long unsigned mid_s, mid_us;
    int count_rep_s, count_rep_us;
    double rse_s, rse_us;

    FILE *f = NULL;
    char *filename = "./tabs/tab_O0_1a_s_rse.txt";

    fill_arr_sorted(a, LEN_ARR);
    get_midtime_countrep_rse(a, &mid_s, &count_rep_s, &rse_s);
    fill_arr_unsorted(a, LEN_ARR);
    get_midtime_countrep_rse(a, &mid_us, &count_rep_us, &rse_us);

    if (LEN_ARR == 10)
    {
        f = fopen(filename, "w");
        fprintf(f, "%s\n", "\tСлучайный массив\tУпорядоченный массив");
        fprintf(f, "%s\n", "Размер массива\tВремя мс\tКол-во повторов\tRSE %\tВремя мс\tКол-во повторов\tRSE %");
    }
    else
        f = fopen(filename, "a");

    if (f == NULL)
    {
        printf("ERROR 1\n");
        return 1;
    }

    fprintf(f, "%d \t %llu \t %d \t %.2f \t %llu \t %d \t %.2f \n",
            LEN_ARR, mid_s, count_rep_s, rse_s, mid_us, count_rep_us, rse_us);

    a[0] = a[1];
    a[1] = 1234;

    //printf("%llu\n", (long long unsigned) mid);

    return 0;
}




