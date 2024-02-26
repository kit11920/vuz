#pragma once

#include "errors.h"
#include "data_figure.h"
#include "ui_main_window.h"


/// @brief Рисует фигуру
/// @param scene сцена
/// @param figure данные о фигуре
/// @return код ошибки
err_t draw_figure(QGraphicsScene &scene, figure_t &figure);

/// @brief Сдвигает фигуру
/// @param points точки фигуры
/// @param dx сдвиг по x
/// @param dy сдвиг по y
/// @param dz сдвиг по z
/// @return код ошибки
err_t shift_figure(points_arr_t &points, double dx, double dy, double dz);

/// @brief Вращает фигуру относительно точки центра
/// @param points точки фигуры 
/// @param center точка центра
/// @param x_grad угол вращения относительно OX в градусах
/// @param y_grad гол вращения относительно OY в градусах
/// @param z_grad гол вращения относительно OZ в градусах
/// @return код ошибки
err_t rotate_figure(points_arr_t &points, point_t &center, double x_grad, double y_grad, double z_grad);

/// @brief Масштабирует фигуру относительно точки центра
/// @param points точки фигуры 
/// @param center точка центра
/// @param kx коэффицен масштабирования по x
/// @param ky коэффицен масштабирования по y
/// @param kzкоэффицен масштабирования по z
/// @return код ошибки
err_t scale_figure(points_arr_t &points, point_t &center, double kx, double ky, double kz);