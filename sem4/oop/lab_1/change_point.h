#pragma once

#include <QGraphicsScene>
#include "one_point_link.h"
/* included
draw_figure.h
*/

typedef struct draw_data_s draw_data_t;
struct draw_data_s
{
    QGraphicsScene *scene;
    QPen *pen;
};

typedef struct scale_data_s scale_data_t;
struct scale_data_s
{
    point_t center;
    double kx;
    double ky;
    double kz;
};

typedef struct rotate_data_s rotate_data_t;
struct rotate_data_s
{
    point_t center;
    double x_grad;
    double y_grad;
    double z_grad;
};

typedef struct shift_data_s shift_data_t;
struct shift_data_s
{
    double dx;
    double dy;
    double dz;
};


/// @brief Вращает точку относительно точки центра
void rotate_point(point_t &point, rotate_data_t &data);

void shift_point(point_t &point, shift_data_t &data);

/// @brief Масштабирует точку относительно точки центра
void scale_point(point_t &point, scale_data_t &data);

void draw_line_by_point(draw_data_t &data, point_t &beg_point, point_t &end_point);