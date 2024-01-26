#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#include "errs.h"

// int my_strcpy(char *dst, char *src, size_t *i, size_t max_dst_i)
// {
//     size_t j = 0;
//     while (src[j] != 0)
//     {
//         if (*i >= max_dst_i)
//             return ERR_RANGE;
//         dst[*i] = src[j];
//         (*i)++;
//         j++;
//     }
//     return OK;
// }

size_t my_strncpy(char *dst, char *src, size_t n)
{
    size_t j = 0;
    while (src[j] != 0 && j < n)
    {
        dst[j] = src[j];
        j++;
    }
    return j;
}

size_t my_strlen(char *str)
{
    size_t i = 0;
    while (str[i] != 0)
        i++;
    return i;
}

size_t num_10_to_16str_len(unsigned long long int num)
{
    unsigned int n = 16;
    unsigned long long int tmp;
    size_t lenstr = 0;

    tmp = num;
    while (tmp >= n)
    {
        tmp /= n;
        lenstr++;
    }
    lenstr++;

    return lenstr;
}

size_t num_10_to_16str_nadd(char *str, size_t n, unsigned long long int num)
{
    unsigned int ss = 16;
    char alphabet[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };
    size_t lenstr = 0, max_len_str, j;
    unsigned long long int tmp;
    int rest;

    // Считаем длину результирующей строки
    lenstr = num_10_to_16str_len(num);
    max_len_str = lenstr;
    //
    // Случай когда не хватает пямяти и копируется не вся строка
    if (lenstr > n)
        lenstr = n;
    //
    
    // Пропускаем цифры с конца числа если они не входят в результирующую строку
    tmp = num;
    for (size_t i = 0; i < max_len_str - lenstr; i++)
        tmp /= ss;
    //

    // Переводит число 10сс в 16сс строку
    j = lenstr - 1;
    while (tmp >= ss)
    {
        rest = tmp % ss;
        str[j] = alphabet[rest];
        j--;
        tmp /= ss;
    }
    str[j] = alphabet[tmp];
    
    return lenstr;
}

/* Алгоритм
Проверяет параметр format, так как в моей функции возможна передача его как NULL
Считает кол-во символов которых потребуется для выходной строки - enough
И параллетльно проверяет верность содержимоно format
(При неверно переданных параметрах моя функция возвращает отрицательное значение,
в то время как для оригинальное фунции компилятор неверных параметров впринципе не допустит)

Если size_str == 0, то возвращентся enough и ничего в str не записывается
*Как раз для этого и нужен двойной просмотр параметров, на случай если size_str == 0 и 
для того чтобы убедиться что format задан верно
(За один просмотр скорее всего можно решить, но это очень усложнит код, добавит кучу разных if,
и как раз из-за их присутствия не факт что будет выигрышь по времени и понятность кода)

Далее заполняется стока str, на столько сколько под нее выделено памяти
Так же в функция ввода %s %llx учитывается случай когда подстрока или число в 16й с/с запишутся не полностью
*/
int my_snprintf(char *str, size_t size_str, const char *format, ...)
{
    if (format == NULL)
        return ERR_PARAMS;
    int rc = OK;

    // Считывает кол-во символов потребуется для выходной строки enough
    va_list vl;
    va_start(vl, format);
    size_t i = 0, enough = 0;
    while (format[i] != 0 && rc == OK)
    {
        if (format[i] != '%')
            enough++;
        else if (format[i + 1] == 's')
        {
            char *s = va_arg(vl, char *);
            enough += my_strlen(s);
            i++;
        }
        else if (format[i + 1] == 'l' && format[i + 2] == 'l' && format[i + 3] == 'x')
        {
            unsigned long long int num = va_arg(vl, unsigned long long int);
            enough += num_10_to_16str_len(num);
            
            i += 3;
        }
        else
            rc = ERR_FORMAT;
        i++;
    }
    va_end(vl);
    //
    if (rc != OK)
    {
        str = NULL;
        return rc;
    }
    if (size_str == 0)
    {
        str = NULL;
        return enough;
    }

    va_start(vl, format);
    i = 0;
    size_t j = 0;
    while (format[i] != 0 && j != size_str - 1)
    {
        if (format[i] != '%')
        {
            str[j] = format[i];
            j++;
        }
        else if (format[i + 1] == 's')
        {
            char *s = va_arg(vl, char *);
            size_t len_s = my_strncpy(&str[j], s, size_str - j - 1);
            j += len_s;
            i++;
        }
        else if (format[i + 1] == 'l' && format[i + 2] == 'l' && format[i + 3] == 'x')
        {
            // по умолчанию %x - unsigned int
            unsigned long long int num = va_arg(vl, unsigned long long int);
            
            size_t len_s = num_10_to_16str_nadd(&str[j], size_str - j - 1, num);
            j += len_s;
            i += 3;
        }
        else
            assert(rc == ERR_FORMAT);

        i++;
    }
    str[j] = 0;
    va_end(vl);

    return enough;
}

























