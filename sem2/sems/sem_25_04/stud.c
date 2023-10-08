#include <stdio.h>
#include <string.h>
#include "array.h"
#include "stud.h"

/**
@brief Проверяет что оценки в массиве допустимы по значению
@param a[] - массив оценок
@param a_n - количество оценок
@return код ошибки
*/
int check_marks(const int a[], size_t a_n)
{
    for (size_t i = 0; i < a_n; i++)
        if (a[i] <= 0 || a[i] > 5)
            return ERR_RANGE;
    return OK;
}


int stud_read(struct student_t *pstud)
{
    char buf[NAME_LEN + 2]; // массив чуть больше чем нужно
    size_t len;
    int marks[MARKS_N];
    char tmp[2];
    int rc;

    fgets(tmp, sizeof(tmp), stdin);
    printf("Имя: ");
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return ERR_IO;


    len = strlen(buf);
    if (len && buf[len - 1] == '\n')
    {
        buf[len - 1] = '\0';
        len--;
    }

    if (!len || len > NAME_LEN)
        return ERR_RANGE;
    
    printf("Оценки: ");
    rc = arr_read(marks, MARKS_N);
    if (rc != OK)
        return rc;

    rc = check_marks(marks, MARKS_N);
    if (rc != OK)
        return rc;
    
    // вычитывает \n после введенной строки
    //fgets(tmp, sizeof(tmp), stdin);

    strcpy (pstud->name, buf);
    memcpy(pstud->marks, marks, sizeof(marks));

    return OK;
}


void stud_print(const struct student_t stud)
{
    printf("%s: ", stud.name);
    arr_print(stud.marks, COUNT_MARKS);
}



int stud_cmp_by_marks(const struct student_t lstud, const struct student_t rstud)
{
    double lavg, ravg;
    lavg = arr_calc_avg(lstud.marks, COUNT_MARKS);
    ravg = arr_calc_avg(rstud.marks, COUNT_MARKS);

    if (lavg < ravg)
        return -1;
    else if (lavg > ravg)
        return 1;
    else
        return 0;
}


int stud_cmp_by_name(const struct student_t lstud, const struct student_t rstud)
{
    int res = strncmp(lstud.name, rstud.name, NAME_LEN);

    if (res < 0)
        return -1;
    else if (res > 0)
        return 1;

    return res;
}
























