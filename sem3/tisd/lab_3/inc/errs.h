#ifndef ERRS_H__
#define ERRS_H__

#define OK 0
#define ERR_IO 1
#define ERR_MEM 2
#define ERR_NUM_ACT_INPUT 3
#define ERR_COUNT_REPEAT_TIME_SMALL 4
#define ERR_RANGE 5



/// @brief Выводит описание ошибки
/// @param [in] rc - код ошибки
void print_err(int rc);


#endif
