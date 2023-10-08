#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#include "number.h"
#include "errs.h"


int input_str(char *buf, int max_len_str)
{
    size_t buf_len;
    if (!fgets(buf, sizeof(char) * max_len_str, stdin))
        return ERR_IO;

    buf_len = strlen(buf);
    if (buf_len && buf[buf_len - 1] == '\n')
    {
        buf[buf_len - 1] = 0;
        buf_len--;
    }
    if (!buf_len || buf_len > MAX_LEN_BUF)
        return ERR_RANGE_STR;

    return OK;
}


int input_mantissa(const char *buf, size_t *ind_buf, unsigned short mantissa[], size_t *len_arr)
{
    size_t i = *ind_buf;
    char symbol[2];
    symbol[1] = 0;

    while (buf[i] != 0 && isdigit(buf[i]) && *len_arr <= LEN_MANTISSA)
    {
        symbol[0] = buf[i];
        //printf("elem: %c, %d\n", buf[i], atoi(symbol));
        mantissa[*len_arr] = (unsigned short) atoi(symbol);
        (*len_arr)++;
        i++;
    }

    if (*len_arr > LEN_MANTISSA)
        return ERR_RANGE_MANTISSA;

    *ind_buf = i;

    return OK;
}


void del_insignificant_zeros(unsigned short mantissa[], size_t *len_arr, int *k)
{
    // удаляем нули справа
    while (*len_arr > 1 && mantissa[*len_arr - 1] == 0)
        (*len_arr)--;
    //

    // удаляем нули слева
    while (*len_arr > 1 && mantissa[0] == 0)
    {
        for (size_t i = 0; i < *len_arr - 1; i++)
            mantissa[i] = mantissa[i + 1];
        (*len_arr)--;
        (*k)++;
    }
    //
    
    // .0
    if (*len_arr == 1 && mantissa[0] == 0)
        *k = 0;
}


void reverse_arr(unsigned short arr[], const size_t len_arr)
{
    short tmp;
    for (size_t i = 0; i < len_arr / 2; i++)
    {
        tmp = arr[i];
        arr[i] = arr[len_arr - 1 - i];
        arr[len_arr - 1 - i] = tmp;
    }
}


int get_number_from_str(const char *buf, struct number_t *num)
{
    int sign = 1;
    unsigned short mantissa[LEN_ARR_MANTISSA];
    size_t len_arr = 0;
    int k = 0; // порядок
    int rc = OK;

    size_t i = 0; // индекс знака с которым работаем

    // удаляем пробелы в начале строки
    while (buf[i] != 0 && buf[i] == ' ')
        i++;
    //
    
    // если есть знак перед числом
    if (buf[i] == '+' || buf[i] == '-')
    {
        if (buf[i] == '-')
            sign = -1;
        i++;
    }
    //

    // Записываем мантиссу в массив до первого символа не являющегося цифрой
    rc = input_mantissa(buf, &i, mantissa, &len_arr);
    if (rc != OK)
        return rc;
    //
    
    // Записываем мантиссу после точки
    if (buf[i] == '.')
    {
        i++;
        size_t last_i = i;
        
        rc = input_mantissa(buf, &i, mantissa, &len_arr);
        if (rc != OK)
            return rc;
        k = -(i - last_i);
    }
    //

    // Если значащих цифр так и не было введено
    if (len_arr == 0)
        return ERR_NO_MANTISSA;
    //

    // переворачиваем мантиссу
    reverse_arr(mantissa, len_arr);
    //

    // Удяляем незначащие нули
    del_insignificant_zeros(mantissa, &len_arr, &k);
    //

    // обрабатываем конструкцию " E " или " e "
    // пробелы перед Е 
    while (buf[i] != 0 && buf[i] == ' ')
        i++;
    // если конец строки и нет Е
    if (buf[i] != 0)
    {
        if (buf[i] == 'E' || buf[i] == 'e')
            i++;
        else
            return ERR_IO;

        // Вводим порядок - k
        char *pend;
        long adding_k = strtol(&buf[i], &pend, 10);
        if (adding_k == 0 && strcmp(&buf[i], pend) == 0)
            return ERR_IO;
        if (-99999 <= adding_k && adding_k <= 99999)
            k += (int) adding_k;
        else
            return ERR_ORDER_OVERFLOW;
        //

        // удаляем пробелы после порядка
        i = 0;
        while (pend[i] == ' ')
            i++;

        if (pend[i] != 0)
            return ERR_IO;
        //        
    }

    // если число 0, то порядок 1
    if (len_arr == 1 && mantissa[0] == 0)
        k = 0;
    //

    // Переносим введенные данные в структуру числа
    num->sign = sign;
    memcpy(num->mantissa, mantissa, sizeof(unsigned short) * len_arr);
    num->len_arr = len_arr;
    num->k = k;
    //

    return OK;
}

void print_num(const struct number_t *num)
{
    //del_insignificant_zeros(num->mantissa, &num->len_arr, &num->k);

    int k = num->k + num->len_arr; // порядок в нормализованном виде
    assert(-99999 <= k && k <= 99999);

    if (num->sign < 0)
        printf("-");
    else
        printf("+");

    printf("0.");
    for (int i = num->len_arr - 1; i >= 0; i--)
        printf("%d", num->mantissa[i]);
    
    printf(" E %+d\n", k);
}
