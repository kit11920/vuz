#ifndef ERRS_H__
#define ERRS_H__

#define OK 0
#define ERR_DATA 1
#define ERR_MEM 2
#define ERR_NODE_EXIST 3
#define ERR_FILE 4


#define ERR_NOT_FOUND 5
#define ERR_COUNT_REPEAT_TIME_SMALL 6
#define ERR_NUM_ACT_INPUT 7
#define ERR_EMPTY_TREE 8

/// @brief Выводит описание ошибки
/// @param [in] rc - код ошибки
void print_err(int rc);







#endif
