#include <stdio.h>
#include <stdbool.h>

#include "stud_array.h"



int sa_read(struct student_t studs[], size_t *studs_n)
{
    if (scanf("%zu", studs_n) != 1)
        return ERR_IO;

    if (*studs_n > STUDS_MAX)
        return ERR_RANGE;

    int rc;
    for (size_t i = 0; i < *studs_n; i++)
    {
        rc = stud_read(&studs[i]);
        if (rc != OK)
            return rc;
    }

    return OK;
}


void sa_print(const struct student_t studs[], size_t studs_n)
{
    for (size_t i = 0; i < studs_n; i++)
        stud_print(studs[i]);
}


void sa_sort(struct student_t studs[], size_t studs_n)
{
    struct student_t tmp;
    bool swapped = true;

    while (swapped)
    {
        swapped = false;
        for (size_t i = 0; i < studs_n - 1; i++)
        {
            if ((stud_cmp_by_marks(studs[i], studs[i + 1]) > 0 && SORTING_MARKS) ||
                    (stud_cmp_by_name(studs[i], studs[i + 1]) > 0 && !SORTING_MARKS))
            {
                tmp = studs[i];
                studs[i] = studs[i + 1];
                studs[i + 1] = tmp;

                swapped = true;
            }
        }
    }
}

