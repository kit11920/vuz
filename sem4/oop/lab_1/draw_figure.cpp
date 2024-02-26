#include <math.h>
#include "draw_figure.h"

#ifndef DEBUG
#define DEBUG 1
#endif

err_t draw_figure(QGraphicsScene &scene, figure_t &figure)
{
    if (figure.points.arr == NULL || figure.points.len == 0 || 
    figure.links.arr == NULL || figure.links.len == 0)
        return ERR_PARAM;

#if DEBUG
    printf("DRAW FIGURE:\n");
    print_points(figure.points);
    puts("");
#endif

    QPen pen(Qt::darkBlue, 3);

    point_t beg_point, end_point;
    for (size_t i = 0; i < figure.links.len; i++)
    {
        beg_point = figure.points.arr[figure.links.arr[i][0]];
        end_point = figure.points.arr[figure.links.arr[i][1]];
        scene.addLine(beg_point.x, beg_point.y, end_point.x, end_point.y, pen);
    }

    return OK;
}

err_t shift_figure(points_arr_t &points, double dx, double dy, double dz)
{
    if (points.len == 0 || points.arr == NULL)
        return ERR_PARAM;

    for (size_t i = 0; i < points.len; i++)
    {
        points.arr[i].x += dx;
        points.arr[i].y += dy;
        points.arr[i].z += dz;
    }

    return OK;
}

/// @brief Переводит градусы в радианы
static inline double rad(double grad)
{
    return grad * M_PI / 180;
}

/// @brief Вращает точку относительно оси ОХ на alpha градусов
static void ox_rotate_point(point_t &point, double alpha)
{
    if (alpha == 0)
        return;
    double sin_alpha = sin(rad(alpha));
    double cos_alpha = cos(rad(alpha));
    double ytmp;
    ytmp = point.y;

    point.y = point.y * cos_alpha + point.z * sin_alpha;
    point.z = - ytmp * sin_alpha + point.z * cos_alpha;
}

/// @brief Вращает точку относительно оси ОY на alpha градусов
static void oy_rotate_point(point_t &point, double alpha)
{
    if (alpha == 0)
        return;
    double sin_alpha = sin(rad(alpha));
    double cos_alpha = cos(rad(alpha));
    double xtmp;
    xtmp = point.x;

    point.x = point.x * cos_alpha + point.z * sin_alpha;
    point.z = - xtmp * sin_alpha + point.z * cos_alpha;
}

/// @brief Вращает точку относительно оси ОZ на alpha градусов
static void oz_rotate_point(point_t &point, double alpha)
{
    if (alpha == 0)
        return;
    double sin_alpha = sin(rad(alpha));
    double cos_alpha = cos(rad(alpha));
    double xtmp;
    xtmp = point.x;

    point.x = point.x * cos_alpha + point.y * sin_alpha;
    point.y = - xtmp * sin_alpha + point.y * cos_alpha;
}

/// @brief Вращает точку относительно точки центра
static void rotate_point(point_t &point, point_t &center, double x_grad, double y_grad, double z_grad)
{
    point.x -= center.x;
    point.y -= center.y;
    point.z -= center.z;

    ox_rotate_point(point, x_grad);
    oy_rotate_point(point, y_grad);
    oz_rotate_point(point, z_grad);

    point.x += center.x;
    point.y += center.y;
    point.z += center.z;
}

err_t rotate_figure(points_arr_t &points, point_t &center, double x_grad, double y_grad, double z_grad)
{
    if (points.len == 0 || points.arr == NULL)
        return ERR_FIGURE_NOT_LOADED;
    if (x_grad == 0 && y_grad == 0 && z_grad == 0)
        return OK;
    
    for (size_t i = 0; i < points.len; i++)
        rotate_point(points.arr[i], center, x_grad, y_grad, z_grad);
    
    return OK;
}

/// @brief Масштабирует точку относительно точки центра
static void scale_point(point_t &point, point_t &center, double kx, double ky, double kz)
{
    point.x -= center.x;
    point.y -= center.y;
    point.z -= center.z;

    point.x *= kx;
    point.y *= ky;
    point.z *= kz;

    point.x += center.x;
    point.y += center.y;
    point.z += center.z;
}

err_t scale_figure(points_arr_t &points, point_t &center, double kx, double ky, double kz)
{
    if (points.len == 0 || points.arr == NULL)
        return ERR_FIGURE_NOT_LOADED;
    if (kx == 1 && ky == 1 && kz == 1)
        return OK;
    
    for (size_t i = 0; i < points.len; i++)
        scale_point(points.arr[i], center, kx, ky, kz);
    
    return OK;
}






