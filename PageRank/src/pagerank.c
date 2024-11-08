#include "pagerank.h"
#include <stdio.h>
#include <stdlib.h>

#define DAMPING_FACTOR 0.85 //el profe menciono que ese es el valooooor

Node* create_node(int out_links) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->pagerank = 1.0;
    node->out_links = out_links;
    node->in_links = NULL;
    return node;
}

void add_inlink(Node *node, int source_id) {
    InLinkNode *new_inlink = (InLinkNode*)malloc(sizeof(InLinkNode));
    new_inlink->node_id = source_id;
    new_inlink->next = node->in_links;
    node->in_links = new_inlink;
}

void calculate_pagerank(Node *nodes[], int node_count, int iterations) {
    double base_rank = (1.0 - DAMPING_FACTOR) / node_count;
    
    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < node_count; i++) {
            double rank_sum = 0.0;
            InLinkNode *inlink = nodes[i]->in_links;
            
            //calculo suma pagerank
            while (inlink != NULL) {
                int source_id = inlink->node_id;
                rank_sum += nodes[source_id]->pagerank / nodes[source_id]->out_links;
                inlink = inlink->next;
            }
            
            //actualiza pagerank
            nodes[i]->pagerank = base_rank + DAMPING_FACTOR * rank_sum;
        }
    }
}

void free_nodes(Node *nodes[], int node_count) {
    for (int i = 0; i < node_count; i++) {
        InLinkNode *inlink = nodes[i]->in_links;
        while (inlink) {
            InLinkNode *temp = inlink;
            inlink = inlink->next;
            free(temp);
        }
        free(nodes[i]);
    }
}
