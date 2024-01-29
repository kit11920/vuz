#ifndef MY_SNPRINTF_H__
#define MY_SNPRINTF_H__

#include <stdlib.h>

/// @brief Копирует строку src в dst целиком
/// @param [in out] dst строка в которую копируют (в этой строке нет \0)
/// @param [in] src строка которую копирую
/// @param [in] n ограничение длины копирования
/// @return кол-во скопированных символов
size_t my_strncpy(char *dst, char *src, size_t n);

/// @brief Считает длину строки
/// @param [in] str строка
/// @return длина строки
size_t my_strlen(char *str);

/// @brief Считает длину строки в которой записано число в 16 сс
/// @param [in] num число в 10 сс
/// @return длина строки
size_t num_10_to_16str_len(unsigned long long int num);

/// @brief Переводит десятичное число в 16ю число-строку и 
/// дописывает эту строку в str начиная с индекса i, так чтобы i < max_dst_i
/// @param [in out] str строка в которуб дописывает
/// @param [in] n ограничение длины копирования
/// @param [in] num число в 10й сс
/// @return кол-во скопированных символов
size_t num_10_to_16str_nadd(char *str, size_t n, unsigned long long int num);

/// @brief Преобразует число в отформатированную строку
/// Функция записывает в строку (size_str - 1) байт и добавляет концевой нулевой байт
/// @param [in] str строка, в которую помещается преобразованное число
/// @param [in] size_str максимальное количество символов строки. 
/// @param [in] format задает формат преобразования в строку (%s %llx)
/// @param [in] params параметры формата format
/// @return При успешном преобразовании функция возвращает количество символов, 
/// записанных в строку (исключая концевой нулевой байт). 
/// При неудачном преобразовании возвращается отрицательное число.
int my_snprintf(char *str, size_t size_str, const char *format, ... );















#endif
