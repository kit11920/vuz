#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "errs.h"
#include "stack.h"


stack_t *create_stack(size_t len_stack)
{
    stack_t *stack = malloc(sizeof(stack_t));
    if (stack == NULL)
        return NULL;
    
    stack->arr = malloc(sizeof(int) * len_stack);
    if (stack->arr == NULL)
    {
        free(stack);
        return NULL;
    }
    stack->ps = NULL;
    stack->aub = stack->arr + len_stack - 1;

    return stack;
}

void push_stack(stack_t *stack, int elem)
{
    assert(stack->ps != stack->aub);

    if (stack->ps == NULL)
        stack->ps = stack->arr;
    else
        stack->ps++;
    *(stack->ps) = elem;
}

int pop_stack(stack_t *stack)
{
    assert(stack->ps != NULL);

    int out = *stack->ps;
    if (stack->ps == stack->arr)
        stack->ps = NULL;
    else
        stack->ps--;
    
    return out;
}

void free_stack(stack_t **stack)
{
    free((*stack)->arr);
    free(*stack);
    *stack = NULL;
}

bool is_empty_stack(stack_t *stack)
{
    return stack->ps == NULL;
}

void print_stack(stack_t *stack)
{
    for (int *cur = stack->ps; cur >= stack->arr; cur--)
        printf("%d ", *cur);
    printf("\n");
}










