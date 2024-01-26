#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>

#define STR_LEN (256+1)
#define WORD_LEN (16+1)
#define COUNT_WORDS 128
#define DELIMS " ,;:-.!?"


/**
@brief Вводит строку
@param
str - указатель на строку в которую будут введены данные
str_len - длина строки
@return код ошибки
*/
int get_line(char *str, size_t str_len);


/**
@brief
Копирует данные из строки, на которую указывает аргумент src,
в строку, на которую указывает аргумент dst,
пока не встретится символ конца строки (нулевой символ).
Копирование производится вместе с символом конца строки.
@param
dst – указатель на строку, в которую будут скопированы данные.
src – указатель на строку источник копируемых данных.
@return код ошибки
*/
int my_strcpy(char *dst, char *src, int dst_len);


/**
@brief Разделяет строку на массив слов
@param
str - указатель на строку
words - массив слов
words_n - указатель на количество слов
@return код ошибки
*/
int parse_string(char *str, char words[][WORD_LEN], size_t *count_words);


/**
@brief
Формирует строку из массива
Длина массива больше 0
Слова в строке отделяются 1 пробелом
@param
words - массив слов
words_n - количество слов
str - указатель на строку
str_len - длина строки
*/
void form_string(char words[][WORD_LEN], size_t words_n, char *str);

#endif // INPUT_OUTPUT_H
