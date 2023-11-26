#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

#include "tree.h"
#include "errs.h"
#include "efficiency_find_fill.h"
#include "interface.h"
#include "work_bin_search_tree.h"
#include "exp_tree.h"


int main(void)
{
    int rc = OK, act = -1;
    char c;

    node_t *bb_root = NULL;

    printf(INTRANCE);
    while (act != ACT_EXIT && rc == OK)
    {
        printf(WHAT_DO);
        while (scanf("%d", &act) != 1 || 
        !(act == ACT_BIN_SEARCH_TREE || act == ACT_EFFICIENCY || act == ACT_EXP_TREE || 
        act == ACT_EXIT) || (c = getchar()) != '\n')
        {
            printf("\n");
            print_err(ERR_NUM_ACT_INPUT);
            printf(WHAT_DO);

            c = getchar();
            while (c != '\n')
                c = getchar();
        }
        printf("\n");

        if (act == ACT_BIN_SEARCH_TREE)
            rc = work_bin_search_tree(&bb_root);
        else if (act == ACT_EFFICIENCY)
            rc = make_compare_table_fill_find();
        else if (act == ACT_EXP_TREE)
        {
            rc = act_exp_tree();
        }

        
        if (rc != OK)
        {
            print_err(rc);
            if (rc != ERR_MEM)
                rc = OK;
        }
    }
    free_tree(&bb_root);
    
    // node_t *root = NULL;
    // int rc = OK;
    // int data[] = {8, 4, 20, 2, 6, 18, 24, 25, 21, 19, 16, 3, 1, 0, 17};
    // size_t len_arr_data = 15;

    // for (size_t i = 0; i < len_arr_data; i++)
    // {
    //     rc = add_node_bin_search_tree(&root, data[i]);
    //     assert(rc == OK);
    // }
    // print_tree(root);
    // // printf("%s\n", root->left->data);

    // rc = export_to_dot("graph/graph.gv", root);
    // assert(rc == OK);

    // int data_find[] = {8, 4, 20, 2, 6, 18, 24, 25, 21, 19, 16, 3, 1, 0, 17, 100, -10};
    // node_t *node, *parant;
    // for (size_t i = 0; i < len_arr_data; i++)
    // {
    //     node = find_node_tree(root, data_find[i], &parant);
    //     if (node == NULL)
    //         printf("%d not found\n", data_find[i]);
    //     else if (parant == NULL)
    //         printf("%d: node - %d, parant = NULL\n", data_find[i], node->data);
    //     else
    //         printf("%d: node - %d, parant = %d\n", data_find[i], node->data, parant->data);
    // }

    // int remove_data = 8;
    // rc = del_node_by_data_tree(&root, remove_data);
    // if (rc == ERR_NOT_FOUND)
    //     print_err(rc);
    // else
    // {
    //     rc = export_to_dot("graph/del_graph.gv", root);
    //     assert(rc == OK);
    // }
    
    // free_tree(&root);

    // rc = make_left_tree(&root, 3);
    // assert(rc == OK);

    // print_tree(root);
    // rc = export_to_dot("graph/arr_graph.gv", root);
    // assert(rc == OK);

    // free_tree(&root);

    return rc;
}














