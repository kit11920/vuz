#include <stdlib.h>
#include <stdio.h>


#include "arr.h"
#include "list.h"
#include "errs.h"
#include "time_system.h"
#include "interface.h"


int main(void)
{
    int rc = OK, act = -1;
    char c;

    time_params_t tp;
    init_time_params(&tp);

    printf(INTRANCE);
    while (act != ACT_END_PROGRAM)
    {
        print_time_params(&tp);
        printf(WHAT_DO);
        while (scanf("%d", &act) != 1 || 
        !(act == ACT_ARR_QUEUE || act == ACT_LIST_QUEUE || act == ACT_CHANGE_PARAMS 
        || act == ACT_EFFICIENCY || act == ACT_END_PROGRAM) ||
        (c = getchar()) != '\n')
        {
            printf("\n");
            print_err(ERR_NUM_ACT_INPUT);
            print_time_params(&tp);
            printf(WHAT_DO);

            c = getchar();
            while (c != '\n')
                c = getchar();
        }

        if (act == ACT_ARR_QUEUE)
        {
            rc = process_arr_queue(&tp);
        }
        else if (act == ACT_LIST_QUEUE)
        {
            rc = process_list_queue(&tp);
        }
        else if (act == ACT_CHANGE_PARAMS)
        {
            rc = change_time_params(&tp);
        }

        if (rc != OK)
        {
            print_err(rc);
            rc = OK;
        }
    }

            


    return rc;
}













