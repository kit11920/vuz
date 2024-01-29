#include <stdio.h>
#include <string.h>

const char *my_strpbrk(const char *str, const char *sym)
{
    const char *frst_chr = NULL;
    int ind_frst_chr, ind;
    const char *pcur_sym = sym, *pcur_str;
    while (*pcur_sym)
    {
        pcur_str = str;
        ind = 0;
        while (*pcur_str)
        {
            if (*pcur_sym == *pcur_str)
                if (frst_chr == NULL || ind < ind_frst_chr)
                {
                    frst_chr = pcur_str;
                    ind_frst_chr = ind;
                }
            pcur_str++;
            ind++;
        }
        pcur_sym++;
    }

    return frst_chr;
}

size_t my_strspn(const char *str, const char *sym)
{
    size_t max_len = 0;

    const char *pcur = str;
    while (*pcur && strchr(sym, *pcur))
    {
        pcur++;
        max_len++;
    }
    return max_len;
}

size_t my_strcspn(const char *str, const char *sym)
{
    size_t max_len = 0;

    const char *pcur = str;
    while (*pcur && ! strchr(sym, *pcur))
    {
        pcur++;
        max_len++;
    }
    return max_len;
}

char *my_strchr(const char *str, int ch)
{
    char *pcur = (char *)str;
    while (*pcur && ch != *pcur)
        pcur++;
    if (*pcur || ch == *pcur)
        return pcur;
    else
        return NULL;
}

char *my_strrchr(const char *str, int ch)
{
    char *frst_chr = NULL;
    char *pcur = (char *)str;
    while (*pcur)
    {
        if (*pcur == ch)
            frst_chr = pcur;
        pcur++;
    }
    if (*pcur == ch)
        frst_chr = pcur;
    return frst_chr;
}

















