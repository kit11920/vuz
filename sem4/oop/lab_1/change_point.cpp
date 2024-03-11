#include <math.h>
#include "change_point.h"

void shift_point(point_t &point, shift_data_t &data)
{
    point.x += data.dx;
    point.y += data.dy;
    point.z += data.dz;
}

static void shift_center_to_zero(point_t &point, point_t &center)
{
    shift_data_t shift = {- center.x, - center.y, - center.z};
    shift_point(point, shift);
}

static void shift_center_to_center(point_t &point, point_t &center)
{
    shift_data_t shift = {center.x, center.y, center.z};
    shift_point(point, shift);
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
    double ytmp = point.y;

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
    double xtmp = point.x;

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
    double xtmp = point.x;

    point.x = point.x * cos_alpha + point.y * sin_alpha;
    point.y = - xtmp * sin_alpha + point.y * cos_alpha;
}

void rotate_point(point_t &point, rotate_data_t &data)
{
    shift_center_to_zero(point, data.center);

    ox_rotate_point(point, data.x_grad);
    oy_rotate_point(point, data.y_grad);
    oz_rotate_point(point, data.z_grad);

    shift_center_to_center(point, data.center);
}

static void just_scale_point(point_t &point, scale_data_t &data)
{
    point.x *= data.kx;
    point.y *= data.ky;
    point.z *= data.kz;
}

void scale_point(point_t &point, scale_data_t &data)
{
    shift_center_to_zero(point, data.center);

    just_scale_point(point, data);    

    shift_center_to_center(point, data.center);
}

void draw_line_by_point(draw_data_t &data, point_t &beg_point, point_t &end_point)
{
    data.scene->addLine(beg_point.x, beg_point.y, end_point.x, end_point.y, *data.pen);
}