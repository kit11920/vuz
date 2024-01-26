#ifndef INPUT_OUTPUT_H__
#define INPUT_OUTPUT_H__

#include <stdio.h>
#include <stdlib.h>

/// @brief Считает кол-во элементов записанные в файле
/// @param [in out] f - указатель на файловую переменную
/// @param [out] len_arr - укзатель на кол-во элементов в файле
/// @return код ошибки
int count_elems_in_arr(FILE *f, size_t *len_arr);


/// @brief Заполняет массив целыми числами из файла
/// @param [in out] f - указатель на файловую переменную 
/// @param [in] pbeg - указатель на начало массива
/// @param [in] pend - указатель на конец массива
/// @return код ошибки
int fill_arr(FILE *f, int *const pbeg, int *const pend);


/// @brief Выводит массив в файл 
/// @param [in out] f - указатель на файловую переменную  
/// @param [in] pbeg - указатель на начало массива
/// @param [in] pend - указатель на конец массива
void output_arr(FILE *f, const int *const pbeg, const int *const pend);

#endif
