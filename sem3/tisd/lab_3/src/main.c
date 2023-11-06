#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "actions.h"
#include "errs.h"
#include "efficieny.h"
#include "check.h"


int main(void)
{
    int act = -1;
    int rc = OK;

    printf(INTRANCE);
    while (act != 0)
    {
        printf(WHAT_DO);
        char c;
        while (scanf("%d", &act) != 1 || !(act == ACT_ADDITION || act == ACT_EFFICIENCE || 
        act == ACT_END_PROGRAMM || act == ACT_CHECK_ADDITION) || (c = getchar()) != '\n')
        {
            printf("\n");
            print_err(ERR_NUM_ACT_INPUT);
            printf(WHAT_DO);
            
            char c = getchar();
            while (c != '\n')
                c = getchar();
        }
        // getchar();

        if (act == ACT_ADDITION)
        {
            rc = act_addition();
            if (rc != OK)
            {
                print_err(rc);
                return rc;
            }
        }
        else if (act == ACT_EFFICIENCE)
        {
            rc = make_compare_table();
            if (rc != OK)
            {
                print_err(rc);
                return rc;
            }
        }
        else if (act == ACT_CHECK_ADDITION)
        {
            rc = check_main();
            if (rc != OK)
            {
                print_err(rc);
                return rc;
            }
           
        }
    }


    return OK;
}
