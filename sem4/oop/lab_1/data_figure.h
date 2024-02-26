#ifndef DATA_FIGURE_H__
#define DATA_FIGURE_H__

#include <stdlib.h>
#include <stdio.h>
#include "errors.h"

// 1 точка
typedef struct point_s point_t;
struct point_s
{
    double x;
    double y;
    double z;
};

// массив точек фигуры и его размер
typedef struct points_arr_s points_arr_t;
struct points_arr_s
{
    point_t *arr;
    size_t len;
};

// массив индексов точек фигуры между которыми линия
typedef struct links_arr_s links_arr_t;
struct links_arr_s
{
    size_t **arr;
    size_t len;
};

// фигура, состоящая из точек и связей между ними
typedef struct figure_s figure_t;
struct figure_s
{
    points_arr_t points;
    links_arr_t links;
};

/// @brief Проводит начальную инициализацию нулями фигуры
/// @param fig фигура
void start_init_figure(figure_t &fig);

/// @brief Освобождает память из под данных фигуры 
/// @param fig - ссылка на фигуру
void free_data_figure(figure_t &fig);

/// @brief Выводит массив точек
/// @param points точки
void print_points(points_arr_t &points);

/// @brief Выводит массив соединений точек
/// @param links соединения
void print_links(links_arr_t &links);

/// @brief Определяет фигуру, выделяет поде неее память и заполняет данными из файла
/// @param filename строка- название файла
/// @param figure переменная которой присвоиться значение новой фигуры
/// @return код ошибки
err_t load_figure(const char *filename, figure_t &figure);










#endif // DATA_FIGURE_H__
