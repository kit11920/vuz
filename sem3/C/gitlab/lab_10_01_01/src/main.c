#include <stdlib.h>
#include <string.h>
// #include <stdio.h>

#include "data.h"
#include "errs.h"
#include "node_list.h"
#include "list.h"


int main(int argc, char **argv)
{
    node_t *head = NULL;
    int rc = OK;
    FILE *fout;

    if (argc >= 3)
    {
        rc = read_file_list(argv[1], &head);
        if (rc != OK)
            return rc;
        if (head == NULL)
            return ERR_RANGE;

        fout = fopen(argv[2], "w");
        if (fout == NULL)
        {
            free_data_list(head, free_country);
            free_list(head);
            return ERR_FILE_OUT;
        }

        if (argc == 3)
            print_list(fout, head, print_country);
        else if (argc == 6 && strcmp(argv[3], "-i") == 0)
        {
            node_t *before = NULL;
            rc = find_by_country_name(argv[4], head, &before);
            if (rc == OK && before == NULL)
                fprintf(fout, "Not found\n");
            else if (rc == OK)
            {
                // Считываем из файла2, данные которые будем вставлять в список
                node_t *node = NULL;
                rc = read_file_list(argv[5], &node);
                if (rc == OK && node->next != NULL)
                {
                    free_data_list(node, free_country);
                    free_list(node);
                    rc = ERR_FILE_ONE_DATA;
                }
                //

                if (rc == OK)
                {
                    insert(&head, node, before);
                    print_list(fout, head, print_country);
                }
            }
        }
        else if (argc == 4 && strcmp(argv[3], "-s") == 0)
        {
            head = sort(head, cmp_name);
            print_list(fout, head, print_country);
        }
        else if (argc == 4 && strcmp(argv[3], "-d") == 0)
        {
            node_t *full_list = NULL;
            rc = copy_list(&full_list, head);
            if (rc == OK)
            {
                remove_duplicates(&head, cmp_name);
                print_list(fout, head, print_country);

                free_list(head);
                head = full_list;
            }
        }
        else
            rc = ERR_ARGS;

        free_data_list(head, free_country);
        free_list(head);
        fclose(fout);
    }
    else
        rc = ERR_ARGS;


    return rc;
}




