#ifndef IN_OUTPUT_H__
#define IN_OUTPUT_H__

#include <stdlib.h>
#include <stdio.h>

#include "inits.h"
#include "errs.h"


/// @brief Считываем матрицу из файла (память под матрицу уже выделена)
/// @param [in out] f - указатель на файловую переменную
/// @param [in out] mtrx - структура матрицы (указатель)
/// @return код ошибки
int read_mtrx(FILE *f, struct mtrx_t *mtrx);

/// @brief Выделяет память под матрицу и заполняет ее данными из файла
/// Открывает и закрывает файл с названием filename
/// Если выделилась память но произошла ошибка заполнения, то память освобождается
/// @param [in] filename - название файла
/// @param [out] mtrx - структура матрицы (указатель)
/// @return код ошибки
int create_mtrx(char *filename, struct mtrx_t *mtrx);



/// @brief Выводит матрицу в координатном виде по названию файла
/// @param [in] filename - название файла
/// @param [in] mtrx - структура матрицы (указатель)
/// @return код ошибки
int print_mtrx_coord_file(char *filename, struct mtrx_t *mtrx);

/// @brief Считает кол-во ненулевых элементов в матрице
/// @param [in] mtrx - структура матрицы (указатель) 
/// @return кол-во ненулевых элементов в матрице
size_t count_nonzero(struct mtrx_t *mtrx);

/// @brief Выводит матрицу в координатном виде по FILE * 
/// @param [in out] f - указатель на файловую переменную или поток вывода
/// @param [in] mtrx - структура матрицы (указатель)
void print_mtrx_coord(FILE *f, struct mtrx_t *mtrx);

/// @brief Выводит матрицу в стандартном виде на экран
/// @param [in] mtrx - структура матрицы (указатель)
void print_mtrx_standart(struct mtrx_t *mtrx);



#endif

