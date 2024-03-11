#ifndef ERRORS_H__
#define ERRORS_H__

#include <QMessageBox>
#include <string.h>
#include <errno.h>
/* included
errors.cpp
one_point_link.h
*/

#define DEBUG 1

enum Errors
{
    OK = 0,
    ERR_DATA = -1,
    ERR_MEM_ALLOC = -2,
    ERR_FIGURE_NOT_LOADED = -3,
    ERR_ACT_NO = -4,
    ERR_PARAM = -5,
    ERR_SELECT_COLOR = -6,
    ERR_UNKNOWN = -7,

    ERR_FILE_NO = ENOENT,
    ERR_FILE_ACCES = EACCES,
    ERR_FILE_BUSY = ETXTBSY,
    ERR_FILE_MANY_OPEN = ENFILE
};
typedef enum Errors err_t;


/// @brief Вызывает окно ошибки с ее описанием
/// @param err код ошибки
void show_err(err_t err);

err_t errno_to_myerr(int errno_num);

void show_err_file(int errno_num);


#endif // ERRORS_H__