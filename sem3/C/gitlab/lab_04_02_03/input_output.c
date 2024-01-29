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


void get_next_word(const char *str, char **pbeg, char **pend)
{
    const char *pcur = str;
    *pbeg = *pend = NULL;

    while (*pcur && strchr(DELIMS, *pcur))
        pcur++;

    if (*pcur == 0)
        return;

    *pbeg = (char *)pcur;
    while (*pcur && !strchr(DELIMS, *pcur))
        pcur++;

    *pend = (char *)pcur;
}


int copy_word(const char *pbeg, const char *pend, char *word, size_t word_size)
{
    if ((pend - pbeg + 1) > (long int)word_size)
        return ERR_BUF_TOO_SMALL;

    while (pbeg < pend)
    {
        *word = *pbeg;
        pbeg++;
        word++;
    }
    *word = 0;

    return OK;
}


int parse_string(char *str, char words[][WORD_LEN], size_t *count_words)
{
    char *pbeg, *pend, *pcur = str;
    size_t n = 0; // колво слов
    int rc = OK;

    while (rc == OK && pcur && *pcur)
    {
        get_next_word(pcur, &pbeg, &pend);

        if (pbeg)
        {
            if (n < COUNT_WORDS)
            {
                rc = copy_word(pbeg, pend, words[n], WORD_LEN);

                if (rc == OK)
                    n++;
            }
            else
                rc = ERR_TOO_MUCH_WORDS;
        }
        pcur = pend;
    }

    //printf("%zu", n);
    if (rc == OK)
        *count_words = n;
    return rc;
}


int form_string(char words[][WORD_LEN], size_t words_n, char *str, size_t str_len)
{
    if (words_n == 0)
        return ERR_NO_DIFF_WORDS;

    size_t need_strlen = 0;
    for (size_t i = 0; i < words_n; i++)
        need_strlen += strlen(words[i] + 1);

    if (need_strlen > str_len)
        return ERR_BUF_TOO_SMALL;

    str[0] = 0; // превратили str  в пустую строку
    for (size_t i = 0; i < words_n - 1; i++)
    {
        strcat(str, words[i]);
        strcat(str, " ");
    }
    strcat(str, words[words_n - 1]);
    return OK;
}


