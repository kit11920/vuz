#include <stdio.h>
#include <stdbool.h>
#include "input_output.h"
#include "errors.h"

void only_frst_enty_char(char *word)
{
    char *pread, *pwrite;
    pread = pwrite = word;

    while (*pread)
    {
        bool frst = true;
        for (char *pcur = word; pcur < pwrite && frst; pcur++)
            if (*pread == *pcur)
                frst = false;
        if (frst)
        {
            *pwrite = *pread;
            pwrite++;
        }
        pread++;
    }
    *pwrite = 0;
}


bool if_str_same(char *str1, char *str2)
{
    bool if_same = true;
//    if (str1 == NULL || str2 == NULL)
//        if_same = false;
    while (*str1 && *str2)
    {
        if (*str1 != *str2)
            if_same = false;
        str1++;
        str2++;
    }
    if (*str1 || *str2)
        if_same = false;
    return if_same;
}

int make_new_arr_of_words(char words[][WORD_LEN], size_t count_words, char new_words[][WORD_LEN], size_t *count_new_words)
{
    int rc = OK;
    size_t ind_new_words = 0;
    for (int i = count_words - 2; i >= 0; i--)
    {
        if (!if_str_same(words[count_words - 1], words[i]))
        {
            rc = my_strcpy(new_words[ind_new_words], words[i], WORD_LEN);
            if (rc != OK)
                return rc;

            only_frst_enty_char(new_words[ind_new_words]);
            ind_new_words++;
        }
    }
//    if (ind_new_words == 0)
//        return ERR_NO_DIFF_WORDS;

    *count_new_words = ind_new_words;
    return OK;
}



