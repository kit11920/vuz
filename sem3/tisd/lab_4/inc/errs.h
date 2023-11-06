#ifndef ERRS_H__
#define ERRS_H__

#define OK 0
#define ERR_RANGE_LONG 1
#define ERR_IO 2
#define ERR_RANGE_EMPTY 3
#define ERR_NUM_ACT_INPUT 4
#define ERR_MEM 5
#define ERR_COUNT_REPEAT_TIME_SMALL 6



/// @brief Выводит описание ошибки
/// @param rc - код ошибки
void print_err(int rc);

#endif
