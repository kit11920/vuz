#pragma once

#include "change_point.h"

/* included
points_links.h
figure.h
*/

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
    link_t *arr;
    size_t len;
};


void start_init_points(points_arr_t &points);

void start_init_links(links_arr_t &links);

bool if_points_init(points_arr_t &points);

bool if_links_init(links_arr_t &links);

/// @brief Выделяет память под массив структуры points_arr_t
err_t alloc_points_arr(point_t **arr, size_t len);

/// @brief Выделяет память под массив структуры links_arr_t
err_t alloc_links_arr(link_t **arr, size_t len);

void free_points(points_arr_t &points);

void free_links(links_arr_t &links);

/// @brief Выводит массив точек
/// @param points точки
void print_points(points_arr_t &points);

/// @brief Выводит массив соединений точек
/// @param links соединения
void print_links(links_arr_t &links);

/// @brief Считывает массив точек из файла
err_t read_points(points_arr_t &points, FILE *f);

/// @brief Считывает массив связей из файла
err_t read_links(links_arr_t &links, FILE *f);

bool check_links(links_arr_t &links, size_t count_points);

err_t deep_copy_points(points_arr_t &dst, points_arr_t &src);

err_t deep_copy_links(links_arr_t &dst, links_arr_t &src);

size_t points_count(points_arr_t &points);

size_t links_count(links_arr_t &links);

err_t connection_points_from_link(point_t *beg, point_t *end, points_arr_t &points, link_t &link);

err_t draw_figure_points(draw_data_t &data,  points_arr_t &points, links_arr_t &links);

err_t shift_figure_points(points_arr_t &points, shift_data_t &data);

err_t rotate_figure_points(points_arr_t &points, rotate_data_t &data);

err_t scale_figure_points(points_arr_t &points, scale_data_t &data);