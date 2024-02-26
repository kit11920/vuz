#include "errors.h"


void show_err(err_t err)
{
    switch(err)
    {
        case ERR_FILE_OPEN:
            QMessageBox :: warning(NULL, "Ошибка", "Ошибка открытия файла с данными");
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
        default:
            QMessageBox :: warning(NULL, "Ошибка", "Ошибка не определена");
            break;
    }
}
