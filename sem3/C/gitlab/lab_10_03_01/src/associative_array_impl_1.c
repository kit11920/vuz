#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "associative_array.h"
#include "impl_1_plus.h"


assoc_array_t assoc_array_create(void)
{
    assoc_array_t arr = malloc(sizeof(struct assoc_array_type));
    if (arr != NULL)
    {
        arr->real_len = 1;
        arr->len = 0;
        arr->step_increase = 2;

        // выделили память под указатель
        arr->data = malloc(sizeof(data_t *) * arr->real_len);
        if (arr->data == NULL)
        {
            free(arr);
            return NULL;
        }
        arr->data[0] = NULL;
    }
    return arr;
}


void assoc_array_destroy(assoc_array_t *arr)
{
    if (arr == NULL || (*arr) == NULL)
        return;
    assert(assoc_array_clear(*arr) == ASSOC_ARRAY_OK);
    free((*arr)->data);
    free(*arr);
    *arr = NULL;
}

// вставляет в отсортированный массив по возрастанию значения ключей
assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;

    int *tmp_num = NULL;
    if (assoc_array_find(arr, key, &tmp_num) == ASSOC_ARRAY_OK)
        return ASSOC_ARRAY_KEY_EXISTS;

    data_t *data = assoc_array_data_create(key, num);
    if (data == NULL)
        return ASSOC_ARRAY_MEM;

    assoc_array_insert_sorted_arr(arr, data);
    return ASSOC_ARRAY_OK;
}

// бинарный поиск
assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (arr == NULL || key == NULL || strlen(key) == 0 || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;
    
    assoc_array_error_t rc;
    size_t ind;
    rc = assoc_array_find_ind(arr, key, &ind);
    if (rc != ASSOC_ARRAY_OK)
        return rc;
    *num = &arr->data[ind]->num;

    return rc;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (arr == NULL || key == NULL || strlen(key) == 0)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    assoc_array_error_t rc;
    size_t ind = ASSOC_ARRAY_OK;
    rc = assoc_array_find_ind(arr, key, &ind);
    if (rc != ASSOC_ARRAY_OK)
        return rc;
    
    rc = assoc_array_data_ind_remove(arr, ind);
    
    return rc;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (arr == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    
    assoc_array_data_clear(arr);

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (arr == NULL || action == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->len; i++)
        action(arr->data[i]->key, &arr->data[i]->num, param);
    
    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &arr->data[0]->num;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (arr == NULL || num == NULL)
        return ASSOC_ARRAY_INVALID_PARAM;
    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &arr->data[arr->len - 1]->num;

    return ASSOC_ARRAY_OK;
}




