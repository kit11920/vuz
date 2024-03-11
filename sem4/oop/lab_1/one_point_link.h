#pragma once

#include <stdio.h>
#include "errors.h"
/* included
one_point_link.cpp
points_links.h
change_point.h
*/

// 1 точка
typedef struct point_s point_t;
struct point_s
{
    double x;
    double y;
    double z;
};

typedef struct link_s link_t;
struct link_s
{
    size_t beg;
    size_t end;
};

void print_one_point(point_t &p);

void print_one_link(link_t &link);

void free_points_arr(point_t *arr);

void free_links_arr(link_t *arr);

err_t read_one_point(point_t &point, FILE *f);

err_t read_point_index_arr(point_t *arr, size_t len_arr, size_t ind, FILE *f);

/// @brief Считывает количество чего либо из файла
err_t read_count(size_t &len, FILE *f);

err_t set_links_index_arr(link_t *arr, size_t len_arr, size_t index, link_t &newlink);

bool check_range_link_index_arr(link_t *arr, size_t index, size_t max_val);

// err_t get_point_by_index(point_t *arr, size_t len_arr, size_t index, point_t *point);

point_t *get_point_by_index(point_t *arr, size_t len, size_t index);

link_t *get_link_by_index(link_t *arr, size_t len, size_t index);

// void set_one_link(link_t &link, size_t beg, size_t end);

