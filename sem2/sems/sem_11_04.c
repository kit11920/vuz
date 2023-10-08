/*
Пользователь вводит строку, необходимо
- разделить строку на слова
- отсортировать слова в алфавитном порядке
- свормировать новую строку из этих слов
*/

#include <stdio.h>
#include <string.h>

#define OK 0
#define ERR_IO 1
#define ERR_BUF_TOO_SMALL 2
#define ERR_TOO_MUCH_WORDS 3

#define STR_LEN (127+1)
#define WORD_LEN (20+1)
#define N 10
#define DELIMS "\n \t./;!?"

// char* fgets(char *buf, size_t buf_size, FILE *f)

/*
Вводит строку

Параметры:
-буффер
-размер буффера

Возвращает код ошибки
*/
int get_line(char *buf, size_t buf_size)
{
    char *p;
    printf("Введите строку: ");
    if (!fgets(buf, buf_size, stdin))
        return ERR_IO;
    p = strrchr(buf, '\n'); // указатель на местро в строке где находится искомый символ
    // strchr, strrchr
    if (p)
    {
        *p = 0; // заменили \n на ноль
        // 0 эквивалентен '\0'
        return OK;
    }

    return ERR_BUF_TOO_SMALL;
}

/*
Определяет указатель на начало слова и на конец слова

Параметры
- строка, она не меняется, надо const
- указатель на указатель начала млова
- указатель на указатель конца слова
*/
void get_next_word(char *str, char **pbeg, char **pend)
{
    char *pcur = str;
    *pbeg = *pend = NULL;

    while (*pcur && strchr(DELIMS, *pcur))
        pcur++;

    if (!*pcur)
        return;

    *pbeg = pcur;
    while (*pcur && !strchr(DELIMS, *pcur))
        pcur++;

    *pend = pcur;
}

/*
Копирует слово из указателей в перемнную
*/
int copy_word(const char *pbeg, const char *pend, char *word, size_t word_size)
{
    if ((pend - pbeg + 1) > word_size)
        return ERR_BUF_TOO_SMALL;
    while (pbeg < pend)
    {
        *word = *pbeg;
        pbeg++;
        word++;
    }
    *word = 0;

    return 0;
}

/*
Разделяет строку на массив слов

Параметры
-строка
-массив слов
-количество слов

Возвращает код ошибки
*/
int parse_string(char *str, char words[][WORD_LEN], size_t *words_n)
{
    char *pbeg, *pend, *pcur = str;
    size_t n = 0; // колво слов
    int rc = OK; // код возврата return code

    while (rc == OK && pcur && *pcur)
    {
        get_next_word(pcur, &pbeg, &pend);
        if (pbeg)
        {
            if (n < N)
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

    if (rc == OK)
        *words_n = n;

    return rc;
}

/*
Формирует строку из массива
Слова в строке отделяются 1 пробелом

Параметры
-массив слов
-его размер
-строка которую будем формировать
-размер строки

Возвращает код возврата
*/
int form_string(char words[][WORD_LEN], size_t words_n, char *buf, size_t buf_size)
{
    size_t need = 0;

    for (size_t i = 0; i < words_n; i++)
        need = need + (strlen(words[i] + 1));

    if (need > buf_size)
        return ERR_BUF_TOO_SMALL;

    buf[0] = 0; // превратили buf  в пустую строку
    for (size_t i = 0; i < words_n - 1; i++)
    {
        strcat(buf, words[i]);
        strcat(buf, " ");
    }

    strcat(buf, words[words_n - 1]);
    return OK;
}


int main(void)
{

}


























