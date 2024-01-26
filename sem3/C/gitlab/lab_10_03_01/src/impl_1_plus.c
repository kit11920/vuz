#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "associative_array.h"
#include "impl_1_plus.h"


data_t *assoc_array_data_create(const char *key, int num)
{
    data_t *data = malloc(sizeof(data_t));
    if (data == NULL)
        return NULL;;
    data->key = key;
    data->num = num;
    return data;
}

assoc_array_error_t assoc_array_realloc(assoc_array_t arr)
{
    if (arr->len == arr->real_len)
    {
        data_t **tmp = realloc(arr->data, sizeof(data_t *) * arr->real_len * arr->step_increase);
        if (tmp == NULL)
            return ASSOC_ARRAY_MEM;
        arr->data = tmp;

        arr->real_len = arr->real_len * arr->step_increase;
    }
    return ASSOC_ARRAY_OK;
}

// бинарный поиск
assoc_array_error_t assoc_array_find_ind(const assoc_array_t arr, const char *key, size_t *ind)
{
    assert(arr != NULL && key != NULL && strlen(key) > 0);
    
    if (arr->len == 0)
        return ASSOC_ARRAY_NOT_FOUND;

    int low = 0, high = arr->len - 1, mid;
    int cmp;

    while (low <= high)
    {
        mid = (low + high) / 2;

        // printf("%d - %s\n", mid, arr->data[mid]->key);
        cmp = strcmp(arr->data[mid]->key, key);
        if (cmp == 0)
        {
            *ind = mid;
            return ASSOC_ARRAY_OK;
        }
        else if (cmp < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }
    
    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_insert_sorted_arr(assoc_array_t arr, data_t *data)
{
    assoc_array_error_t rc = assoc_array_realloc(arr);
    if (rc != ASSOC_ARRAY_OK)
    {
        free(data);
        return rc;
    }

    size_t ind;
    assert(assoc_array_find_ind(arr, data->key, &ind) != ASSOC_ARRAY_OK);

    data_t *tmp;
    size_t i = arr->len;
    arr->data[i] = data;
    arr->len++;

    while (i > 0 && strcmp(arr->data[i - 1]->key, arr->data[i]->key) > 0)
    {
        tmp = arr->data[i - 1];
        arr->data[i - 1] = arr->data[i];
        arr->data[i] = tmp;
        i--;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_data_ind_remove(assoc_array_t arr, size_t ind)
{
    if (arr == NULL || ind >= arr->len)
        return ASSOC_ARRAY_INVALID_PARAM;

    free(arr->data[ind]);
    for (size_t i = ind; i < arr->len - 1; i++)
        arr->data[i] = arr->data[i + 1];
    arr->len--;

    return ASSOC_ARRAY_OK;
}

void assoc_array_data_clear(assoc_array_t arr)
{
    for (size_t i = 0; i < arr->len; i++)
    {
        free(arr->data[i]);
        arr->data[i] = NULL;
    }
    arr->len = 0;
}







