#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>

/**
@brief Проводит тест с данными строкми для функции strpbrk
@param
const char *str, const char *sym
- параметры для функции strpbrk
@return количество ошибок при тестировании
*/
int test_strpbrk(const char *str, const char *sym);

/**
@brief Проводит все тесты для функции strpbrk
@return количество ошибок при тестировании
*/
int all_tests_strpbrk();

/**
@brief Проводит тест с данными строкми для функции strspn
@param
const char *str, const char *sym
- параметры для функции strspn
@return количество ошибок при тестировании
*/
int test_strspn(const char *str, const char *sym);

/**
@brief Проводит все тесты для функции strspn
@return количество ошибок при тестировании
*/
int all_tests_strspn();

/**
@brief Проводит тест с данными строкми для функции strcspn
@param
const char *str, const char *sym
- параметры для функции strcspn
@return количество ошибок при тестировании
*/
int test_strcspn(const char *str, const char *sym);

/**
@brief Проводит все тесты для функции strcspn
@return количество ошибок при тестировании
*/
int all_tests_strcspn();


/**
@brief Проводит тест с данными строкми для функции strchr
@param
const char *str, int ch
- параметры для функции strchr
@return количество ошибок при тестировании
*/
int test_strchr(const char *str, int ch);

/**
@brief Проводит все тесты для функции strchr
@return количество ошибок при тестировании
*/
int all_tests_strchr();

/**
@brief Проводит тест с данными строкми для функции strrchr
@param
const char *str, int ch
- параметры для функции strrchr
@return количество ошибок при тестировании
*/
int test_strrchr(const char *str, int ch);

/**
@brief Проводит все тесты для функции strrchr
@return количество ошибок при тестировании
*/
int all_tests_strrchr();

#endif // TESTS_H
