#ifndef INSERT_LINE_H
#define INSERT_LINE_H

#include <stdio.h>
#include <stdbool.h>
#include "input_output.h"

/**
@brief Определяет нечетна ли сумма цифр числа
(если число отрицательное, рассматриваем его как пложительное,
если число - 0 то сумма четная (т к 0 - четное число)
@param
num - число
@return true если нечет
*/
bool if_odd_sum(int num);

/**
@brief
Определяет есть ли в массиве хотябы 2 элемента сумма цифр каждого из которых нечетна (if_odd_sum)
@param
a Массив
a_size Рамер массива
@return true если есть
*/
bool if_2elem_with_odd_sum(const int a[], size_t a_size);

/**
@brief Присваивает массиву a массив b, поэлементно
массивы не пустые и имеют одинаковый рамер
@param массив a, массив b, их рамер
*/
void assigning_arr_to_arr(int a[], const int b[], size_t n);

/**
@brief Смещает сроки начиная с данного индекса на один вниз
и вставляет массив inserting_line на индекс ind
Предполагается что с учетом размера массива это сделать можно
@param
a[][M] - матрица
a_n - указатель на количество строк матрицы
a_m - количество столбцов матрицы
ind - индекс
inserting_line - вставляемый массив
*/
void insert_one_line(int a[][M], size_t *a_n, size_t a_m, size_t ind, const int inserting_line[]);

/**
@brief Вставляет строку чисел -1 перед каждой строкой, (if_2elem_with_odd_sum)
в которой есть хотябы 2 элемента, сумма цифр каждого из которых нечетна
@param
a[][M] - матрица
a_n - указатель на количество строк матрицы
a_m - количество столбцов матрицы
@return код ошибки
*/
int insert_lines(int a[][M], size_t *a_n, size_t a_m);

#endif // INSERT_LINE_H
