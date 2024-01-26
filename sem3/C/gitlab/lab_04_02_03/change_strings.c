#include <stdio.h>
#include <string.h>
#include "change_strings.h"
#include "input_output.h"
#include "errors.h"


int count_of_word_in_arr_of_strs(char words[][WORD_LEN], size_t count_words, char *word)
{
    size_t count = 0;
    for (size_t i = 0; i < count_words; i++)
    {
        if (strcmp(words[i], word) == 0)
            count++;
//        char *pcur1 = words[i], *pcur2 = word;
//        while (*pcur1 && *pcur2 && *pcur1 == *pcur2)
//        {
//            pcur1++;
//            pcur2++;
//        }
//        if (!*pcur1 && !*pcur2)
//            count++;
    }
    return count;
}


void diff_words_in_strs(char words1[][WORD_LEN], size_t count_words1, char words2[][WORD_LEN], size_t count_words2, char diff_words[][WORD_LEN], size_t *count_diff_words)
{
    size_t ind_diff_words = 0;
    for (size_t i = 0; i < count_words1; i++)
        if (count_of_word_in_arr_of_strs(words2, count_words2, words1[i]) == 0 && count_of_word_in_arr_of_strs(words1, count_words1, words1[i]) == 1)
        {
            char *pbeg, *pend;
            // т к в строке words1[i] гарантированно 1 слово, в pend пометится указатель на его конец
            get_next_word(words1[i], &pbeg, &pend);
            copy_word(pbeg, pend, diff_words[ind_diff_words], WORD_LEN);
            ind_diff_words++;
        }

    for (size_t i = 0; i < count_words2; i++)
        if (count_of_word_in_arr_of_strs(words1, count_words1, words2[i]) == 0 && count_of_word_in_arr_of_strs(words2, count_words2, words2[i]) == 1)
        {
            char *pbeg, *pend;
            get_next_word(words2[i], &pbeg, &pend);
            copy_word(pbeg, pend, diff_words[ind_diff_words], WORD_LEN);
            ind_diff_words++;
        }
    *count_diff_words = ind_diff_words;
}





































