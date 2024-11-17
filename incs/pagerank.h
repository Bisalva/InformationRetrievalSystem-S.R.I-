#ifndef PAGERANK_H
#define PAGERANK_H

//define un nodo de enlace entrante
typedef struct InLinkNode {
    int node_id;
    struct InLinkNode *next;
} InLinkNode;

//define un nodo principal
typedef struct Node {
    double pagerank;
    int out_links;
    double keyword_relevance;
    InLinkNode *in_links;
} Node;

//crea un nuevo nodo con un numero especifico de enlaces salientes
Node* create_node(int out_links);
//agrega un enlace entrante a un nodo especifico
void add_inlink(Node *node, int source_id);
//calcula el PageRank de un conjunto de nodos utilizando el algoritmo de PageRank
void calculate_pagerank(Node *nodes[], int node_count, double damping_factor, int iterations);
//establece la relevancia de palabras clave para un conjunto de nodos
void set_keyword_relevance(Node *nodes[], int node_count, const char *keywords[], int keyword_count, const char *documents[]);
//libera la memoria asignada a un conjunto de nodos
void free_nodes(Node *nodes[], int node_count);

#endif
