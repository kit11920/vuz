#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include "phone_number.h"
#include "errors.h"


bool is_line_digits(const char *str, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (!isdigit(*str))
            return false;
        str++;
    }
    return true;
}


bool is_phone(const char *str)
{
    int ind = 0;

    if (str[ind] == 0 || str[ind + 1] == 0 || (str[ind] != '+' && str[ind] != '(') || (str[ind] == '+' && str[ind + 1] == '('))
        return false;

    if (str[ind] == '+')
    {
        ind++;
        while (isdigit(str[ind]))
            ind++;
    }

    if (str[ind] != '(')
        return false;
    ind++;

    if (!is_line_digits(str + ind, 3))
        return false;
    ind += 3;
//    for (int i = 0; i < 3; i++)
//    {
//        if (!isdigit(str[ind]))
//            return false;
//        ind++;
//    }

    if (str[ind] != ')' || str[ind + 1] != '-')
        return false;
    ind += 2;

    if (!is_line_digits(str + ind, 3))
        return false;
    ind += 3;
//    for (int i = 0; i < 3; i++)
//    {
//        if (!isdigit(str[ind]))
//            return false;
//        ind++;
//    }

    for (int k = 0; k < 2; k++)
    {
        if (str[ind] != '-')
            return false;
        ind++;

        if (!is_line_digits(str + ind, 2))
            return false;
        ind += 2;
//        for (int i = 0; i < 2; i++)
//        {
//            if (!isdigit(str[ind]))
//                return false;
//            ind++;
//        }
    }

    if (str[ind] != 0)
        return false;

    return true;
}

