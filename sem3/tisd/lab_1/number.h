#ifndef NUMBER_H__
#define NUMBER_H__

#include <stdlib.h>

// длина мантисы - 40 + длина порядка - 5 + 
// знаки перед мантисой и порядком - 2 + Е и пробелы между ней - 3 + точка в мантисе - 1 = 51
#define MAX_LEN_BUF 51
// число хранится в массиве по цифрам, чтобы сохранить
// результат перемножения двух 40-значных чисел берем 80 цифр
#define LEN_ARR_MANTISSA 80
// длина мантисы при вводе и выводе
#define LEN_MANTISSA 40

struct number_t
{
    int sign;
    unsigned short mantissa[LEN_ARR_MANTISSA];
    size_t len_arr;
    int k;
};


/// @brief Обрабатывает ввод строки
/// @param [out] buf - строка
/// @param [out] max_len_str - максимальная длина строки
/// @return код ошибки
int input_str(char *buf, int max_len_str);


/// @brief Записывает цифры из строки buf в массив мантиссы пока не встретит первую не цифру
/// Цифры записываются в мантису в прямом порядке - в массиве старшие разряды расположены слева
/// @param [in] buf - строка
/// @param [in out] ind_buf - указатель на индекс символа строки который сейчас обрабатывается
/// @param [in out] mantissa - массив мантиссы
/// @param [in out] len_arr - указатель на длину массива
/// @return код ошибки
int input_mantissa(const char *buf, size_t *ind_buf, unsigned short mantissa[], size_t *len_arr);


/// @brief Удаляет не значащие нули
/// Цифры записываются в мантису в обратном порядке - в массиве старшие разряды расположены справа
/// @param [in out] mantissa - массив мантиссы
/// @param [in out] len_arr - указатель на длину массива
/// @param [in out] k - указатель на порядок числа
void del_insignificant_zeros(unsigned short mantissa[], size_t *len_arr, int *k);


/// @brief переворачивает массив
/// @param [out] arr - массив
/// @param [in] len_arr - длина массива
void reverse_arr(unsigned short arr[], const size_t len_arr);


/// @brief Считывает число в формате "+-m.n E +-k" из строки buf, 
/// где длинна (m + n) <= 40 и длина k <= 5
/// @param [in] buf - строка
/// @param [out] num - указатель на структуру числа
/// @return код ошибки
int get_number_from_str(const char *buf, struct number_t *num);


/// @brief Выводит число в нормализованном виде
/// Предполагается что переполнения порядка нет и длина мантисы <= 40 знаков
/// @param [in] num - указатель на структуру числа
void print_num(const struct number_t *num);



#endif
