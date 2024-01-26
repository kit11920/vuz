// #include <stdlib.h>
// #include <stdio.h>
// #include <assert.h>

// #include "associative_array.h"
// #include "impl_2_plus.h"


// void action_print(const char *key, int *num, void *param)
// {
//     printf((char *) param, key, *num);
// }

// // dot
// void tree_each(node_t *node, void (*action)(node_t *node, void *param), void *param)
// {
//     assert(action != NULL);

//     if (node == NULL)
//         return;

//     action(node, param);
//     tree_each(node->left, action, param);
//     tree_each(node->right, action, param);
// }

// void to_dot(node_t *node, void *param)
// {
//     FILE *f = param;
//     assert(f != NULL && node != NULL);
    
//     if (node->left)
//         fprintf(f, "%s -> %s;\n", node->key, node->left->key);
//     if (node->right)
//         fprintf(f, "%s -> %s;\n", node->key, node->right->key);
// }

// void export_to_dot(char *filename, node_t *node)
// {
//     FILE *f = fopen(filename, "w");
//     assert(f != NULL);

//     fprintf(f, "digraph graph_aa {\n");

//     tree_each(node, to_dot, f);

//     fprintf(f, "}\n");
// }




