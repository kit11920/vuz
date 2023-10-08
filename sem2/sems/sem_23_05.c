/*
В двоичном файле хранится информация о книгах, которая в себя включает название
(строку не более чем из 15 символов) и год издания (1900 <= year <= 2024)
Необходимо реализоватать программу, которая добавляет информацию о книгах в конец строки (
инф вводится пользователем)

app.exe a books.bin добавление информации
app.exe p books.bin вывод информации
item #0
book # 1
2002

item # 1
super book
2005

*/

#define _GNU_SOURSE

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define STR_LEN 15

#define OK 1
#define ERR_IO 1
#define ERR_RANGE 2

struct book_t
{
    char title[STR_LEN + 1];
    int year;
};


int book_input(struct book_t *book);

void book_print(const struct book_t *book);

void fb_print(FILE *f);

int fb_add(FILE *f, const struct book_t *book);

int fb_get_by_pos(FILE *f, long pos, struct book_t *book);
    // pos - это индекс, не смещение в файле

int fb_put_by_pos(FILE *f, long pos, const struct book_t *book);


int fb_del(FILE *f, long pos);




int fb_del(FILE *f, long n)
{
    struct book_t book;
    long size;
    int rc = OK;

    if (fseek(f, 0, SEEK_END) != 0)
        return ERR_IO;
    size = ftell(f);
    if (size == -1L)
        return ERR_IO;

    size = size / sizeof(struct book_t);
    if (n < 0 || n >= size)
        return ERR_RANGE;

    for (long i = n + 1; rc == OK && i < size; i++)
    {
        rc = fb_get_by_pos(f, i, &book);
        if (rc == OK)
            rc = fb_put_by_pos(f, i - 1, &book);

        if (rc == OK)
        {
            // fileno(f) - возвращает числовой описатель файла
            // (size - 1) * sizeof(book) - новый размер файла
            if (ftruncate(fileno(f), (size - 1) * sizeof(book)) != 0)
                return ERR_IO;
        }
    }



    printf("%d", errno);
    return rc;
}


int fb_get_by_pos(FILE *f, long pos, struct book_t *book)
{
    if (fseek(f, pos * sizeof(*book), SEEK_SET) != 0)
        return ERR_IO;

    if (fread(book, sizeof(*book), 1, f) != 1)
        return ERR_IO;

    return OK;
}

int fb_put_by_pos(FILE *f, long pos, const struct book_t *book)
{
    if (fseek(f, pos * sizeof(*book), SEEK_SET) != 0)
        return ERR_IO;

    if (fwrite(book, sizeof(*book), 1, f) != 1)
        return ERR_IO;

    return OK;
}


void fb_print(FILE *f)
{
    struct book_t book;
    size_t n = 0;
    while (fread(&book, sizeof(book), 1, f) == 1)
    {
        printf("Item %zu\n", n);
        book_print(&book);
        n++;
    }
}

int fb_add(FILE *f, const struct book_t *book)
{
    if (fseek(f, 0, SEEK_END) != 0)
        return ERR_IO;

    if (fwrite(book, sizeof(*book), 1, f) != 1)
        return ERR_IO;

    return OK;
}


int book_input(struct book_t *book)
{
    char str[STR_LEN + 1];
    size_t len;
    int year;
    char tmp[2];

    printf("Input title: \n");
    if (!fgets(str, sizeof(str), stdin))
        return ERR_IO;
    len = strlen(str);
    if (str[len - 1] == '\n')
    {
        str[len - 1] = 0;
        len--;
    }
    else
        return ERR_RANGE;

    if (!len)
        return ERR_RANGE;

    if (scanf("%d", &year) != 1)
        return ERR_IO;

    if (year < 1900 || year > 2024)
        return ERR_RANGE;

    fgets(tmp, sizeof(tmp), stdin);

    // заполняем всю структуру 0
    memset(book, 0, sizeof(*book));

    strcpy(book->title, str);
    book->year = year;

    return OK;
}


void book_print(const struct book_t *book)
{
    printf("Title: %s\n", book->title);
    printf("Year: %d\n", book->year);
    printf("\n");
}













