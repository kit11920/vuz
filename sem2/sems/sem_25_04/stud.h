#ifndef __STUD_H__
#define __STUD_H__

#include "errors.h"

#define NAME_LEN 15
#define MARKS_N 4


struct student_t
{
    char name[NAME_LEN + 1];
    int marks [MARKS_N];
};


/**
@brief Считывает структуру
@param pstud - струткра
@return код ошибки
*/
int stud_read(struct student_t *pstud);

/**
@brief Выводит структуру
@param stud - струткра
*/
void stud_print(const struct student_t stud);


/**
@brief Сравнивает структуры студентов по имени
@param lstud - струткра
@param rstud - струткра
@return Результат сравнения
-1 if lstud < rstud
0 if lstud == rstud
1 if lstud > rstud
*/
int stud_cmp_by_name(const struct student_t lstud, const struct student_t rstud);


/**
@brief Сравнивает структуры по средней оценке
@param lstud - струткра
@param rstud - струткра
@return Результат сравнения
-1 if lstud < rstud
0 if lstud == rstud
1 if lstud > rstud
*/
int stud_cmp_by_marks(const struct student_t stud1, const struct student_t stud2);
// Почему здесь были указатели на структуры??????????
// int stud_cmp_by_marks(const struct student_t *pl, const struct student_t *pr);

#endif
