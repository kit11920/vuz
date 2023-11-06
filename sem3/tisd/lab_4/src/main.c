#include <stdio.h>
#include <stdlib.h>

#include "errs.h"
#include "interface.h"
#include "static_stack.h"
#include "work_stack.h"
#include "list_stack.h"
#include "efficiency.h"



int main(void)
{
    int act = -1;
    int rc = OK;
    char c;
    struct static_stack st_stack;
    init_static_stack(&st_stack);
    struct list_stack *li_stack = NULL;
    size_t len_list_stack = 0;
    struct free_adresses fa_arr;

    rc = init_free_adresses_arr(&fa_arr);
    if (rc != OK)
    {
        print_err(rc);
        return rc;
    }
    

    printf(INTRANCE);
    while (act != ACT_END_PROGRAM)
    {
        printf(WHAT_DO);
        while (scanf("%d", &act) != 1 || 
        !(act == ACT_STATICT_STACK || act == ACT_LIST_STACK || act == ACT_EFFICIENCY || act == ACT_END_PROGRAM) ||
        (c = getchar()) != '\n')
        {
            printf("\n");
            print_err(ERR_NUM_ACT_INPUT);
            printf(WHAT_DO);

            c = getchar();
            while (c != '\n')
                c = getchar();
        }

        if (act == ACT_STATICT_STACK)
        {
            working_static_stack(&st_stack);
        }
        else if (act == ACT_LIST_STACK)
        {
            working_list_stack(&li_stack, &len_list_stack, &fa_arr);
        }
        else if (act == ACT_EFFICIENCY)
        {
            make_compare_table();
        }
    }

    just_clear_list_stack(&li_stack);
    free(fa_arr.a);
    return rc;
}



