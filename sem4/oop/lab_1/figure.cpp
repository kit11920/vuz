#include "figure.h"


figure_t start_init_figure()
{
    figure_t fig;
    start_init_points(fig.points);
    start_init_links(fig.links);
    return fig;
}

bool if_figure_init(figure_t &fig)
{
    return if_points_init(fig.points) && if_links_init(fig.links);
}

void free_data_figure(figure_t &fig)
{
    free_points(fig.points);
    free_links(fig.links);
}

/// @brief Считывает данные о фигуре из файла
static err_t read_figure(figure_t &figure, FILE *f)
{
    if (f == NULL)
        return ERR_PARAM;
    
    err_t rc = OK;
    rc = read_points(figure.points, f);
    if (rc == OK)
    {
        if (DEBUG)
        {
            printf("READ_FIGURE:\n");
            print_points(figure.points);
        }

        rc = read_links(figure.links, f);
        if (rc != OK)
            free_points(figure.points);

        if (DEBUG && rc == OK)
            print_links(figure.links);
    }
    return rc;
}

static bool check_figure(figure_t &figure)
{
    return check_links(figure.links, points_count(figure.points));
}

static err_t deep_copy_figure(figure_t &dst, figure_t &src)
{
    if (!if_figure_init(src))
        return ERR_PARAM;
    if (if_figure_init(dst))
        free_data_figure(dst);

    err_t rc = deep_copy_points(dst.points, src.points);
    if (rc == OK)
    {
        rc = deep_copy_links(dst.links, src.links);
        if (rc != OK)
            free_points(dst.points);
    }
    return rc;
}

// static void shallow_copy_figure(figure_t &dst, figure_t &src)
// {
//     if (if_figure_init(dst))
//         free_data_figure(dst);
//     dst = src;
// }

err_t load_figure(figure_t *figure, const char *filename)
{
    err_t rc = OK;
    errno = 0;
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        rc = errno_to_myerr(errno);
    else
    {
        figure_t tmp_figure = start_init_figure();
        rc = read_figure(tmp_figure, f);
        fclose(f);

        if (rc == OK)
        {
            if (!check_figure(tmp_figure))
                rc = ERR_DATA;
            else
                rc = deep_copy_figure(*figure, tmp_figure);
        }       
    }
    return rc;
}

err_t draw_figure(figure_t &figure, draw_data_t &data)
{
    if (!if_figure_init(figure))
        return ERR_FIGURE_NOT_LOADED;

    return draw_figure_points(data, figure.points, figure.links);
}

err_t shift_figure(figure_t &figure, shift_data_t &data)
{
    return shift_figure_points(figure.points, data);
}

err_t rotate_figure(figure_t &fig, rotate_data_t &data)
{
    return rotate_figure_points(fig.points, data);
}

err_t scale_figure(figure_t &fig, scale_data_t &data)
{
    return scale_figure_points(fig.points, data);
}