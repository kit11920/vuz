#include <stdlib.h>
#include <stdio.h>

#include "exp_tree.h"
#include "errs.h"
#include "balanced_tree.h"
#include "external_hashing.h"
#include "internal_hashing.h"
#include "efficiency_hash_tree.h"
#include "efficiency_collision.h"

#define VAR_TREE0 {0, 1, 2, 3, 4, 5, 6, 7, 8}
#define VAR_TREE1 {9, 8, 7, 6, 5, 4, 3, 2, 1}
#define VAR_TREE2 {1, 5, 3, 7, 2, 9, 4, 0, 8}
#define VAR_TREE3 {1, 5, 3, 1, 1, 0, 10, 0, 8}

int main(void)
{
    int arr[LEN_NUM_ARR] = VAR_TREE3;
    enode_t *root = NULL;
    int rc = OK;

    printf("Введите целые числа соответствующие выражению A + (B * (C + (D * (E + F) - (G - H)) + I))\n");
    printf("A B C D E F G H I:\n");
    for (size_t i = 0; i < LEN_NUM_ARR; i++)
        if (scanf("%d", &arr[i]) != 1)
            return ERR_DATA;

    rc = make_exp_tree(&root, arr);
    if (rc != OK)
        return rc;
    
    printf("Значение выражения:\t");
    printf("%d + (%d * (%d + (%d * (%d + %d) - (%d - %d)) + %d)) = %d", 
    arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], calculate_tree(root));
    printf("\n");

    printf("Выражение в префиксной форме (NLR):\t");
    each_nlr_exp_tree(root, print_exp_node, NULL);
    printf("\n");

    printf("Выражение в инфиксной форме (LNR):\t");
    each_lnr_exp_tree(root, print_exp_node, NULL);
    printf("\n");

    printf("Выражение в постфиксной форме (LRN):\t");
    each_lrn_exp_tree(root, print_exp_node, NULL);
    printf("\n");

    char filename[] = "graph/exp_graph.gv";
    rc = export_exp_to_dot(filename, root);
    if (rc != OK)
        goto exp_tree_free;
    printf("Данные о дереве записаны в файл %s\n", filename);
    printf("\n");

    make_counted_exp_tree(&root);
    // printf("Результат выражения: %d\n", res);

    char filename_counted[] = "graph/counted_exp_graph.gv";
    rc = export_exp_to_dot(filename_counted, root);
    if (rc != OK)
        goto exp_tree_free;
    printf("Данные о подсчитанном дереве записаны в файл %s\n", filename_counted);
    printf("\n");

    int arr_tree[LEN_NUM_ARR];
    size_t len_arr_tree = 0;
    printf("Массив на основе дерева, инфиксным обходом (LNR): ");
    make_arr_base_exp_tree(root, arr_tree, &len_arr_tree);
    print_arr(arr_tree, len_arr_tree);
    printf("[len = %zu]", len_arr_tree);
    printf("\n");


    node_t *bs_tree = NULL;
    rc = fill_tree_based_data_arr(&bs_tree, arr_tree, len_arr_tree);
    if (rc != OK)
        goto exp_tree_free;
    char filename_bs[] = "graph/bin_search_graph.gv";
    rc = export_to_dot(filename_bs, bs_tree);
    if (rc != OK)
        goto bs_exp_tree_free;
    printf("Данные о бинарном дереве поиска записаны в файл %s\n", filename_bs);
    printf("count cmps: %zu\n", count_comparison_tree(bs_tree, 1));
    printf("\n");


    bnode_t *bal_tree = NULL;
    rc = fill_btree_based_data_arr(&bal_tree, arr_tree, len_arr_tree);
    if (rc != OK)
        goto bs_exp_tree_free;
    char filename_bal[] = "graph/balance_graph.gv";
    rc = export_to_dot_btree(filename_bal, bal_tree);
    if (rc != OK)
        goto bal_bs_exp_tree_free;
    printf("Данные о сбалансированном дереве записаны в файл %s\n", filename_bal);
    printf("count cmps: %zu\n", count_comparison_btree(bal_tree, 1));
    printf("\n");

    // int tmp_arr[] = {1, 11, 5, 10, 3, 2, 0, -9, -1, 8, 19};
    // size_t tmp_len_arr = 11;

    printf("Хеш-таблицы строятся таким образом, чтобы среднее кол-во сравнений было <= %.2lf\n", MAX_MID_CMPS);

    ex_hash_t ex_htab = create_ex_hash_table();
    rc = fill_ex_hash_table(&ex_htab, arr_tree, len_arr_tree);
    if (rc != OK)
        goto bal_bs_exp_tree_free;
    print_ex_hash_table(&ex_htab);
    printf("count cmp: %zu\n", count_comparison_ex_hash_table(&ex_htab));
    // printf("mem bytes: %zu\n", mem_bytes_ex_hash_table(&ex_htab));
    printf("\n");


    in_hash_t in_htab = create_in_hash_table();
    rc = fill_in_hash_table(&in_htab, arr_tree, len_arr_tree);
    // rc = fill_in_hash_table(&in_htab, tmp_arr, tmp_len_arr);
    if (rc != OK)
        goto ex_htab_bal_bs_exp_tree_free;
    print_in_hash_table(&in_htab);
    printf("count cmp: %zu\n", count_comparison_in_hash_table(&in_htab));
    // printf("mem bytes: %zu\n", mem_bytes_in_hash_table(&in_htab));
    printf("\n");


    rc = make_compare_table_hash_tree(bs_tree, bal_tree, &ex_htab, &in_htab, arr_tree, len_arr_tree);
    if (rc != OK)
        goto in_ex_htab_bal_bs_exp_tree_free;

    rc = make_compare_table_hash_collision(arr_tree, len_arr_tree);
    if (rc != OK)
        goto in_ex_htab_bal_bs_exp_tree_free;

    in_ex_htab_bal_bs_exp_tree_free:
    free_in_hash_tab(&in_htab);
    ex_htab_bal_bs_exp_tree_free:
    free_ex_hash_tab(&ex_htab);
    bal_bs_exp_tree_free:
    free_btree(&bal_tree);
    bs_exp_tree_free:
    free_tree(&bs_tree);
    exp_tree_free:
    free_exp_tree(&root);

    printf("\n");
    return rc;
}














