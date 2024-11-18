#ifndef GRAPH_MANAGEMENT_H
#define GRAPH_MANAGEMENT_H

#include "adj_list.h"

typedef struct Graph {
    int num_docs;
    AdjList *array;
} Graph;


Graph* create_graph(int num_docs);
void free_graph(Graph *graph);

#endif