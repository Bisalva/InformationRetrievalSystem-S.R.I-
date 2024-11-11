#ifndef PAGERANK_H
#define PAGERANK_H

//estructura nodo de entrada
typedef struct InLinkNode {
    int node_id;
    struct InLinkNode *next;
} InLinkNode;

//estructura nodos
typedef struct Node {
    double pagerank;
    int out_links;
    InLinkNode *in_links;
} Node;

//calculo pagerank
Node* create_node(int out_links);
void add_inlink(Node *node, int source_id);
void calculate_pagerank(Node *nodes[], int node_count, double damping_factor, int iterations);
void free_nodes(Node *nodes[], int node_count);

#endif
