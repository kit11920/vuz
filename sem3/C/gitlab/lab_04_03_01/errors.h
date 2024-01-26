#ifndef ERRORS_H
#define ERRORS_H

#define OK 0
#define ERR_IO 1
#define ERR_BUF_TOO_SMALL 2
#define ERR_NO_DIFF_WORDS 4
#define ERR_ONLY_ONE_WORD 5
#define ERR_ONLY_DELIMS 6

/**
@brief Выводит описание ошибки по ее коду
@param
rc - код ошибки
*/
void print_error(int rc);

#endif // ERRORS_H
