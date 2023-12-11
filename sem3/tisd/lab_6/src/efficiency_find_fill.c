#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "tree.h"
#include "errs.h"
#include "fort.h"
#include "efficiency_find_fill.h"
#include "efficiency.h"

void full_arr_data_to_add(int l, int r, int *arr, size_t *len_arr, size_t max_len_arr)
{
    if (r - l == 1)
    {
        return;
    }
    else
    {
        int mid = l + (r - l) / 2;
        arr[*len_arr] = mid;
        (*len_arr)++;

        full_arr_data_to_add(l, mid, arr, len_arr, max_len_arr);
        full_arr_data_to_add(mid, r, arr, len_arr, max_len_arr);
    }
}

int make_arr_data_to_add(int **arr, size_t height, size_t *len_arr)
{
    size_t count_elems = (size_t) pow(2.0, (double) (height + 1)) - 1;
    *len_arr = count_elems;

    // printf("count_elems - %zu, height - %zu\n", count_elems);
    *arr = malloc(sizeof(int) * count_elems);
    if (*arr == NULL)
        return ERR_MEM;
    size_t len_arr_now = 0;
    full_arr_data_to_add(0, count_elems + 1, *arr, &len_arr_now, count_elems);

    return OK;
}

int fill_tree_based_data_arr(node_t **root, int *arr, size_t len_arr)
{
    int rc = OK;
    // printf("arr: ");
    for (size_t i = 0; i < len_arr; i++)
    {
        // printf("%d ", arr[i]);
        rc = add_node_bin_search_tree(root, arr[i]);
        if (rc != OK)
        {
            free_tree(root);
            return rc;
        }
    }
    // printf("\n");
    return OK;
}

int make_full_tree(node_t **root, size_t height)
{
    int rc = OK;
    int *arr;
    size_t len_arr;

    rc = make_arr_data_to_add(&arr, height, &len_arr);
    if (rc != OK)
        return rc;
    
    rc = fill_tree_based_data_arr(root, arr, len_arr);
    if (rc != OK)
        return rc;

    free(arr);
    return OK;
}

int make_half_full_tree(node_t **root, size_t height)
{
    int rc = OK;
    int *arr;
    size_t len_arr;

    rc = make_arr_data_to_add(&arr, height - 1, &len_arr);
    if (rc != OK)
        return rc;
    
    rc = add_node_bin_search_tree(root, arr[len_arr - 1] * 2);
    if (rc != OK)
        return rc;
    
    rc = fill_tree_based_data_arr(root, arr, len_arr);
    if (rc != OK)
        return rc;

    free(arr);
    return OK;
}

int make_left_tree(node_t **root, size_t height)
{
    int rc = OK;
    
    rc = add_node_bin_search_tree(root, height + 1);
    if (rc != OK)
        return rc;
    rc = add_node_bin_search_tree(root, height + 2);
    if (rc != OK)
        return rc;
    for (size_t i = height; i > 0; i--)
    {
        rc = add_node_bin_search_tree(root, (int) i);
        if (rc != OK)
        {
            free_tree(root);
            return rc;
        }
    }
    return OK;
}

int make_2branch_tree(node_t **root, size_t height)
{
    int rc = OK;
    
    rc = add_node_bin_search_tree(root, height);
    if (rc != OK)
        return rc;
    for (int i = height - 1; i >= 0; i--)
    {
        rc = add_node_bin_search_tree(root, (int) i);
        if (rc != OK)
        {
            free_tree(root);
            return rc;
        }
    }
    for (size_t i = height + 1; i <= height * 2; i++)
    {
        rc = add_node_bin_search_tree(root, (int) i);
        if (rc != OK)
        {
            free_tree(root);
            return rc;
        }
    }
    return OK;
}


unsigned long long fill_left_tree_measure_time(size_t height)
{
    unsigned long long beg, end;
    node_t *root = NULL;
    int rc = OK;

    beg = ms_now();
    rc = make_left_tree(&root, height);
    end = ms_now();
    assert(rc == OK);

    free_tree(&root);
    return end - beg;
}

unsigned long long find_left_tree_measure_time(size_t height)
{
    unsigned long long beg, end;
    node_t *root = NULL;
    int rc = OK;
    node_t *node, *parant;

    rc = make_left_tree(&root, height);
    assert(rc == OK);

    beg = ms_now();
    node = find_node_tree(root, 1, &parant);
    end = ms_now();
    assert(node != NULL);

    free_tree(&root);
    return end - beg;
}

unsigned long long fill_2branch_tree_measure_time(size_t height)
{
    unsigned long long beg, end;
    node_t *root = NULL;
    int rc = OK;

    beg = ms_now();
    rc = make_2branch_tree(&root, height);
    end = ms_now();
    assert(rc == OK);

    free_tree(&root);
    return end - beg;
}

unsigned long long find_2branch_tree_measure_time(size_t height)
{
    unsigned long long beg, end;
    node_t *root = NULL;
    int rc = OK;
    node_t *node, *parant;

    rc = make_2branch_tree(&root, height);
    assert(rc == OK);

    beg = ms_now();
    node = find_node_tree(root, height * 2, &parant);
    end = ms_now();
    assert(node != NULL);

    free_tree(&root);
    return end - beg;
}

unsigned long long fill_half_full_tree_measure_time(size_t height)
{
    unsigned long long beg, end;
    node_t *root = NULL;
    int *arr = NULL;
    size_t len_arr;
    int rc = OK;

    rc = make_arr_data_to_add(&arr, height - 1, &len_arr);
    if (rc != OK)
        return rc;

    beg = ms_now();
    add_node_bin_search_tree(&root, arr[len_arr - 1] + 10);
    rc = fill_tree_based_data_arr(&root, arr, len_arr);
    end = ms_now();
    assert(rc == OK);
    
    free(arr);
    free_tree(&root);
    return end - beg;
}

unsigned long long find_half_full_tree_measure_time(size_t height)
{
    unsigned long long beg, end;
    node_t *root = NULL;
    size_t len_arr = (size_t) pow(2.0, (double) (height + 1)) - 1;
    int rc = OK;
    node_t *node, *parant;

    rc = make_half_full_tree(&root, height);
    assert(rc == OK);

    int searching_data = (len_arr + 1) / 2 - 1; // элемент из последней ступени дерева в середине
    beg = ms_now();
    node = find_node_tree(root, searching_data, &parant);
    end = ms_now();
    assert(node != NULL);
    
    free_tree(&root);
    return end - beg;
}

unsigned long long fill_full_tree_measure_time(size_t height)
{
    unsigned long long beg, end;
    node_t *root = NULL;
    int *arr = NULL;
    size_t len_arr;
    int rc = OK;

    rc = make_arr_data_to_add(&arr, height, &len_arr);
    assert(rc == OK);

    beg = ms_now();
    rc = fill_tree_based_data_arr(&root, arr, len_arr);
    end = ms_now();
    assert(rc == OK);
    
    free(arr);
    free_tree(&root);
    return end - beg;
}

unsigned long long find_full_tree_measure_time(size_t height)
{
    unsigned long long beg, end;
    node_t *root = NULL;
    int *arr;
    size_t len_arr;
    int rc = OK;
    node_t *node, *parant;

    rc = make_arr_data_to_add(&arr, height, &len_arr);
    assert(rc == OK);

    rc = fill_tree_based_data_arr(&root, arr, len_arr);
    assert(rc == OK);

    int searching_data = (len_arr + 1) / 2 + 1; // элемент из последней ступени дерева в середине
    beg = ms_now();
    node = find_node_tree(root, searching_data, &parant);
    end = ms_now();
    assert(node != NULL);
    
    free(arr);
    free_tree(&root);
    return end - beg;
}

int gettime(measure_time_t measure, size_t height, unsigned long long *t, size_t len_t, long long *time)
{
    double rse = 100;

    size_t i = 0;
    rse = 100;
    while (i < len_t && (rse > 5 || i <= MIN_COUNT_REAPET))
    {
        t[i] = measure(height);
        rse = get_rse(t, i + 1);
        i++;
    }
    
    if (i >= len_t)
        return ERR_COUNT_REPEAT_TIME_SMALL;
    
    *time = (long long) get_tavg(t, i);
    
    return OK;
}

int make_compare_table_fill_find(void)
{
    int rc = OK;
    unsigned long long *t = NULL;
    int len_t = 500;
    long long fill_left_tree_time, find_in_left_tree_time, fill_2branch_tree_time, find_in_2branch_tree_time;
    long long fill_full_tree_time, find_in_full_tree_fime, fill_half_full_tree_time, find_in_half_full_tree_fime; 

    // Выделение памяти под вспомагательные структуры
    t = malloc(len_t * sizeof(unsigned long long));
    if (!t)
    {
        rc = ERR_MEM;
        return rc;
    }
    //

    printf("Подождите, идет обработка данных для таблицы 1...\n");
    // size_t beg = BEGIN, end = END, step = STEP;
    size_t beg = 2000, end = 4000, step = 500;
    ft_table_t *tab = ft_create_table();
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_printf_ln(tab, "height|fill left tree|find in left tree|fill 2branch tree|find in 2branch tree");

    for (size_t height = beg; height <= end; height += step)
    {
        rc = gettime(fill_left_tree_measure_time, height, t, len_t, &fill_left_tree_time);
        assert(rc == OK);

        rc = gettime(find_left_tree_measure_time, height, t, len_t, &find_in_left_tree_time);
        assert(rc == OK); 

        rc = gettime(fill_2branch_tree_measure_time, height, t, len_t, &fill_2branch_tree_time);
        assert(rc == OK);

        rc = gettime(find_2branch_tree_measure_time, height, t, len_t, &find_in_2branch_tree_time);
        assert(rc == OK);
 
        ft_printf_ln(tab, "%zu|%lld|%lld|%lld|%lld", 
        height, fill_left_tree_time, find_in_left_tree_time, fill_2branch_tree_time, find_in_2branch_tree_time);
    }
    printf("Таблица сравнения функции поиска в бинарном дереве поиска и заполнения его:\n");
    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);

    printf("Подождите, идет обработка данных для таблицы 2...\n");
    tab = ft_create_table();
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_printf_ln(tab, "height|fill\nleft tree|fill\n2branch tree|fill half\nfull tree|fill\nfull tree");

    beg = 12, end = 20, step = 2;
    for (size_t height = beg; height <= end; height += step)
    {
        rc = gettime(fill_left_tree_measure_time, height, t, len_t, &fill_left_tree_time);
        assert(rc == OK);

        rc = gettime(fill_2branch_tree_measure_time, height, t, len_t, &fill_2branch_tree_time);
        assert(rc == OK);

        rc = gettime(fill_half_full_tree_measure_time, height, t, len_t, &fill_half_full_tree_time);
        assert(rc == OK);

        rc = gettime(find_half_full_tree_measure_time, height, t, len_t, &find_in_half_full_tree_fime);
        assert(rc == OK);

        rc = gettime(fill_full_tree_measure_time, height, t, len_t, &fill_full_tree_time);
        assert(rc == OK);

        rc = gettime(find_full_tree_measure_time, height, t, len_t, &find_in_full_tree_fime);
        assert(rc == OK);
 
        ft_printf_ln(tab, "%zu|%lld|%lld|%lld|%lld", 
        height, fill_left_tree_time, fill_2branch_tree_time, fill_half_full_tree_time, fill_full_tree_time);
    }
    printf("Таблица сравнения времени работы функции заполнения бинарного дерева поиска \nв зависимости от его ветвистости:\n");
    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);


    free(t);
    return OK;
}










