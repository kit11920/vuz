#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "node_list.h"
#include "errs.h"
#include "str_list.h"
#include "list.h"


char *input_dstr(void)
{
    char *str = NULL;
    size_t len = 0;
    ssize_t read = 0;

    if ((read = getline(&str, &len, stdin)) == -1 || read <= 1)
    {
        free(str);
        return NULL;
    }
    str[read - 1] = 0;

    return str;
}

/*
Пока str не закончится:
В data копирует по 4 символа из str
потом на основе data создает узел списка и добавляет его 
*/
int string_to_list(node_t **head, char *str)
{
    *head = NULL;
    node_t *node;
    char data[PART_LEN + 1];
    size_t len_data;
    bool string_end = false;
    char end_char = 0;
    size_t i = 0;

    if (str[0] == end_char)
        return ERR_IO;

    while (!string_end)
    {
        data[0] = 0;
        strncat(data, &str[i], PART_LEN);
        len_data = strlen(data);
        i += len_data;
        if (len_data < PART_LEN)
            string_end = true;
        
        node = create_node(data);
        if (node == NULL)
        {
            free_list(head);
            return ERR_IO;
        }
        *head = add_tail_list(*head, node);
    }

    return OK;
}

int input_string_list(node_t **head)
{
    int rc = OK;
    char *str = input_dstr();
    if (str == NULL)
        return ERR_MEM;
    rc = string_to_list(head, str);
    free(str);
    return rc;
}

/// head - указатель на голову с которой надо смотреть
/// ind < PART_LEN
bool strcmp_ind(node_t *head, node_t *str, size_t ind)
{
    assert(ind < PART_LEN);
    bool same = true, string_end = false;

    size_t i = ind, j = 0;
    while (!string_end && same)
    {
        if (head->data[i] != str->data[j] && str->data[j] != 0)
            same = false; 
        else
        {
            if (str->data[j] == 0 || head->data[j] == 0)
                string_end = true;
            else
            {
                i++;
                j++;

                if (i == PART_LEN)
                {
                    head = head->next;
                    assert(head != NULL);   // список не может закончится раньше строки
                    i = 0;
                }
                if (j == PART_LEN)
                {
                    str = str->next;
                    assert(str != NULL);
                    j = 0;
                }
            }
        }
    }

    return same;
}

int search_string(node_t *head, node_t *str)
{
    size_t ind = 0, i = 0;
    node_t *node = head;

    while (node != NULL)
    {
        if (strcmp_ind(node, str, i))
            return ind;
        ind++;
        i = (i + 1) % PART_LEN;
        if (i == 0)
            node = node->next;
    }

    return -1;
}

void del_char(node_t *head, size_t ind)
{
    assert(ind < PART_LEN);

    bool string_end = false;
    node_t *node = head;
    size_t i = ind;

    while (!string_end)
    {
        if (i < PART_LEN - 1)
        {
            node->data[i] = node->data[i + 1];
            if (node->data[i] == 0)
                string_end = true;
            i++;
        }
        else
        {
            node->data[i] = node->next->data[0];
            if (node->data[i] == 0)
            {
                free_node(node->next);
                node->next = NULL;
                string_end = true;
            }
            else
            {
                node = node->next;
                i = 0;
            }
        }
    }
}

void del_2spaces(node_t *head)
{
    node_t *node = head;
    size_t ind = 0;
    bool string_end = false;

    while (!string_end)
    {
        if (ind < PART_LEN - 1 && node->data[ind] == ' ' && node->data[ind + 1] == ' ')
            del_char(node, ind + 1);
        else if (ind == PART_LEN - 1 && node->data[ind] == ' ' && node->next->data[0] == ' ')
            del_char(node->next, 0);
        else if (ind < PART_LEN - 1)
            ind++;
        else
        {
            node = node->next;
            ind = 0;
        }

        if (node->data[ind] == 0)
            string_end = true;
    }
}

void cat_str_list(node_t *list1, node_t *list2)
{
    assert(list1 != NULL && list2 != NULL);

    node_t *tmp = list1;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = list2;
        
    size_t count_left = 0;
    char *adrs_0 = strchr(tmp->data, 0);
    assert(adrs_0 != NULL);
    count_left = PART_LEN - (adrs_0 - tmp->data);

    memmove(adrs_0, list2->data, count_left * sizeof(char));
    for (size_t i = 0; i < count_left; i++)
        del_char(list2, 0);
}










