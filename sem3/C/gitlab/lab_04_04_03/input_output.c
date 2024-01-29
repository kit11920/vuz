#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "input_output.h"
#include "errors.h"

int get_line(char *str, size_t str_len)
{
    char *p;

    //printf("Введите строку: ");
    if (fgets(str, str_len, stdin) == NULL)
        return ERR_IO;

    p = strrchr(str, '\n');
    if (p)
    {
        *p = 0;
        return OK;
    }

    return ERR_BUF_TOO_SMALL;
}


int strip(char *str)
{
    char *pbeg, *pend;
    get_phone(str, &pbeg, &pend);

    if (pbeg == NULL)
        return ERR_ONLY_SPACES;

    while (pbeg < pend)
    {
        *str = *pbeg;
        str++;
        pbeg++;
    }

    *str = 0;

    return OK;
}


void get_phone(const char *str, char **pbeg, char **pend)
{
    *pbeg = *pend = NULL;
    const char *pcur = str;

    while (*pcur && isspace(*pcur))
        pcur++;

    if (*pcur == 0)
        return;

    *pbeg = (char *)pcur;
    while (*pcur && !isspace(*pcur))
        pcur++;

    *pend = (char *)pcur;
}

