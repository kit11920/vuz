#ifndef IN_OUTPUT_H__
#define IN_OUTPUT_H__


#include <stdio.h>
#include <stdlib.h>
#include "fort.h"


/// @brief Вводит строку
/// @param [in out] f - файловая переменная
/// @param [out] str - строка
/// @param [in] max_len_str - максимальная длина строки
/// @return код ошибки
int input_str(FILE *f, char *str, const size_t max_len_str);

/// @brief Вводит название страны
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] name - укзатель на введенное название страны
/// @return код ошибки
int input_name(FILE *f, bool print_input_text, char *name);

/// @brief Вводит столицу страны
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] capital - укзатель на введенную столицу страны
/// @return код ошибки
int input_capital(FILE *f, bool print_input_text, char *capital);

/// @brief Вводит континент на котором находится страна
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] continent - укзатель на введенный континент
/// @return код ошибки
int input_continent(FILE *f, bool print_input_text, char *continent);

/// @brief Вводит нужна ли виза для посещения страны
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] visa - укзатель на надобности визы
/// @return код ошибки
int input_visa(FILE *f, bool print_input_text, bool *visa);

/// @brief Вводит время полета до страны
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] time - укзатель на введенное время полета до страны
/// @return код ошибки
int input_time(FILE *f, bool print_input_text, int *time);

/// @brief Вводит стоимость отдыха в стране
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] cost_min - укзатель на введенную стоимость отдыха в стране
/// @return код ошибки
int input_cost_min(FILE *f, bool print_input_text, int *cost_min);

/// @brief Вводит вид туризма в стране
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] type_tourism - укзатель на введенный вид туризма в стране
/// @return код ошибки
int input_type_tourism(FILE *f, bool print_input_text, type_tourism_t *type_tourism);

/// @brief Вводит количество достопримечательностей в стране
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] count_sights - укзатель на введенное количество достопримечательностей в стране
/// @return код ошибки
int input_exrsn_trsm_count_sights(FILE *f, bool print_input_text, int *count_sights);

/// @brief Вводит вид достопримечательностей в стране
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] type_sights - укзатель на введенный вид достопримечательностей в стране
/// @return код ошибки
int input_exrsn_trsm_type_sights(FILE *f, bool print_input_text, char *type_sights);

/// @brief Вводит структуру вида экскурсионного туризма в стране
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] exrsn_trsm - укзатель на введенную структуру вида экскурсионного туризма в стране
/// @return код ошибки
int input_excursion_tourism(FILE *f, struct excursion_tourism_t *exrsn_trsm, bool print_input_text);

/// @brief Вводит сезон пляжного отдыха в стране
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] season - укзатель на введенный сезон пляжного отдыха в стране
/// @return код ошибки
int input_beach_trsm_season(FILE *f, bool print_input_text, char *season);

/// @brief Вводит температуру возуда в стране
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] air_temp - укзатель на введенную температуру возуда в стране
/// @return код ошибки
int input_beach_trsm_air_temp(FILE *f, bool print_input_text, int *air_temp);

/// @brief Вводит температуру воды в стране
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] water_temp - укзатель на введенную температуру воды в стране
/// @return код ошибки
int input_beach_trsm_water_temp(FILE *f, bool print_input_text, int *water_temp);

/// @brief Вводит структуру вида пляжного туризма в стране
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] beach_trsm - укзатель на введенную структуру вида пляжного туризма в стране
/// @return код ошибки
int input_beach_tourism(FILE *f, struct beach_tourism_t *beach_trsm, bool print_input_text);

/// @brief Вводит вид спорта в стране 
/// @param [in out] f - файловая переменная
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @param [out] sport_type - укзатель на введенный вид спорта в стране
/// @return код ошибки
int input_sport_type(FILE *f, bool print_input_text, char *sport_type);

/// @brief Вводит структуру страны
/// @param [in out] f - файловая переменная
/// @param [out] country - указатель на введенную структуру страны
/// @param [in] ind - индекс введенной структуры страны в таблице
/// @param [in] print_input_text - надо ли ввыводить приглашающий к вводу текст
/// @return код ошибки
int input_country(FILE *f, struct country_t *country, size_t ind, bool print_input_text);

/// @brief Вводим массив структур стран
/// @param [in out] f - файловая переменная 
/// @param [out] table - массив стран
/// @param [out] len_table - длина массива стран (указатель)
/// @param [in] max_len_table - максимальная длина массива стран
/// @return код ошибки
int input_table(FILE *f, struct country_t table[], size_t *len_table, size_t max_len_table);

/// @brief Считывает массив стран из файла
/// @param [in] filename - имя файда
/// @param [out] table - массив стран
/// @param [out] len_table - длина массива table (указатель)
/// @param [in] max_len_table - максимальная длина table
/// @return код ошибки
int read_table(char *filename, struct country_t table[], size_t *len_table, size_t max_len_table);





/// @brief Переводит переменную надобности визы в строку
/// @param [in] visa - переменная надобности визы
/// @param [out] visa_str - строки
void visa_to_str(bool visa, char *visa_str);

/// @brief Переводит переменную вида туризма в строку
/// @param [in] type - переменная вида туризма
/// @param [out] str - строка
void type_tourism_to_str(type_tourism_t type, char *str);

/// @brief Выводит страну как строку таблицы 
/// @param [in] tab - Рисуемая таблица
/// @param [in] country - структура страны (указатель)
void print_country(ft_table_t *tab, const struct country_t *country);

/// @brief Выводит заголовок нарисованной таблицы
/// @param [in] tab - рисуемая таблица
void print_header_tab(ft_table_t *tab);

/// @param [in] table - массив стран
/// @param [in] len_table - длина массива table
void print_table(const struct country_t table[], const size_t len_table);

/// @brief Выводит страну в таблице
/// @param [in] country - структура страны (указатель)
void print_one_country(const struct country_t *country);

/// @brief Выводит таблицу ключей в виде таблицы
/// @param [in] key_table - массив ключей
/// @param [in] len_table - длина массива key_table
void print_key_table(const struct key_table_t key_table[], const size_t len_table);

/// @brief Выводит массив стран в порядке указанном в массиве ключей
/// @param [in] table - массив стран
/// @param [in] len_table - длина массива table и key_table
/// @param [in] key_table  - массив ключей
void print_table_based_on_key_table(const struct country_t table[], size_t len_table, const struct key_table_t key_table[]);

#endif
