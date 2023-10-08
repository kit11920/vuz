#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "number.h"
#include "errs.h"


void print_mantissa(const unsigned short mantissa[], size_t len_arr)
{
    printf("Mantissa: ");
    for (size_t j = 0; j < len_arr; j++)
        printf("%d ", mantissa[j]);
    printf("\n");
}


void round_num(unsigned short num[], size_t *len_arr, int *k)
{
    assert(*len_arr < LEN_ARR_MANTISSA);
    while (*len_arr > LEN_MANTISSA)
    {
        if (num[0] >= 5)
            num[1]++;
        // print_mantissa(num, *len_arr);
        for (size_t i = 0; i < *len_arr - 1; i++)
                num[i] = num[i + 1];
        (*len_arr)--;
        (*k)++;
    }
    size_t i = 0;
    while (num[i] == 10 && i + 1 < *len_arr)
    {
        num[i] = 0;
        num[i + 1]++;
        i++;
    }
    if (num[i] == 10 && i + 1 == *len_arr)
    {
        (*len_arr)++;
        (*k)++;
        num[i] = 0;
        num[i + 1] = 1;
    }
    //print_mantissa(num, *len_arr);
}


void multiplication_long_by_short_num(const unsigned short long_num[], const size_t len_long_arr, 
const unsigned short short_num, unsigned short res_num[], size_t *len_res_arr)
{
    short next_rung = 0, res;
    for (size_t i = 0; i < len_long_arr; i++)
    {
        res = long_num[i] * short_num + next_rung;
        next_rung = res / 10;
        res_num[i] = res % 10;
    }
    *len_res_arr = len_long_arr;

    if (next_rung != 0)
    {
        res_num[*len_res_arr] = next_rung;
        (*len_res_arr)++;
    }
}


int cmp_nums(const unsigned short num1[], const size_t len_arr1, const unsigned short num2[], const size_t len_arr2)
{
    if (len_arr1 != len_arr2)
        return len_arr1 - len_arr2;

    // print_mantissa(num1, len_arr1);
    // print_mantissa(num2, len_arr2);
    // printf("%zu %zu\n", len_arr1, len_arr2);
    
    size_t i = 1;
    while (i < len_arr1 && num1[len_arr1 - i] == num2[len_arr1 - i])
         i++;

    if (i == len_arr1)
        return num1[0] - num2[0];
    else
        return num1[len_arr1 - i] - num2[len_arr2 - i];
}


void num1_minus_num2(const unsigned short num1[], const size_t len_arr1, const unsigned short num2[], const size_t len_arr2, 
unsigned short res_num[], size_t *len_res_arr)
{
    // если числа равны
    int res_cmp = cmp_nums(num1, len_arr1, num2, len_arr2);

    if (res_cmp == 0)
    {
        res_num[0] = 0;
        *len_res_arr = 1;
        return;
    }
    //

    assert(cmp_nums(num1, len_arr1, num2, len_arr2) > 0);

    int minus_now = 0;
    int minus_next = 0;
    int res;
    for (size_t i = 0; i < len_arr2; i++)
    {
        res = num1[i] + minus_now;
        if (res < num2[i])
        {
            res += 10;
            minus_next = -1;
        }
        res -= num2[i];

        assert(0 <= res && res <= 9);
        res_num[i] = res;

        minus_now = minus_next;
        minus_next = 0;
    }

    size_t i = len_arr2;
    while (i < len_arr1)
    {
        res = num1[i] + minus_now;
        minus_now = 0;

        assert(0 <= res && res <= 9);        
        res_num[i] = res;
        i++;
    }
    *len_res_arr = i;
}


void division_for_one_digit_and_rest(const unsigned short num1[], const size_t len_arr1, 
const unsigned short num2[], const size_t len_arr2, 
unsigned short *integer, unsigned short rest[], size_t *len_rest_arr)
{
    short end_of_num1, end_of_num2;
    unsigned short res[LEN_ARR_MANTISSA];
    size_t len_res_arr = 0;

    // Выделяем числа с большими разрядами чтобы определить целую часть частного
    if (len_arr1 == len_arr2)
        end_of_num1 = num1[len_arr1 - 1];
    else
        end_of_num1 = num1[len_arr1 - 1] * 10 + num1[len_arr1 - 2];
    end_of_num2 = num2[len_arr2 - 1];
    //

    *integer = end_of_num1 / end_of_num2; // целая часть частного
    multiplication_long_by_short_num(num2, len_arr2, *integer, res, &len_res_arr);
    // если целая часть частного взята больше чем нужно
    while (cmp_nums(num1, len_arr1, res, len_res_arr) < 0)
    {
        (*integer)--;
        multiplication_long_by_short_num(num2, len_arr2, *integer, res, &len_res_arr);
    }
    //

    assert(*integer < 10); // целая часть частного должна получиться цифрой

    // находим остаток - rest
    num1_minus_num2(num1, len_arr1, res, len_res_arr, rest, len_rest_arr);
    //

    // Удаляем незначащие нули
    while (rest[*len_rest_arr - 1] == 0 && *len_rest_arr > 1)
        (*len_rest_arr)--;
    //
}


void longer_num_for_division(struct number_t *num1, const struct number_t *num2, int *count_added)
{
    *count_added = 0;
    while (cmp_nums(num1->mantissa, num1->len_arr, num2->mantissa, num2->len_arr) < 0)
    {
        (num1->len_arr)++;
        for (size_t i = num1->len_arr - 1; i > 0; i--)
            num1->mantissa[i] = num1->mantissa[i - 1];
        num1->mantissa[0] = 0;
        (num1->k)--;
        
        (*count_added)++;
    }
}


void add_integet_to_mantissa(unsigned short mantissa[], size_t *len_arr, const unsigned short integer)
{
    assert(*len_arr + 1 <= LEN_ARR_MANTISSA);
    (*len_arr)++;
    for (size_t i = *len_arr - 1; i > 0; i--)
        mantissa[i] = mantissa[i - 1];
    mantissa[0] = integer;
}


int division(const struct number_t *num1, const struct number_t *num2, struct number_t *num3)
{
    int sign3 = num1->sign * num2->sign; 
    unsigned short mantissa3[LEN_ARR_MANTISSA];
    size_t len_arr3 = 0;
    int k3 = num1->k - num2->k;

    struct number_t num1_copy;
    num1_copy = *num1;
    int count_added_zero;


    // Проверка на делениена 0
    if (num2->mantissa[0] == 0 && num2->len_arr == 1)
        return ERR_DIVISION_ZERO;
    //

    // Выделяем неполное делимое
    // Если мантисса делимого меньше мантиссы делителя по длине то добавляем нули к мантиссе
    longer_num_for_division(&num1_copy, num2, &count_added_zero);
    k3 -= count_added_zero;
    // printf("count_added_zero first: %d\n", k3);
    //

    // находим индекс начала неполного делимого в мантиссе числа 1
    size_t ind_separate_div1; 
    assert(num1_copy.len_arr >= num2->len_arr);
    ind_separate_div1 = num1_copy.len_arr - num2->len_arr;

    if (cmp_nums(&num1_copy.mantissa[ind_separate_div1], num1_copy.len_arr - ind_separate_div1, 
    num2->mantissa, num2->len_arr) < 0)
    {
        assert(ind_separate_div1 > 0);
        ind_separate_div1--;
    }
    //


    unsigned short integer;
    unsigned short rest[LEN_ARR_MANTISSA];
    size_t len_rest_arr;

    while (!(num1_copy.len_arr == 1 && num1_copy.mantissa[0] == 0) && len_arr3 <= LEN_MANTISSA)
    {
        // Найдем частное(integer) и остаток(rest) деления неполного делимого и делителя
        // неполное делимое - часть мантисы num1_copy, начиная с индекса ind_separate_div1
        division_for_one_digit_and_rest(&num1_copy.mantissa[ind_separate_div1], num1_copy.len_arr - ind_separate_div1, 
        num2->mantissa, num2->len_arr, &integer, rest, &len_rest_arr);
        //

        // printf("num1 ");
        // print_mantissa(num1_copy.mantissa, num1_copy.len_arr);
        // printf("half div ");
        // print_mantissa(&num1_copy.mantissa[ind_separate_div1], num1_copy.len_arr - ind_separate_div1);
        // printf("num2 ");
        // print_mantissa(num2->mantissa, num2->len_arr);
        // printf("integer: %d\n", integer);


        // допишем целое от деления (integer) в ответ
        add_integet_to_mantissa(mantissa3, &len_arr3, integer);
        //

        // Возвращаем остаток(rest) от деления неполного делимого и делителя в num1_copy
        //printf("%zu %zu\n", len_rest_arr, ind_separate_div1);
        num1_copy.len_arr = len_rest_arr + ind_separate_div1;
        for (size_t i = ind_separate_div1; i < num1_copy.len_arr; i++)
            num1_copy.mantissa[i] = rest[i - ind_separate_div1];
        //

        // printf("rest ");
        // print_mantissa(num1_copy.mantissa, num1_copy.len_arr);

        // Увеличиваем длину неполного делимого если деление не закончилось
        if (!(num1_copy.len_arr == 1 && num1_copy.mantissa[0] == 0) && len_arr3 <= LEN_MANTISSA)
        {
            // Добавляем нули к делимому если оно меньше делителя
            longer_num_for_division(&num1_copy, num2, &count_added_zero);
            //printf("k3 count_added_zero: %d   %d\n", k3, count_added_zero);
            k3 -= count_added_zero;
            ind_separate_div1 += count_added_zero; // коррекция индекса
            //

            // увеличиваем длину неполного делимого на 1
            // (если после увеличения делимое < делителя то увеличиваем еще раз добавляя 0 в результат деления)
            ind_separate_div1--;
            while (cmp_nums(&num1_copy.mantissa[ind_separate_div1], num1_copy.len_arr - ind_separate_div1, 
            num2->mantissa, num2->len_arr) < 0)
            {
                add_integet_to_mantissa(mantissa3, &len_arr3, 0);
                ind_separate_div1--;
            }
            //
        }
        //
    }

    // если длина мантисы больше положеного, то округляем
    if (len_arr3 > LEN_MANTISSA)
    {
        //k3 += count_added_zero;
        round_num(mantissa3, &len_arr3, &k3);
        // printf("k3, count_added_zero: %d %d\n", k3, count_added_zero);
    }
    //

    // удаляем незначащие нули
    del_insignificant_zeros(mantissa3, &len_arr3, &k3);
    //

    // проверка на переполнение порядка в нормализованном виде
    if (k3 + (long long) len_arr3 < -99999 || k3 + (long long) len_arr3 > 99999)
        return ERR_ORDER_OVERFLOW;
    //

    // printf("k1 k2:  %d, %d\n", num1->k, num2->k);
    // printf("k3:   %d\n", k3);

    // переносим данные в структуру
    num3->sign = sign3;
    memcpy(num3->mantissa, mantissa3, sizeof(unsigned short) * len_arr3);
    num3->len_arr = len_arr3;
    num3->k = k3;
    //

    // printf("num3->k: %d\n", num3->k);

    return OK;
}
