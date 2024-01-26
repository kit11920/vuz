#ifndef HELP_CHECK__H__
#define HELP_CHECK__H__

typedef struct struct_str_int
{
    char *str;
    int num;
} str_int_t;

// typedef void (*action_t)(const char *key, int *num, void *param);


/// @brief Заполняет массив данными 
/// @param [out] arr - описатель массива
/// @param [in] data - массив данных (пользовательских структур)
/// @param [in] len_arr - длина массива
/// @return код ошибки
assoc_array_error_t full_assoc_array(assoc_array_t arr, str_int_t *data, size_t len_arr);

/// @brief К каждому числу добавляет число param
/// @param [in] key - ключ
/// @param [in out] num - значение ключа
/// @param [in] param - указатель на число которое надо прибавить к значению
void action_plus(const char *key, int *num, void *param);

/// @brief Считает кол-во элементов в массиве у которых ключ это 1 симвод
/// @param [in] key - ключ
/// @param [in] num - значение ключа
/// @param [in out] param - указатель на счетчик количества (для первого элемента счетчик должен равняться 0)
void action_count_key_is_char(const char *key, int *num, void *param);



#endif

