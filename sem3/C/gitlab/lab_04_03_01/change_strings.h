#ifndef CHANGE_STRINGS_H
#define CHANGE_STRINGS_H

#include <stdio.h>
#include <stdbool.h>
#include "input_output.h"

/**
@brief
Оставляет в слове word только первые вхождения каждой буквы
@param
word - указатель на слово
*/
void only_frst_enty_char(char *word);


/**
@brief
Проверяет одинаковые ли строки
Предполагается что ссылки на строки не NULL
@param
str1, str2 - ссылки на строки
@return true - если одинаковые, false - если разные
*/
bool if_str_same(char *str1, char *str2);

/**
@brief
Помещает в новый массив строк new_words на основе words по правилу
В новый массив помещаются слова отличные от последнего, в обратном порядке и
подвергшиеся проеобразованию only_frst_enty_char
Размер массива words не превышает размера new_words
@param
words - массив слов
count_words - длина words
new_words - новый массив слов который составили
count_new_words - ссылка на длину new_words
@return код ошибки
*/
int make_new_arr_of_words(char words[][WORD_LEN], size_t count_words, char new_words[][WORD_LEN], size_t *count_new_words);



#endif // CHANGE_STRINGS_H
