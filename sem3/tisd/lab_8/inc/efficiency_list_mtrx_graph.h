#ifndef EFFICIENCY_LIST_MTRX_GRAPH_H__
#define EFFICIENCY_LIST_MTRX_GRAPH_H__

#include "list_graph.h"
#include "mtrx_graph.h"

#define COUNT_CALCS 1000
#define MIN_COUNT_REAPET 1000

typedef unsigned long long (*measure_time_t)(void *data_struct);








int make_compare_table_list_mtrx_graph(listg_t *list_graph, mtrxg_t *mtrx_graph);












#endif


