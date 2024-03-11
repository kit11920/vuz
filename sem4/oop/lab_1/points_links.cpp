
#include "points_links.h"



void start_init_points(points_arr_t &points)
{
    points.arr = NULL;
    points.len = 0;
}

void start_init_links(links_arr_t &links)
{
    links.arr = NULL;
    links.len = 0;
}

bool if_points_init(points_arr_t &points)
{
    return points.len > 0 && points.arr != NULL;
}

bool if_links_init(links_arr_t &links)
{
    return links.arr != NULL && links.len > 0;
}

err_t alloc_points_arr(point_t **arr, size_t len)
{
    if (len == 0)
        return ERR_PARAM;

    err_t rc = OK;
    point_t *tmp_arr = (point_t *) malloc(sizeof(point_t) * len);
    if (tmp_arr == NULL)
        rc = ERR_MEM_ALLOC;
    else
        *arr = tmp_arr;
    return rc;
}

err_t alloc_links_arr(link_t **arr, size_t len)
{
    if (len == 0)
        return ERR_PARAM;

    err_t rc = OK;
    link_t *tmp_arr = (link_t *) malloc(sizeof(link_t) * len);
    if (tmp_arr == NULL)
        rc = ERR_MEM_ALLOC; 
    else
        *arr = tmp_arr;

    return rc;
}

void free_points(points_arr_t &points)
{
    free_points_arr(points.arr);
}

void free_links(links_arr_t &links)
{
    free_links_arr(links.arr);
}

void print_points(points_arr_t &points)
{
    printf("points_arr_t:\n");
    if (if_points_init(points))
        for (size_t i = 0; i < points.len; i++)
            print_one_point(points.arr[i]);
    printf("\n");
}

void print_links(links_arr_t &links)
{
    printf("links_arr_t:\n");
    if (if_links_init(links))
        for (size_t i = 0; i < links.len; i++)
            print_one_link(links.arr[i]);
    printf("\n");
}

// static err_t read_count_points(points_arr_t &points, FILE *f)
// {
//     return read_count(points.len, f);
// }

static err_t just_read_points(point_t *arr, size_t len, FILE *f)
{
    err_t rc = OK;
    for (size_t i = 0; rc == OK && i < len; i++)
    {
        rc = read_point_index_arr(arr, len, i, f);
        // более лаконичный вариант
        // rc = read_one_point(points.arr[i], f);
    }
    return rc;
}

err_t read_points(points_arr_t &points, FILE *f)
{
    if (f == NULL)
        return ERR_PARAM;
    
    err_t rc = OK;      
    if ((rc = read_count(points.len, f)) == OK)
        if ((rc = alloc_points_arr(&points.arr, points.len)) == OK)  
        {
            rc = just_read_points(points.arr, points.len, f);
            if (rc != OK)
                free_points_arr(points.arr);
        }

    return rc;
}

// static err_t read_count_links(links_arr_t &links, FILE *f)
// {
//     return read_count(links.len, f);
// }

static err_t just_read_links(link_t *arr, size_t len, FILE *f)
{
    err_t rc = OK;
    int begtmp, endtmp;
    for (size_t i = 0; rc == OK && i < len; i++)
    {
        if (fscanf(f, "%d%d", &begtmp, &endtmp) != 2 || begtmp < 0 || endtmp < 0)
            rc = ERR_DATA;
        else
        {
            link_t new_link; 
            new_link.beg = begtmp;
            new_link.end = endtmp;
            rc = set_links_index_arr(arr, len, i, new_link);
            // более лаконичный вариант
            // links.arr[i] = new_link;
        }
    }
    return rc;
}

err_t read_links(links_arr_t &links, FILE *f)
{
    if (f == NULL)
        return ERR_PARAM;
    
    err_t rc = OK;
    if ((rc = read_count(links.len, f)) == OK)
        if ((rc = alloc_links_arr(&links.arr, links.len)) == OK)
        {
            rc = just_read_links(links.arr, links.len, f);
            if (rc != OK)
                free_links_arr(links.arr);
        }
    return rc;
}

bool check_links(links_arr_t &links, size_t count_points)
{
    bool good_links = true;
    for (size_t i = 0; good_links && i < links.len; i++)
        good_links = check_range_link_index_arr(links.arr, i, count_points - 1);
    return good_links;
}

err_t deep_copy_points(points_arr_t &dst, points_arr_t &src)
{
    if (!if_points_init(src))
        return ERR_PARAM;
    if (if_points_init(dst))
        free_points(dst);

    dst.len = src.len;
    err_t rc = alloc_points_arr(&dst.arr, dst.len);
    if (rc == OK)
        memcpy(dst.arr, src.arr, dst.len * sizeof(point_t));
    return rc;
}

err_t deep_copy_links(links_arr_t &dst, links_arr_t &src)
{
    if (!if_links_init(src))
        return ERR_PARAM;
    if (if_links_init(dst))
        free_links(dst);

    dst.len = src.len;
    err_t rc = alloc_links_arr(&dst.arr, dst.len);
    if (rc == OK)
        memcpy(dst.arr, src.arr, dst.len * sizeof(link_t)); // данные не пересекаются т к malloc
    return rc;
}

size_t points_count(points_arr_t &points)
{
    return points.len;
}

size_t links_count(links_arr_t &links)
{
    return links.len;
}

static err_t draw_line_by_link(draw_data_t &data, points_arr_t &points, link_t &link)
{
    err_t rc = OK;
    point_t *begp, *endp;
    begp = get_point_by_index(points.arr, points.len, link.beg);
    endp = get_point_by_index(points.arr, points.len, link.end);
    if (begp == NULL || endp == NULL)
        rc = ERR_DATA;
    else
        draw_line_by_point(data, *begp, *endp);

    return rc;
}

err_t draw_figure_points(draw_data_t &data,  points_arr_t &points, links_arr_t &links)
{
    if (!if_points_init(points) || !if_links_init(links))
        return ERR_FIGURE_NOT_LOADED;

    if (DEBUG)
    {
        printf("DRAW FIGURE:\n");
        print_points(points);
        puts("");
    }

    // link_t *link = NULL;
    err_t rc = OK;
    for (size_t i = 0; rc == OK && i < links.len; i++)
    {
        rc = draw_line_by_link(data, points, links.arr[i]);
        // link = get_link_by_index(links.arr, links.len, i);
        // if (link == NULL)
        //     rc = ERR_DATA;
        // else
        //     rc = draw_line_by_link(data, points, *link);
    }

    return rc;
}

err_t shift_figure_points(points_arr_t &points, shift_data_t &data)
{
    if (!if_points_init(points))
        return ERR_FIGURE_NOT_LOADED;

    err_t rc = OK;
    // point_t *ppoint;
    for (size_t i = 0; rc == OK && i < points.len; i++)
    {
        // более лаконичный вариант
        shift_point(points.arr[i], data);
        // ppoint = get_point_by_index(points.arr, points.len, i);
        // if (ppoint == NULL)
        //     rc = ERR_DATA;
        // else
        //     shift_point(*ppoint, data);

    }

    return rc;
}

err_t rotate_figure_points(points_arr_t &points, rotate_data_t &data)
{
    if (points.len == 0 || points.arr == NULL)
        return ERR_FIGURE_NOT_LOADED;
    if (data.x_grad == 0 && data.y_grad == 0 && data.z_grad == 0)
        return OK;
    
    err_t rc = OK;
    // point_t *ppoint;
    for (size_t i = 0; i < points.len; i++)
    {
        // более лаконичный вариант
        rotate_point(points.arr[i], data);
        // ppoint = get_point_by_index(points.arr, points.len, i);
        // if (ppoint == NULL)
        //     rc = ERR_DATA;
        // else
        //     rotate_point(*ppoint, data);
    }
    
    return rc;
}

err_t scale_figure_points(points_arr_t &points, scale_data_t &data)
{
    if (points.len == 0 || points.arr == NULL)
        return ERR_FIGURE_NOT_LOADED;
    if (data.kx == 1 && data.ky == 1 && data.kz == 1)
        return OK;
    
    err_t rc = OK;
    // point_t *ppoint;
    for (size_t i = 0; i < points.len; i++)
    {
        // более лаконичный вариант
        scale_point(points.arr[i], data);
        // ppoint = get_point_by_index(points.arr, points.len, i);
        // if (ppoint == NULL)
        //     rc = ERR_DATA;
        // else
        //     scale_point(*ppoint, data);
    }
    
    return rc;
}
