/*
Задан текстовый файл.
В нем хранятся строки.
Длина строки не превышает 127 символов.
Найти строку, которая нач и заканчивается одним сомволом,
максимальной длины и вывести на экран
*/

#include <stdio.h>
#include <string.h>

#define MAX_LEN (127 + 1)

#define OK 0
#define ERR_NOT_FOUM 1
#define ERR_IO 2

int process_file(FILE *f, char *str)
{
    char str_work[MAX_LEN];
    size_t len, max_len = 0;

    while (fgets(str_work, sizeof(str_work), f))
    {
        len = strlen(str_work);
        if (str_work[len - 1] == '\n')
        {
            str_work[len - 1] = '\0';
            len--;
        }

        if (len && str_work[0] == str_work[len - 1] && max_len < len)
        {
            max_len = len;
            strcpy(str, str_work);
        }
    }

    if (max_len == 0)
        return ERR_NOT_FOUM;


    return OK;
}


int main(int argc, char **argv)
{
    FILE *f;
    char str[MAX_LEN];
    int rc = OK;

    printf("%d", argc);
    if (argc != 2)
    {
        fprintf(stderr, "app.exe file_name\n");
        return ERR_IO;
    }

    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Caon not open file\n");
        return ERR_IO;
    }

    // НАЧИНАЯ С ЭТОГО МОМЕНТА МОЖЕТ БЫТЬ ТОЛЬКО ОДНА ТОЧКА ВЫХОДА Т К ФАЙЛ ОТКРЫТ

    rc = process_file(f, str);
    if (rc == OK)
        printf("Result: %s\n", str);
    else
        fprintf(stderr, "process_file_error %d\n", rc);

    fclose(f);

    return rc;
}



















