#ifndef IMPL_1_PLUS_H__
#define IMPL_1_PLUS_H__

#include <stdlib.h>
#include <stdio.h>

#include "associative_array.h"


typedef struct struct_data_t data_t;

struct struct_data_t
{
    const char *key;
    int num;
};

/*
Так как память подл массив будет выделяться при увеличении с запасом, 
но не факт что будет полность. использовать
Рациональнее сделать массив указателей, т к выделение память с запасом под под указатели
менее затрато чем выделение памчти с запасом под структуру
При большом размере массива будет выигрышь
*/
struct assoc_array_type
{
    data_t **data;          // динамически расширяемый массив указателей на структуры элементов
    size_t len;             // кол-во элементов заполнено по факту
    size_t real_len;        // размер массива (его фактическая длина)
    size_t step_increase;   // число на которое умножается размер массива при его увеличении
};


/// @brief Создает элемент data_t
/// @param key ключ
/// @param num число
/// @return Указатель на элемент data_t
data_t *assoc_array_data_create(const char *key, int num);

/// @brief Удаляет элемент по индексу
/// @param [in out] arr - описатель массива 
/// @param [in] ind - индекс массива данных по которому удаляем элемент 
/// @return код ошибки
assoc_array_error_t assoc_array_data_ind_remove(assoc_array_t arr, size_t ind);

/// @brief Увеличивает размер массива, перевыделяя память под него, если массив заполнен полностью
/// @param [in out] arr - описатель массива
/// @return код ошибки
assoc_array_error_t assoc_array_realloc(assoc_array_t arr);

/// @brief Ищет индекс элемента по ключу (бинарный поиск)
/// @param [in] arr - описатель массива 
/// @param [in] key - ключ 
/// @param [out] ind - указатель на индекс найденного элемента
/// @return код ошибки
assoc_array_error_t assoc_array_find_ind(const assoc_array_t arr, const char *key, size_t *ind);

/// @brief Вставляет элемент в отсортированный массив
/// Если места не хватает увеличивает размер массива
/// @param [in out] arr - описатель массива 
/// @param [in] data - указатель на структуру данных хранящихся в массива
/// @return код ошибки
assoc_array_error_t assoc_array_insert_sorted_arr(assoc_array_t arr, data_t *data);

/// @brief Освобождает память из под массива данных
/// @param [in out] arr - описатель массива  
void assoc_array_data_clear(assoc_array_t arr);

#endif

