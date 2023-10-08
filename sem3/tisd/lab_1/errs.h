#ifndef ERRS_H__
#define ERRS_H__

#define OK 0
#define ERR_IO 1
#define ERR_RANGE_STR 2
#define ERR_NO_MANTISSA 3
#define ERR_RANGE_MANTISSA 4
#define ERR_ORDER_OVERFLOW 5
#define ERR_DIVISION_ZERO 6


/// @brief Выводит описание ошибки
/// @param rc 
void print_error(const int rc);

#endif
