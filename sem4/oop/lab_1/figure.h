#pragma once

#include <stdbool.h>
#include "points_links.h"

/* included
select_act.h
*/

// фигура, состоящая из точек и связей между ними
typedef struct figure_s figure_t;
struct figure_s
{
    points_arr_t points;
    links_arr_t links;
};

/// @brief Проводит начальную инициализацию нулями фигуры
figure_t start_init_figure();

/// @brief Определяет была ли проинициализированная фигура
/// @param fig фигура
/// @return true/false
bool if_figure_init(figure_t &fig);

/// @brief Освобождает память из под данных фигуры 
/// @param fig - ссылка на фигуру
void free_data_figure(figure_t &fig);

/// @brief Определяет фигуру, выделяет поде неее память и заполняет данными из файла
/// @param filename строка- название файла
/// @param figure переменная которой присвоиться значение новой фигуры
/// @return код ошибки
err_t load_figure(figure_t *figure, const char *filename);

err_t draw_figure(figure_t &figure, draw_data_t &data);

err_t shift_figure(figure_t &figure, shift_data_t &data);

err_t rotate_figure(figure_t &fig, rotate_data_t &data);

err_t scale_figure(figure_t &fig, scale_data_t &data);

