#ifndef ERRORS_H__
#define ERRORS_H__

#include <QMessageBox>

// #define DEBUG 0

enum Errors
{
    OK,
    ERR_FILE_OPEN,
    ERR_DATA,
    ERR_MEM_ALLOC,
    ERR_FIGURE_NOT_LOADED,
    ERR_UNKNOWN,

    ERR_PARAM
};
typedef enum Errors err_t;


/// @brief Вызывает окно ошибки с ее описанием
/// @param err код ошибки
void show_err(err_t err);


#endif // ERRORS_H__