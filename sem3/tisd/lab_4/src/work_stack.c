#include <stdio.h>
#include <assert.h>

#include "work_stack.h"
#include "errs.h"
#include "static_stack.h"
#include "interface.h"
#include "list_stack.h"


int choose_work_stack(int act)
{
    assert(act == ACT_LIST_STACK || act == ACT_STATICT_STACK);

    char c;
    int work;
    if (act == ACT_LIST_STACK)
        printf(WORK_STACK_LI);
    else
        printf(WORK_STACK_ST);

    while (scanf("%d", &work) != 1 ||
    !(work == WORK_STACK_ADD || work == WORK_STACK_DEL 
    || work == WORK_STACK_PRINT || work == WORK_STACK_END || work == WORK_STACK_CLEAR ||
    (work == WORK_WATCH_FREE_ADRESSES_ARR && act == ACT_LIST_STACK)) ||
    (c = getchar()) != '\n')
    {
        printf("\n");
        print_err(ERR_NUM_ACT_INPUT);

        if (act == ACT_LIST_STACK)
            printf(WORK_STACK_LI);
        else
            printf(WORK_STACK_ST);

        c = getchar();
        while (c != '\n')
            c = getchar();
    }

    return work;
}


void working_static_stack(struct static_stack *stack)
{
    int rc = OK;
    int work = -1;
    
    while (work != WORK_STACK_END)
    {
        work = choose_work_stack(ACT_STATICT_STACK);
        if (work == WORK_STACK_ADD)
        {
            rc = act_add_elem_static_stack(stack);
            print_err(rc);
        }
        else if (work == WORK_STACK_DEL)
        {
            rc = act_del_elem_static_stack(stack);
            print_err(rc);
        }
        else if (work == WORK_STACK_PRINT)
            print_static_stack(stack);
        else if (work == WORK_STACK_CLEAR)
            clear_static_stack(stack);
    }
}

void working_list_stack(struct list_stack **stack, size_t *len_list_stack, struct free_adresses *arr)
{
    int rc = OK;
    int work = -1;
    
    while (work != WORK_STACK_END)
    {
        work = choose_work_stack(ACT_LIST_STACK);
        if (work == WORK_STACK_ADD)
        {
            rc = act_add_elem_list_stack(stack, len_list_stack, arr);
            print_err(rc);
        }
        else if (work == WORK_STACK_DEL)
        {
            rc = act_del_elem_list_stack(stack, len_list_stack, arr);
            print_err(rc);
            // printf("%p \n", arr->a)
        }
        else if (work == WORK_STACK_PRINT)
        {
            printf("Максимальная длина стека %d\n", MAX_LEN_LIST_STACK);
            print_list_stack(*stack);
        }
        else if (work == WORK_STACK_CLEAR)
            clear_list_stack(stack, len_list_stack, arr);
        else if (work == WORK_WATCH_FREE_ADRESSES_ARR)
            print_free_adresses_arr(arr);
    }
}

