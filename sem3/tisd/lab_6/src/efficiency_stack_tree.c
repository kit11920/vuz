#include <stdio.h>
#include <assert.h>

#include "efficiency.h"
#include "efficiency_stack_tree.h"
#include "exp_tree.h"
#include "fort.h"
#include "arr_stack.h"


unsigned long long measure_time_for(void *exp)
{
    unsigned long long beg, end;
    (void) exp;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
        ;
    end = ms_now();
    return end - beg;
}

unsigned long long measure_time_tree(void *exp)
{
    enode_t *head = exp;
    unsigned long long beg, end;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
        calculate_tree(head);
    end = ms_now();
    return end - beg;
}

unsigned long long measure_time_stack(void *exp)
{
    lnode_t *list_exp = exp;
    unsigned long long beg, end;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
        calculate_stack(list_exp);
    end = ms_now();
    return end - beg;
}

unsigned long long measure_time_arr_stack(void *exp)
{
    lnode_t *list_exp = exp;
    unsigned long long beg, end;

    beg = ms_now();
    for (size_t i = 0; i < COUNT_CALCS; i++)
        calculate_arr_stack(list_exp);
    end = ms_now();
    return end - beg;
}

int gettime_stack_tree(calc_measure_time_t measure, void *exp, unsigned long long *t, size_t len_t, long long *time)
{
    double rse = 100;

    size_t i = 0;
    rse = 100;
    while (i < len_t && (rse > 5 || i <= MIN_COUNT_REAPET))
    {
        t[i] = measure(exp);
        
        rse = get_rse(t, i + 1);
        i++;
    }
    
    if (i >= len_t)
        return ERR_COUNT_REPEAT_TIME_SMALL;
    
    *time = (long long) get_tavg(t, i);
    
    return OK;
}

int make_compare_table_stack_tree(enode_t *tree, lnode_t *stack)
{
    int rc = OK;
    unsigned long long *t = NULL;
    int len_t = 500;
    long long tree_calc_time, stack_calc_time, for_calc_time, arr_stack_calc_time;
    double list_stack_tree_koef_bigger, arr_stack_tree_koef_bigger;
    
    // Выделение памяти под вспомагательные структуры
    t = malloc(len_t * sizeof(unsigned long long));
    if (!t)
    {
        rc = ERR_MEM;
        return rc;
    }
    //

    printf("Подождите, идет обработка данных...\n");
    ft_table_t *tab = ft_create_table();
    ft_set_cell_prop(tab, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_printf_ln(tab, "tree time calc\nmks|list stack time calc\nmks|koef bigger\nlist stack then tree|arr stack time calc\nmks|koef bigger\narr stack then tree");

    rc = gettime_stack_tree(measure_time_for, NULL, t, len_t, &for_calc_time);
    assert(rc == OK); 

    rc = gettime_stack_tree(measure_time_tree, tree, t, len_t, &tree_calc_time);
    assert(rc == OK); 
    if (for_calc_time > tree_calc_time)
        tree_calc_time = 0;
    else
        tree_calc_time -= for_calc_time;

    rc = gettime_stack_tree(measure_time_stack, stack, t, len_t, &stack_calc_time);
    assert(rc == OK); 
    if (for_calc_time > stack_calc_time)
        stack_calc_time = 0;
    else
        stack_calc_time -= for_calc_time;

    rc = gettime_stack_tree(measure_time_arr_stack, stack, t, len_t, &arr_stack_calc_time);
    assert(rc == OK); 
    if (for_calc_time > arr_stack_calc_time)
        arr_stack_calc_time = 0;
    else
        arr_stack_calc_time -= for_calc_time;

    list_stack_tree_koef_bigger = (double) stack_calc_time / tree_calc_time;
    arr_stack_tree_koef_bigger = (double) arr_stack_calc_time / tree_calc_time;

    ft_printf_ln(tab, "%lld|%lld|%.2lf|%lld|%.2lf", tree_calc_time, stack_calc_time, list_stack_tree_koef_bigger, arr_stack_calc_time, arr_stack_tree_koef_bigger);
    
    printf("Кол-во вычислений в одном замере: %d\n", COUNT_CALCS);
    printf("%s\n", ft_to_string(tab));
    ft_destroy_table(tab);

    free(t);
    return OK;
}


















