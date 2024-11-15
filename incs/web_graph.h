#ifndef WEB_GRAPH_H
#define WEB_GRAPH_H

//estructura nodo
typedef struct AdjListNode {
    int dest;
    struct AdjListNode *next;
} AdjListNode;

//estructura aristas
typedef struct AdjList {
    int document_id;
    AdjListNode *head;
} AdjList;

//estructura grafo
typedef struct Graph {
    int num_docs;
    AdjList *array;
} Graph;

//funciones gestion grafo
Graph* create_graph(int num_docs);
void add_link(Graph *graph, int src, int dest);
void connect_graphs(Graph *graph1, Graph *graph2, int src, int dest);
void display_graph(Graph *graph);
void free_graph(Graph *graph);

#endif

