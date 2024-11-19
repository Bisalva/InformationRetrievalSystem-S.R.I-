/* @Authors : Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */
#include <stdlib.h>
#include <string.h>
#include "node_management.h"

Node* create_node(int out_links) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->pagerank = 1.0;
    node->out_links = out_links;
    node->keyword_relevance = 0.0; //inicializar la relevancia
    node->in_links = NULL;
    return node;
}

void add_inlink(Node *node, int source_id) {
    InLinkNode *new_inlink = (InLinkNode*)malloc(sizeof(InLinkNode));
    new_inlink->node_id = source_id;
    new_inlink->next = node->in_links;
    node->in_links = new_inlink;
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
