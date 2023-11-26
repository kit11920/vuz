#include <stdlib.h>
#include <stdio.h>

#include "errs.h"
#include "tree.h"
#include "interface.h"


int work_bin_search_tree(node_t **root)
{
    int act = -1, rc = OK;
    char c;

    while (act != WORK_END && rc == OK)
    {
        printf(WORK_BIN_SEARCH_TREE);
        while (scanf("%d", &act) != 1 || 
        !(act == WORK_ADD || act == WORK_DEL || act == WORK_FIND || 
        act == WORK_SHOW || act == WORK_END || act == WORK_CLEAR) || (c = getchar()) != '\n')
        {
            printf("\n");
            print_err(ERR_NUM_ACT_INPUT);
            printf(WORK_BIN_SEARCH_TREE);

            c = getchar();
            while (c != '\n')
                c = getchar();
        }
        printf("\n");

        if (act == WORK_ADD)
        {
            int data;
            printf("Введите число, которое будет записано в новом узле: ");
            if (scanf("%d", &data) != 1)
                rc = ERR_DATA;
            else
                rc = add_node_bin_search_tree(root, data);
            
            if (rc == OK)
                printf("Добавлен новый узел с содержимым %d\n", data);

            c = getchar();
            while (c != '\n')
                c = getchar();
        }
        else if (act == WORK_DEL)
        {
            if (*root == NULL)
                rc = ERR_EMPTY_TREE;
            else
            {
                int data;
                printf("Введите число, которое должно быть записано в удаляемом узле: ");
                if (scanf("%d", &data) != 1)
                    rc = ERR_DATA;
                else
                    rc = del_node_by_data_tree(root, data);
                
                if (rc == OK)
                    printf("Удален узел с содержимым %d\n", data);

                c = getchar();
                while (c != '\n')
                    c = getchar();
            }
        }
        else if (act == WORK_FIND)
        {
            if (*root == NULL)
                rc = ERR_EMPTY_TREE;
            else
            {
                int data;
                node_t *node, *parant;
                printf("Введите число, которое будем искать: ");
                if (scanf("%d", &data) != 1)
                    rc = ERR_DATA;
                else
                {
                    node = find_node_tree(*root, data, &parant);
                    if (node == NULL)
                        rc = ERR_NOT_FOUND;
                    else if (parant == NULL)
                        printf("Найден элемент - %d, он является корнем дерева\n", node->data);
                    else
                        printf("Найден элемент - %d, его предок - %d\n", node->data, parant->data);
                }
                c = getchar();
                while (c != '\n')
                    c = getchar();
            }
        }
        else if (act == WORK_SHOW)
        {
            if (*root == NULL)
                rc = ERR_EMPTY_TREE;
            else
            {
                printf("Дерево в префиксной форме: ");
                print_tree(*root);

                if (!((*root)->left == NULL && (*root)->right == NULL))
                {
                    char filename[] = "graph/graph.gv"; 
                    rc = export_to_dot(filename, *root);
                    if (rc == OK)
                        printf("Данные о дереве записаны в файл %s\n", filename);
                }
            }
        }
        else if (act == WORK_CLEAR)
        {
            free_tree(root);
            printf("Теперь дерево пусто\n");
        }
        
        if (rc != OK)
        {
            print_err(rc);
            if (rc != ERR_MEM)
                rc = OK;
        }
        printf("\n");
    }
    return rc;
}























