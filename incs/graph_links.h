#ifndef GRAPH_LINKS_H
#define GRAPH_LINKS_H

#include "graph_management.h"
#include "adj_list.h"

/* Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */

AdjListNode* create_adj_list_node(int dest);
void add_link(Graph *graph, int src, int dest);
void connect_graphs(Graph *graph1, Graph *graph2, int src, int dest);

#endif