#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

#include "tree.h"
#include "errs.h"



int main(void)
{
    node_t *root = NULL;
    int rc = OK;

    rc = add_node_bin_search_tree(&root, "ff");
    assert(rc == OK);
    rc = add_node_bin_search_tree(&root, "e");
    printf("rc = %d\n", rc);
    assert(rc == OK);
    rc = add_node_bin_search_tree(&root, "a");
    assert(rc == OK);
    rc = add_node_bin_search_tree(&root, "qq");
    assert(rc == OK);

    print_tree(root);
    // printf("%s\n", root->left->data);

    rc = export_to_dot("graph.gv", root);
    assert(rc == OK);

    node_t *node, *parant;

    char *data[] = {"ff", "e", "a", "qq", "s"};
    for (size_t i = 0; i < 5; i++)
    {
        node = find_node_tree(root, data[i], &parant);
        if (node == NULL)
            printf("%s not found\n", data[i]);
        else if (parant == NULL)
            printf("%s: node - %s, parant = NULL", data[i], node->data);
        else
            printf("%s: node - %s, parant = %s", data[i], node->data, parant->data);
    }
    
    free_tree(root);

    return OK;
}














