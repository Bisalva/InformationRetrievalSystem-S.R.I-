#ifndef NODE_MANAGEMENT_H
#define NODE_MANAGEMENT_H

typedef struct InLinkNode {
    int node_id;
    struct InLinkNode *next;
} InLinkNode;

typedef struct Node {
    double pagerank;
    int out_links;
    double keyword_relevance;
    InLinkNode *in_links;
} Node;

/* Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */

Node* create_node(int out_links);
void add_inlink(Node *node, int source_id);
void free_nodes(Node *nodes[], int node_count);

#endif