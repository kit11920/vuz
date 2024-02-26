#include "data_figure.h"

#ifndef DEBUG
#define DEBUG 1
#endif


/// @brief Выделяет память под массив структуры points_arr_t
static err_t alloc_points_arr(points_arr_t &pa, size_t len)
{
    if (len == 0)
        return ERR_PARAM;
    pa.len = len;
    pa.arr = (point_t *) malloc(sizeof(point_t) * len);
    if (pa.arr == NULL)
        return ERR_MEM_ALLOC;
    return OK;
}

/// @brief Выделяет память под массив структуры links_arr_t
static err_t alloc_links_arr(links_arr_t &la, size_t len)
{
    const int count_cols = 2;
    if (len == 0)
        return ERR_PARAM;
    la.len = len;
    la.arr = (size_t **) malloc(sizeof(size_t *) * len + sizeof(size_t) * len * count_cols);
    if (la.arr == NULL)
        return ERR_MEM_ALLOC;

    size_t *data = (size_t *) (la.arr + len);
    for (size_t i = 0; i < len; i++)
        la.arr[i] = data + i * count_cols;

    return OK;
}

void start_init_figure(figure_t &fig)
{
    fig.points.arr = NULL;
    fig.points.len = 0;
    fig.links.arr = NULL;
    fig.points.len = 0;
}

void free_data_figure(figure_t &fig)
{
    free(fig.points.arr);
    free(fig.links.arr);
}

/// @brief Считывает количество чего либо из файла
static err_t read_count(FILE *f, size_t &len)
{
    if (f == NULL)
        return ERR_PARAM;

    int tmplen;
    if (fscanf(f, "%d", &tmplen) == 1 && tmplen > 0)
        len = (size_t) tmplen;
    else
        return ERR_DATA;
    return OK;
}

void print_points(points_arr_t &points)
{
    printf("points_arr_t:\n");
    if (points.len > 0 && points.arr != NULL)
        for (size_t i = 0; i < points.len; i++)
            printf("(%.2f %.2f %.2f)\n", points.arr[i].x, points.arr[i].y, points.arr[i].z);
    printf("\n");
}

/// @brief Считывает массив точек из файла
static err_t read_points(FILE *f, points_arr_t &points)
{
    if (f == NULL)
        return ERR_PARAM;
    
    err_t rc = OK;
    if ((rc = read_count(f, points.len)) != OK)
        return rc;
    
    if ((rc = alloc_points_arr(points, points.len)) != OK)
        return rc;

    for (size_t i = 0; i < points.len && rc == OK; i++)
        if (fscanf(f, "%lf%lf%lf", &points.arr[i].x, &points.arr[i].y, &points.arr[i].z) != 3)
            rc = ERR_DATA;
    if (rc != OK)
    {
        free(points.arr);
        points.len = 0;
    }

    return rc;
}

void print_links(links_arr_t &links)
{
    printf("links_arr_t:\n");
    if (links.len > 0 && links.arr != NULL)
        for (size_t i = 0; i < links.len; i++)
            printf("%zu - %zu\n", links.arr[i][0], links.arr[i][1]);
    printf("\n");
}

/// @brief Считывает массив связей из файла
static err_t read_links(FILE *f, figure_t &fig)
{
    if (f == NULL)
        return ERR_PARAM;
    
    err_t rc = OK;
    if ((rc = read_count(f, fig.links.len)) != OK)
        return rc;

    if ((rc = alloc_links_arr(fig.links, fig.links.len)) != OK)
        return rc;
    
    int begtmp, endtmp;
    for (size_t i = 0; i < fig.links.len && rc == OK; i++)
        if (fscanf(f, "%d%d", &begtmp, &endtmp) != 2 
        || begtmp < 0 || endtmp < 0 || 
        (size_t) begtmp >= fig.points.len || (size_t) endtmp >= fig.points.len)
            rc = ERR_DATA;
        else
        {
            fig.links.arr[i][0] = begtmp;
            fig.links.arr[i][1] = endtmp;
        }
    
    if (rc != OK)
    {
        free(fig.links.arr);
        fig.links.len = 0;
    }
    return rc;
}

/// @brief Считывает данные о фигуре из файла
static err_t read_figure(FILE *f, figure_t &figure)
{
    if (f == NULL)
        return ERR_PARAM;
    
    err_t rc = OK;
    rc = read_points(f, figure.points);
    if (rc == OK)
    {
#if DEBUG
    printf("READ_FIGURE:\n");
    print_points(figure.points);
#endif
        rc = read_links(f, figure);
#if DEBUG && rc == OK
        print_links(figure.links);
#endif
        if (rc != OK)
        {
            free(figure.points.arr);
            figure.points.len = 0;
        }
    }
    return rc;
}

err_t load_figure(const char *filename, figure_t &figure)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        return ERR_FILE_OPEN;

    figure_t tmp_figure;
    start_init_figure(tmp_figure);
    err_t rc = read_figure(f, tmp_figure);

    if (rc == OK)
        figure = tmp_figure;

    fclose(f);
    return rc;
}
