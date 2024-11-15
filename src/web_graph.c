#include <stdio.h>
#include <stdlib.h>
#include "web_graph.h"

//crear nodo en lista de adyacencia
AdjListNode* create_adj_list_node(int dest) {
    AdjListNode *newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

//crear grafo
Graph* create_graph(int num_docs) {
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->num_docs = num_docs;

    //crear arreglo con lista de adyacencia
    graph->array = (AdjList*)malloc(num_docs * sizeof(AdjList));

    //inicializar aristas
    for (int i = 0; i < num_docs; i++) {
        graph->array[i].document_id = i;
        graph->array[i].head = NULL;
    }
    return graph;
}

//funcion agregar arista
void add_link(Graph *graph, int src, int dest) {
    if (src >= graph->num_docs || dest >= graph->num_docs) {
        printf("Error: Nodo fuera de rango.\n");
        return;
    }
    AdjListNode *newNode = create_adj_list_node(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

//funcion para conectar dos grafos
void connect_graphs(Graph *graph1, Graph *graph2, int src, int dest) {
    if (src >= graph1->num_docs || dest >= graph2->num_docs) {
        printf("Error: Nodo fuera de rango.\n");
        return;
    }
    AdjListNode *newNode = create_adj_list_node(dest + graph1->num_docs);
    newNode->next = graph1->array[src].head;
    graph1->array[src].head = newNode;
}

//funcion mostrar grafo
void display_graph(Graph *graph) {
    for (int i = 0; i < graph->num_docs; i++) {
        AdjListNode *node = graph->array[i].head;
        printf("Document %d:", graph->array[i].document_id);
        while (node) {
            printf(" -> %d", node->dest);
            node = node->next;
        }
        printf("\n");
    }
}

//liberar memoria grafo
void free_graph(Graph *graph) {
    for (int i = 0; i < graph->num_docs; i++) {
        AdjListNode *node = graph->array[i].head;
        while (node) {
            AdjListNode *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(graph->array);
    free(graph);
}
