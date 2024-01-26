#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"
#include "errs.h"
#include "node_list.h"


node_t *add_tail_list(node_t *head, node_t *node)
{
    node->next = NULL;
    if (head == NULL)
        return node;
    
    node_t *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    
    tmp->next = node;
    return head;
}


void print_list(FILE *f, node_t *head, void (*print_data)(FILE *, void *))
{
    node_t *node = head;
    
    while (node != NULL)
    {
        print_data(f, node->data);
        node = node->next;
    }
}

void free_list(node_t *head)
{
    if (head == NULL)
        return;

    node_t *node;
    while (head != NULL)
    {
        node = head->next;
        free_node(head);
        head = node;
    }
}
// 
void free_data_list(node_t *head, void (*free_data)(void *))
{
    if (head == NULL)
        return;

    node_t *node = head;
    node_t *next_node;
    while (node != NULL)
    {
        next_node = node->next;
        free_data(node->data);
        node = next_node;
    }
}

// size_t count_list(node_t *head)
// {
//     size_t len_list = 0;
//     node_t *node = head;

//     while (node != NULL)
//     {
//         len_list++;
//         node = node->next;
//     }

//     return len_list;
// }

void front_back_split(node_t *head, node_t **back)
{
    if (head == NULL)
        return;

    node_t *frst = head, *scnd = head;
    while (scnd != NULL && scnd->next != NULL)
    {
        scnd = scnd->next;
        scnd = scnd->next;
        if (scnd != NULL)
            frst = frst->next;
    }

    *back = frst->next;
    frst->next = NULL;
}

void fast_add_tail_list(node_t **head, node_t **tail, node_t *new_node)
{
    if (*head == NULL)
    {
        *head = new_node;
        *tail = *head;
    }
    else
    {
        (*tail)->next = new_node;
        (*tail) = (*tail)->next;
    }
}

// без fast_add_tail_list() нельзя так как проверка "if (*head == NULL)" нужна в любом случаем
// так как мы заполняем список out с начала (а в начале out == NULL)
node_t *sorted_merge(node_t **head_a, node_t **head_b, cmp_t cmp)
{
    node_t *out = NULL, *last_out, *tmp = NULL;

    node_t *help = NULL;
    if (head_a == NULL)
        head_a = &help;
    if (head_b == NULL)
        head_b = &help;

    while (*head_a != NULL && *head_b != NULL)
    {
        if (cmp((*head_a)->data, (*head_b)->data) <= 0)
        {
            tmp = (*head_a)->next;
            fast_add_tail_list(&out, &last_out, *head_a);
            *head_a = tmp;
        }
        else
        {
            tmp = (*head_b)->next;
            fast_add_tail_list(&out, &last_out, *head_b);
            *head_b = tmp;          
        }
    }
    //убрать копирование
    if (*head_a != NULL)
    {
        if (out == NULL)
            out = *head_a;
        else
            last_out->next = *head_a;
        *head_a = NULL;
    }
    else if (*head_b != NULL)
    {
        if (out == NULL)
            out = *head_b;
        else
            last_out->next = *head_b;
        *head_b = NULL;
    }

    return out;
}

node_t *sort(node_t *head, cmp_t cmp)
{
    if (head == NULL)
        return NULL;

    if (head->next != NULL)
    {
        node_t *back = NULL;
        front_back_split(head, &back);
        head = sort(head, cmp);
        back = sort(back, cmp);
        head = sorted_merge(&head, &back, cmp);
    }

    return head;
}


// int make_arr_of_data(node_t *head, country_t *arr[], size_t *len_arr)
// {
//     *len_arr = count_list(head);
//     if (*len_arr == 0)
//         return OK;

//     node_t *node = head;

//     arr = malloc(*len_arr * sizeof(country_t *));
//     if (arr == NULL)
//         return ERR_MEM;

//     for (size_t i = 0; i < len_arr; i++)
//     {
//         arr[i] = node->data;
//         node = node->next;
//     }

//     return OK;
// }

int copy_list(node_t **dst, node_t *head)
{
    *dst = NULL;
    node_t *node = head, *tmp, *last_dst;

    while (node != NULL)
    {
        tmp = create_node(node->data);
        if (tmp == NULL)
        {
            free_list(*dst);
            return ERR_MEM;
        }
        fast_add_tail_list(dst, &last_dst, tmp);
        // *dst = add_tail_list(*dst, tmp);
        node = node->next;
    }

    return OK;
}

node_t *find_first_same_list(node_t *head, cmp_t cmp, void *data)
{
    while (head != NULL && cmp(head->data, data) != 0)
        head = head->next;
    assert(head != NULL);
    return head;
}

/*
Проходим по списку элементом i
i - элемент в списке у которого в данным момент ищем дубликат
в find_first_same_list() проходим от head до i->next или пока не найдем дупликат
(Если функция find_first_same_list() вернула i->next то дупликатор нет)

Аналог кода для массива
for (size_t i = 0; i < len_arr; i++)
    for (size_t j = 0; j < i; j++)
        if (arr[i] == arr[j])
            delete;
*/
void remove_duplicates(node_t **head, cmp_t cmp)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL)
        return;

    node_t *i = *head, *tmp;

    while (i->next != NULL)
    {
        if (find_first_same_list(*head, cmp, i->next->data) != i->next)
        {
            tmp = i->next;
            i->next = tmp->next;
            free_node(tmp);
        }
        else
            i = i->next;
    }
}


