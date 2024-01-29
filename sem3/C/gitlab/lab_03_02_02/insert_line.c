#include <stdio.h>
#include <stdbool.h>
#include "input_output.h"
#include "errors.h"

bool if_odd_sum(int num)
{
    if (num == 0)
        return false;
    if (num < 0)
        num *= -1;

    int sum = 0;
    while (num != 0)
    {
        sum += num % 10;
        num /= 10;
    }

    return sum % 2 != 0;
}


bool if_2elem_with_odd_sum(const int a[], size_t a_size)
{
    int count_elem = 0;
    for (size_t i = 0; i < a_size; i++)
        if (if_odd_sum(a[i]))
            count_elem++;

    return count_elem >= 2;
}


void assigning_arr_to_arr(int a[], const int b[], size_t n)
{
    for (size_t i = 0; i < n; i++)
        a[i] = b[i];
}


void insert_one_line(int a[][M], size_t *a_n, size_t a_m, size_t ind, const int inserting_line[])
{
    for (size_t i = *a_n; i > ind; i --)
    {
        assigning_arr_to_arr(a[i], a[i - 1], a_m);
    }
    assigning_arr_to_arr(a[ind], inserting_line, a_m);
    (*a_n)++;
}


int insert_lines(int a[][M], size_t *a_n, size_t a_m)
{
    int count_inserted_lines = 0;
    int inserting_line[M] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    //int tmp[M];

    size_t i = 0;
    while (i < *a_n)
    {
        if (if_2elem_with_odd_sum(a[i], a_m))
        {
            count_inserted_lines++;
            /*
            if (*a_n + count_inserted_lines > N)
                return ERR_RANGE;
            */
            insert_one_line(a, a_n, a_m, i, inserting_line);
            i++;
        }
        i++;
    }
    return OK;
}









