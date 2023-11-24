#ifndef ERRS_H__
#define ERRS_H__

#define OK 0
#define ERR_DATA 1
#define ERR_MEM 2
#define ERR_NODE_EXIST 3
#define ERR_FILE 4

/// @brief Выводит описание ошибки
/// @param [in] rc - код ошибки
void print_err(int rc);







#endif
