#ifndef PAGERANK_H
#define PAGERANK_H

#include "node_management.h"

/* Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */

void calculate_pagerank(Node *nodes[], int node_count, double damping_factor, int iterations);
void set_keyword_relevance(Node *nodes[], int node_count, const char *keywords[], int keyword_count, const char *documents[]);

#endif
