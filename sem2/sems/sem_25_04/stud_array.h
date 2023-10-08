#ifndef __STUD_ARRAY_H__
#define __STUD_ARRAY_H__

#include "stud.h"
#include "array.h"
#include "errors.h"

#define STUDS_MAX 15
#define SORTING_MARKS true


/**
@brief Считывает массив студентов
@param studs - массив студентов
@param studs_n - указатель на количество студентов
@return код возврата
*/
int sa_read(struct student_t *studs, size_t *studs_n);


/**
@brief Выводит массив студентов
@param studs - массив студентов
@param studs_n - количество студентов
*/
void sa_print(const struct student_t *studs, size_t studs_n);


/**
@brief Сортирует массив студентов по оценками если SORTING_MARKS - true,
иначе сортирет по имени студента
@param studs - массив студентов
@param studs_n - указатель на количество студентов
*/
void sa_sort(struct student_t *studs, size_t studs_n);

#endif  
