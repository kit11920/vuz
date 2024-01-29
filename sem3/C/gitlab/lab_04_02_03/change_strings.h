#ifndef CHANGE_STRINGS_H
#define CHANGE_STRINGS_H

#include <stdio.h>
#include "input_output.h"

/**
@brief Возвращает количество вхождений слова word в массив слов words
Длина слова word равна длине слов в массиве и равна WORD_LEN
@param
words - массив слов
count_words - количество слов в массиве
word - слово
@return Количество вхождений слова word в массив слов words
*/
int count_of_word_in_arr_of_strs(char words[][WORD_LEN], size_t count_words, char *word);


/**
@brief Записывает в массив слов diff_words слова,
которые встречаются в массивах words1 и words2 только 1 раз
@param
words1, words2 - массивы слов
count_words1, count_words2 - количество слов в соответствующих массивах
diff_words - массив слов в который будут записаны неповторяющиеся слова
count_diff_words - количество слов в diff_words
*/
void diff_words_in_strs(char words1[][WORD_LEN], size_t count_words1, char words2[][WORD_LEN], size_t count_words2, char diff_words[][WORD_LEN], size_t *count_diff_words);


#endif // CHANGE_STRINGS_H
