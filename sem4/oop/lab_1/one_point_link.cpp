
#include "one_point_link.h"


void print_one_point(point_t &p)
{
    printf("(%.2f %.2f %.2f)\n", p.x, p.y, p.z);
}

void print_one_link(link_t &link)
{
    printf("%zu - %zu\n", link.beg, link.end);
}

void free_points_arr(point_t *arr)
{
    free(arr);
}

void free_links_arr(link_t *arr)
{
    free(arr);
}

err_t read_one_point(point_t &point, FILE *f)
{
    if (fscanf(f, "%lf%lf%lf", &point.x, &point.y, &point.z) != 3)
        return ERR_DATA;
    return OK;
}

err_t read_point_index_arr(point_t *arr, size_t len_arr, size_t ind, FILE *f)
{
    if (ind >= len_arr)
        return ERR_PARAM;
    return read_one_point(arr[ind], f);
}

err_t read_count(size_t &len, FILE *f)
{
    if (f == NULL)
        return ERR_PARAM;

    int tmplen;
    err_t rc = OK;
    if (fscanf(f, "%d", &tmplen) == 1 && tmplen > 0)
        len = (size_t) tmplen;
    else
        rc = ERR_DATA;
    return rc;
}

err_t set_links_index_arr(link_t *arr, size_t len_arr, size_t index, link_t &newlink)
{
    if (index >= len_arr)
        return ERR_PARAM;
        
    arr[index] = newlink;
    return OK;
}

static bool check_range_one_link(link_t &link, size_t max_val)
{
    return link.beg <= max_val && link.end <= max_val;
}

bool check_range_link_index_arr(link_t *arr, size_t index, size_t max_val)
{
    return check_range_one_link(arr[index], max_val);
}

point_t *get_point_by_index(point_t *arr, size_t len, size_t index)
{
    if (index >= len)
        return NULL;

    return &arr[index];
}

link_t *get_link_by_index(link_t *arr, size_t len, size_t index)
{
    if (index >= len)
        return NULL;

    return &arr[index];
}

