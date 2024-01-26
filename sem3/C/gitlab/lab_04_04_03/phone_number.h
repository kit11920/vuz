#ifndef PHONE_NUMBER_H
#define PHONE_NUMBER_H

#include <stdbool.h>

/**
@brief Определяет является ли строка номером телефона
по следующему шаблону
[+произвольное колво десятичных цифр](DDD)-DDD-DD-DD
D - десятичная цифра
Предполагается что указатель не нулевой
@param
str - указатель на строку
@return true - является, false - нет
*/
bool is_phone(const char *str);


#endif // PHONE_NUMBER_H
