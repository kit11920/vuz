#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#define STR_LEN (256+1)

#include <stdio.h>

/**
@brief Вводит строку
@param
str - указатель на строку в которую будут введены данные
str_len - длина строки
@return код ошибки
*/
int get_line(char *str, size_t str_len);


/**
@brief Удаляет пробельные символы по бокам от слова
@param
str - указатель на строку
@return код ошибки
*/
int strip(char *str);


/**
@brief Из строки str выделяется часть без пробелов по бокам и
записывается в виде указателей на начало и конец этой части
Если строка состоить только из пробельных символов pbeg = NULL
@param
str - указатель на строку
pbeg - указатель на указатель начала слова
pend - указатель на указатель конец слова
*/
void get_phone(const char *str, char **pbeg, char **pend);


#endif // INPUT_OUTPUT_H
