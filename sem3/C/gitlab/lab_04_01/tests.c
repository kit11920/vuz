#include <stdio.h>
#include <string.h>
#include "funcs.h"

int test_strpbrk(const char *str, const char *sym)
{
    int count_fall = 0;
    char *res_my, *res;
    res_my = my_strpbrk(str, sym);
    res = strpbrk(str, sym);

    if (res_my != res)
        count_fall++;
    return count_fall;
}

int all_tests_strpbrk()
{
    int count_fall = 0;

    /*
    Тесты для функции strpbrk
    - 01 str - подходящих символов несколько в sym тоже
    - 02 str - подходящих символов несколько в sym 1 символ
    - 03 str - 1 символ в sym их несколько
    - 04 нет схожих символов
    - 05 Пустая str
    - 06 Пустая sym
    - 07 Пустые str, sym
    */
    count_fall += test_strpbrk("abcdb", "bcbd"); // 01
    count_fall += test_strpbrk("cdb", "b"); // 02
    count_fall += test_strpbrk("a", "bcaabda"); // 03
    count_fall += test_strpbrk("abc", "qwee"); // 04
    count_fall += test_strpbrk("", "qwee"); // 05
    count_fall += test_strpbrk("abc", ""); // 06
    count_fall += test_strpbrk("", ""); // 07

    return count_fall;
}

int test_strspn(const char *str, const char *sym)
{
    int count_fall = 0;
    size_t res_my, res;
    res_my = my_strspn(str, sym);
    res = strspn(str, sym);

    if (res != res_my)
        count_fall++;
    return count_fall;
}

int all_tests_strspn()
{
    int count_fall = 0;

    /*
    Тесты для функции strspn
    - 01 str - участок содержащий только символы из sym есть но не равен длине str, символы в sym в рандомном порядке
    - 02 str - участок содержащий только символы из sym есть но не равен длине str, символы в sym упорядочены как в str
    - 03 str - участок содержащий только символы из sym есть и равен длине str
    - 04 str - участок содержащий только символы из sym есть но равен 1
    - 05 str - участка содержащий только символы из sym нет
    - 06 Пустая str
    - 07 Пустая sym
    - 08 Пустые str, sym
    */
    count_fall += test_strspn("abcdef", "cabaef"); // 01
    count_fall += test_strspn("abcdef", "ab"); // 02
    count_fall += test_strspn("abc", "abc"); // 03
    count_fall += test_strspn("a", "a"); // 04
    count_fall += test_strspn("abc", "qwee"); // 05
    count_fall += test_strspn("", "qwee"); // 06
    count_fall += test_strspn("abc", ""); // 07
    count_fall += test_strspn("", ""); // 08


    return count_fall;
}

int test_strcspn(const char *str, const char *sym)
{
    int count_fall = 0;
    size_t res_my, res;
    res_my = my_strspn(str, sym);
    res = strspn(str, sym);

    if (res != res_my)
        count_fall++;
    return count_fall;
}

int all_tests_strcspn()
{
    int count_fall = 0;

    /*
    Тесты для функции strcspn
    - 01 str - участок не содержащий символы из sym есть но не равен длине str
    - 02 str - участок не содержащий символы из sym есть и равен длине str
    - 03 str - участок не содержащий символы из sym есть но равен 1
    - 04 str - участка не содержащий символы из sym нет
    - 05 Пустая str
    - 06 Пустая sym
    - 07 Пустые str, sym
    */
    count_fall += test_strcspn("abcde faaa", "deeefcf"); // 01
    count_fall += test_strcspn("abcd", "qqqqqq"); // 02
    count_fall += test_strcspn(" ", "qwe"); // 03
    count_fall += test_strcspn(" #$!1", "1! #$"); // 04
    count_fall += test_strcspn("", "qwee"); // 05
    count_fall += test_strcspn("abc", ""); // 06
    count_fall += test_strcspn("", ""); // 07

    return count_fall;
}

int test_strchr(const char *str, int ch)
{
    int count_fall = 0;
    char *res_my, *res;
    res_my = my_strchr(str, ch);
    res = strchr(str, ch);

    if (res_my != res)
        count_fall++;
    return count_fall;
}

int all_tests_strchr()
{
    int count_fall = 0;

    /*
    Тесты для функции strchr
    - 01 символ, код которого указан в аргументе ch - один и стоит вначале
    - 02 символ, код которого указан в аргументе ch - один и стоит в конце
    - 03 символ, код которого указан в аргументе ch - один и стоит в середине
    - 04 символ, код которого указан в аргументе ch - несколько штук
    - 05 символ, код которого указан в аргументе ch - нет
    - 06 Пустая str
    */
    count_fall += test_strchr("abcd", 'a'); // 01
    count_fall += test_strchr("abcd", 'd'); // 02
    count_fall += test_strchr("abcd", 'b'); // 03
    count_fall += test_strchr("abcdbfbbbbb", 'b'); // 04
    count_fall += test_strchr("abc", 'q'); // 05
    count_fall += test_strchr("", 'q'); // 06

    return count_fall;
}

int test_strrchr(const char *str, int ch)
{
    int count_fall = 0;
    char *res_my, *res;
    res_my = my_strrchr(str, ch);
    res = strrchr(str, ch);

    if (res_my != res)
        count_fall++;
    return count_fall;
}

int all_tests_strrchr()
{
    int count_fall = 0;

    /*
    Тесты для функции strrchr
    - 01 символ, код которого указан в аргументе ch - один и стоит вначале
    - 02 символ, код которого указан в аргументе ch - один и стоит в конце
    - 03 символ, код которого указан в аргументе ch - один и стоит в середине
    - 04 символ, код которого указан в аргументе ch - несколько штук
    - 05 символ, код которого указан в аргументе ch - нет
    - 06 Пустая str
    */
    count_fall += test_strrchr("abcd", 'a'); // 01
    count_fall += test_strrchr("dabcd", 'd'); // 02
    count_fall += test_strrchr("babcd", 'b'); // 03
    count_fall += test_strrchr("bbabcdbfbbbbb", 'b'); // 04
    count_fall += test_strrchr("abc", 'q'); // 05
    count_fall += test_strrchr("", 'q'); // 06

    return count_fall;
}








































