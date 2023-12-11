#ifndef ERRS_H__
#define ERRS_H__

#ifndef DEBUG
#define DBG_PRINT(s, ...) ((void) 0)
#else
#define DBG_PRINT(s, ...) printf(s, __VA_ARGS__)
#endif

#define OK 0
#define ERR_MEM 1
#define ERR_COUNT_V 2
#define ERR_COUNT_EDGE 3
#define ERR_EDGE 4
#define ERR_EXIST_EDGE 5
#define ERR_FILE 6
// #define ERR_NO_HAM_PATH 7
#define ERR_NO_EULER_PATH 7
#define ERR_NAME 8
#define ERR_COUNT_REPEAT_TIME_SMALL 9
#define ERR_NOT_CONNECTED 10
#define ERR_TYPE_GRAPH 11


/// @brief Выводит описание ошибки
/// @param [in] rc - код ошибки
/// @return код ошибки
int print_err(int rc);







#endif
