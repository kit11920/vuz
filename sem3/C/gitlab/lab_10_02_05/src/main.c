#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node_list.h"
#include "list.h"
#include "str_list.h"
#include "errs.h"

#define LEN_ACT 3

int main(void)
{
    int rc = OK;
    char act[LEN_ACT + 2];
    size_t len = 0;

    if (fgets(act, sizeof(act), stdin) == NULL)
        return ERR_ACT;
    len = strlen(act);
    if (len != 0 && act[len - 1] == '\n')
    {
        len--;
        act[len] = 0;
    }
    if (len == 0 || len > LEN_ACT)
        return ERR_ACT;

    if (strcmp(act, "out") == 0)
    {
        node_t *head = NULL;

        rc = input_string_list(&head);
        if (rc != OK)
            return rc;
        print_list(head);
        free_list(&head);
    }
    else if (strcmp(act, "cat") == 0)
    {
        node_t *list1 = NULL, *list2 = NULL;
        
        rc = input_string_list(&list1);
        if (rc != OK)
            return rc;
        rc = input_string_list(&list2);
        if (rc != OK)
        {
            free_list(&list1);
            return rc;
        }

        // head = add_tail_list(list1, list2);
        cat_str_list(list1, list2);
        print_list(list1);
        free_list(&list1);
    }
    else if (strcmp(act, "pos") == 0)
    {
        node_t *head = NULL, *str = NULL;
        int ind;

        rc = input_string_list(&head);
        if (rc != OK)
            return rc;
        rc = input_string_list(&str);
        if (rc != OK)
        {
            free_list(&head);
            return rc;
        }

        ind = search_string(head, str);
        // if (ind == -1)
        //     rc = ERR_NOT_FOUND;
        // else
        printf("%d\n", ind);

        free_list(&head);
        free_list(&str);
    }
    else if (strcmp(act, "sps") == 0)
    {
        node_t *head = NULL;

        rc = input_string_list(&head);
        if (rc != OK)
            return rc;

        del_2spaces(head);

        print_list(head);
        free_list(&head);
    }
    else
        return ERR_ACT;

    return rc;
}


