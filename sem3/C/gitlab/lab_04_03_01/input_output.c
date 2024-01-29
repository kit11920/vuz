#include <stdio.h>
#include <string.h>
#include "input_output.h"
#include "errors.h"

int get_line(char *str, size_t str_len)
{
    char *p;
    printf("Введите строку: ");
    if (!fgets(str, str_len, stdin))
        return ERR_IO;
    p = strrchr(str, '\n');
    if (p)
    {
        *p = 0;
        return OK;
    }

    return ERR_BUF_TOO_SMALL;
}


int my_strcpy(char *dst, char *src, int dst_len)
{
    char *pcur_src = src;
    while (*pcur_src)
    {
        *dst = *pcur_src;
        pcur_src++;
        dst++;

        if (pcur_src - src + 1 > dst_len)
            return ERR_BUF_TOO_SMALL;
    }
    *dst = 0;

    return OK;
}


int parse_string(char *str, char words[][WORD_LEN], size_t *count_words)
{
    int rc = OK, n = 0; // n - индекс слова
    char *istr = strtok(str, DELIMS);
//    if (istr == NULL)
//        return ERR_ONLY_DELIMS;

    while (istr != NULL && n < COUNT_WORDS)
    {
        rc = my_strcpy(words[n], istr, WORD_LEN);
        if (rc != OK)
            return rc;
        n++;
        istr = strtok(NULL, DELIMS);
    }
//    if (n == COUNT_WORDS)
//        return ERR_TOO_MUCH_WORDS;
//    if (n == 1)
//        return ERR_ONLY_ONE_WORD;

    *count_words = n;

    return rc;
}

void form_string(char words[][WORD_LEN], size_t words_n, char *str)
{
//    if (words_n == 0)
//        return ERR_NO_DIFF_WORDS;

//    size_t need_strlen = 0;
//    for (size_t i = 0; i < words_n; i++)
//        need_strlen += strlen(words[i] + 1);

//    if (need_strlen > str_len)
//        return ERR_BUF_TOO_SMALL;

    str[0] = 0; // превратили str  в пустую строку
    for (size_t i = 0; i < words_n - 1; i++)
    {
        strcat(str, words[i]);
        strcat(str, " ");
    }
    strcat(str, words[words_n - 1]);
    //return OK;
}






