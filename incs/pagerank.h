#ifndef PAGERANK_H
#define PAGERANK_H

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

Node* create_node(int out_links);
void add_inlink(Node *node, int source_id);
void calculate_pagerank(Node *nodes[], int node_count, double damping_factor, int iterations);
void set_keyword_relevance(Node *nodes[], int node_count, const char *keywords[], int keyword_count);
void free_nodes(Node *nodes[], int node_count);

#endif
