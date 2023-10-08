/*
ВАЖНАЯ ЗАДАЧА ДЛЯ РК!!!
Информация о студенте представлена именем (длиной не более 15 символов)
и оценками по 4 экзаменам
- Необходимо реализовать ввод и хранение инфомации о студентах
(не более 15 студентов)
- Вывод инфомации о студентах
- И сортировку информации о студентах по средней оценке
*/

#include <stdio.h>

#include "stud_array.h"

int main(void)
{
    struct student_t studs[STUDS_MAX];
    size_t studs_n;
    int rc;

    rc = sa_read(studs, &studs_n);
    if (rc != OK)
        return rc;

    sa_sort(studs, studs_n);

    sa_print(studs, studs_n);

    return OK;
}




