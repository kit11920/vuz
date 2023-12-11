#include <stdlib.h>
#include <assert.h>

#include "arr_stack.h"
#include "stack.h"



void init_static_stack(struct static_stack *stack)
{
    stack->ps = NULL;
    stack->aub = stack->a + MAX_LEN_STATICK_STACK - 1;
}

void push_static_stack(struct static_stack *stack, data_exp_t data)
{
    assert(stack->ps != stack->aub);

    if (stack->ps == NULL)
        stack->ps = stack->a;
    else
        stack->ps++;
    *(stack->ps) = data;
}

data_exp_t pop_static_stack(struct static_stack *stack)
{
    assert(stack->ps != NULL);
    data_exp_t out = *(stack->ps);

    if (stack->ps == stack->a)
        stack->ps = NULL;
    else
        stack->ps--;

    return out;
}

int calculate_arr_stack(lnode_t *exp)
{
    struct static_stack stack;
    init_static_stack(&stack);

    lnode_t *tmp = pop_list(&exp);
    data_exp_t now;
    data_exp_t left, right, res_data;
    int res;

    while (tmp != NULL)
    {
        if (tmp->data_exp.type == NUM)
        {
            push_static_stack(&stack, tmp->data_exp);
        }
        else
        {
            right = pop_static_stack(&stack);
            left = pop_static_stack(&stack);

            if (tmp->data_exp.data.exp == PLUS_EXP)
                res = left.data.num + right.data.num;
            else if (tmp->data_exp.data.exp == MINUS_EXP)
                res = left.data.num - right.data.num;
            else
                res = left.data.num * right.data.num;

            res_data.type = NUM;
            res_data.data.num = res;
            push_static_stack(&stack, res_data);
        }
        tmp = pop_list(&exp);
        // print_list(stack);
    }
    now = pop_static_stack(&stack);
    // assert(stack.ps == NULL);
    res = now.data.num;
    // assert(pop_list(&exp) == NULL && tmp->data_exp.type == NUM && stack == NULL);

    return res;
}













