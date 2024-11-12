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
    int num_docs;        //num documentos
    AdjList *array;      //arreglo con las listas de adyacencia
} Graph;

//funciones gestion grafo
Graph* create_graph(int num_docs);
void add_link(Graph *graph, int src, int dest);
void display_graph(Graph *graph);
void free_graph(Graph *graph);

#endif
