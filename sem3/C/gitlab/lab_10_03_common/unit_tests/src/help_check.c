#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "associative_array.h"
#include "help_check.h"



assoc_array_error_t full_assoc_array(assoc_array_t arr, str_int_t *data, size_t len_arr)
{
    assoc_array_error_t rc = ASSOC_ARRAY_OK;

    for (size_t i = 0; i < len_arr; i++)
    {
        rc = assoc_array_insert(arr, data[i].str, data[i].num);
        if (rc != ASSOC_ARRAY_OK)
        {
            assoc_array_clear(arr);
            return rc;
        }
    }
    return ASSOC_ARRAY_OK;
}


void action_plus(const char *key, int *num, void *param)
{
    (void) key;
    int *plus = param;

    *num += *plus;
}

void action_count_key_is_char(const char *key, int *num, void *param)
{
    (void) num;
    int *count = param;

    if (strlen(key) == 1)
        (*count)++;
}






