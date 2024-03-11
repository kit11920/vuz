#include "errors.h"

void show_err_file(int errno_num)
{
    const char *msg = strerror(errno_num);
    QMessageBox :: warning(NULL, "Ошибка открытия файла", msg);
}

void show_err(err_t err)
{
    switch(err)
    {
        case ERR_FILE_ACCES:
            show_err_file(ERR_FILE_ACCES);
            break;
        case ERR_FILE_BUSY:
            show_err_file(ERR_FILE_BUSY);
            break;
        case ERR_FILE_MANY_OPEN:
            show_err_file(ERR_FILE_MANY_OPEN);
            break;
        case ERR_FILE_NO:
            show_err_file(ERR_FILE_NO);
            break;
        case ERR_DATA:
            QMessageBox :: warning(NULL, "Ошибка", "Ошибка ввода данных, убедитесть в корректности содежимого файла с данными");
            break;
        case ERR_MEM_ALLOC:
            QMessageBox :: warning(NULL, "Ошибка", "Ошибка выделения памяти");
            break;
        case ERR_FIGURE_NOT_LOADED:
            QMessageBox :: warning(NULL, "Ошибка", "Данные о фигуре еще не загружены");
            break;
        case ERR_SELECT_COLOR:
            QMessageBox :: warning(NULL, "Ошибка", "Ошибка выбора цвета");
            break;
        case ERR_ACT_NO:
            QMessageBox :: warning(NULL, "Ошибка в коде", "Попытка выполнить действие NO");
            break;
        default:
            QMessageBox :: warning(NULL, "Ошибка", "Ошибка не определена");
            break;
    }
}

err_t errno_to_myerr(int errno_num)
{
    err_t rc = ERR_UNKNOWN;
    switch (errno_num)
    {
        case 0:
            rc = OK;
            break;
        case ETXTBSY:
            rc = ERR_FILE_BUSY;
            break;
        case ENOENT:
            rc = ERR_FILE_NO;
            break;
        case EACCES:
            rc = ERR_FILE_ACCES;
            break;
        case ENFILE:
            rc = ERR_FILE_MANY_OPEN;
            break;
        default:
            break;
    }
    return rc;
}