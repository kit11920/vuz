// #include <stdlib.h>
// #include <stdio.h>


// #include "associative_array.h"
// #include "help_debug.h"

// int main(void)
// {
//     assoc_array_error_t rc = ASSOC_ARRAY_OK;
//     assoc_array_t arr = assoc_array_create();
    
//     if ((rc = assoc_array_insert(arr, "d", 1)) != ASSOC_ARRAY_OK)
//         return rc;
//     if ((rc = assoc_array_insert(arr, "f", 2)) != ASSOC_ARRAY_OK)
//         return rc;
//     if ((rc = assoc_array_insert(arr, "b", 3)) != ASSOC_ARRAY_OK)
//         return rc;
//     if ((rc = assoc_array_insert(arr, "ed", 4)) != ASSOC_ARRAY_OK)
//         return rc;
//     if ((rc = assoc_array_insert(arr, "c", 5)) != ASSOC_ARRAY_OK)
//         return rc;
//     if ((rc = assoc_array_insert(arr, "i", 6)) != ASSOC_ARRAY_OK)
//         return rc;
//     if ((rc = assoc_array_insert(arr, "a", 7)) != ASSOC_ARRAY_OK)
//         return rc;
//     if ((rc = assoc_array_insert(arr, "ef", 8)) != ASSOC_ARRAY_OK)
//         return rc;
//     if ((rc = assoc_array_insert(arr, "j", 9)) != ASSOC_ARRAY_OK)
//         return rc;
//     if ((rc = assoc_array_insert(arr, "eb", 10)) != ASSOC_ARRAY_OK)
//         return rc;
//     export_to_dot("tmp.gv", arr->root);

//     rc = assoc_array_each(arr, action_print, "%s : %d\n");
//     if (rc != ASSOC_ARRAY_OK)
//         return rc;
//     printf("\n");

//     int *num = NULL;
//     char search_str[] = "f";
//     rc = assoc_array_find(arr, search_str, &num);
//     if (rc == ASSOC_ARRAY_NOT_FOUND)
//         puts("Not found");
//     else if (rc == ASSOC_ARRAY_OK)
//         printf("%s - %d\n\n", search_str, *num);
//     else
//         return rc;
    
//     rc = assoc_array_remove(arr, "w");
//     if (rc != ASSOC_ARRAY_NOT_FOUND)
//         return rc;
    
//     printf("\n");
//     rc = assoc_array_each(arr, action_print, "%s : %d\n");
//     if (rc != ASSOC_ARRAY_OK)
//         return rc;
//     printf("\n");

//     if ((rc = assoc_array_min(arr, &num)) != ASSOC_ARRAY_OK)
//         return rc;
//     printf("min: %d", *num);

//     assoc_array_max(arr, &num);
//     printf("max: %d", *num);
    
//     assoc_array_destroy(&arr);
//     if (arr == NULL)
//         printf("ok\n");
    
//     return ASSOC_ARRAY_OK;
// }



