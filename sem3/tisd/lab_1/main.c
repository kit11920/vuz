#include <stdio.h>
#include <stdlib.h>

#include "errs.h"
#include "number.h"
#include "arithmetic.h"

#include "tests.h"


#define TESTING 0

int main(void)
{
    if (TESTING)
    {
        all_tests_get_number_from_str();
        return OK;
    }


    int rc = OK;
    struct number_t num1, num2, res_num;
    // struct number_t num1;
    char buf[MAX_LEN_BUF + 2];

    printf("Деления действительного числа на действительное число в форме +-m.n Е +-K,\n");
    printf("где суммарная длина мантиссы (m+n) - до 40значащих цифр, \n");
    printf("а величина порядка K - до 5цифр \n");
    printf("(вместо Е может быть записана е)\n");
    printf("Введите делимое и делитель:\n\n");

    printf("Линейка:\n");
    printf("123456789_123456789_123456789_123456789_123456789_123456789_123456789_\n\n");

    // Вводим делимое
    printf("Делимое:\n");
    rc = input_str(buf, MAX_LEN_BUF + 2);
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }
    rc = get_number_from_str(buf, &num1);
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }
    //

    // Вводим делитель
     printf("Делитель:\n");
    rc = input_str(buf, MAX_LEN_BUF + 2);
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }
    rc = get_number_from_str(buf, &num2);
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }
    //


    rc = division(&num1, &num2, &res_num);
    if (rc != OK)
    {
        print_error(rc);
        return rc;
    }

    // print_num(&num1);
    // print_num(&num2);
    
    printf("Результат деления:\n");
    print_num(&res_num);

    return rc;
}
