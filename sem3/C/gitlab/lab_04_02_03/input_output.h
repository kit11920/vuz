#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <stdio.h>

#define STR_LEN (256+1)
#define WORD_LEN (16+1)
#define COUNT_WORDS (STR_LEN - 1) / 2
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
Определяет указатель на начало слова и на конец слова
Рзделяет слова на пробельным символам и знакам препинания
@param
str - указатель на строку
pbeg - указатель на указатель начала млова
pend - указатель на указатель конца слова
*/
void get_next_word(const char *str, char **pbeg, char **pend);


/**
@brief Копирует слово из указателей в перемнную
@param
pbeg - константный указатель на начало слова
pend - константный указатель на конец слова
word - указатель на начало строки в которую запишем слово
word_size - размер слова
@return код ошибки
*/
int copy_word(const char *pbeg, const char *pend, char *word, size_t word_size);


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
Слова в строке отделяются 1 пробелом
@param
words - массив слов
words_n - количество слов
str - указатель на строку
str_len - длина строки
@return код ошибки
*/
int form_string(char words[][WORD_LEN], size_t words_n, char *str, size_t str_len);

#endif // INPUT_OUTPUT_H
