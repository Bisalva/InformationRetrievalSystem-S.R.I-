#include <stdio.h>
#include <stdlib.h>
#include "graph_links.h"
#include "graph_management.h"

AdjListNode* create_adj_list_node(int dest) {
    AdjListNode *newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

//funcion agregar arista
void add_link(Graph *graph, int src, int dest) {
    if (src < 0 || src >= graph->num_docs || dest < 0 || dest >= graph->num_docs) {
        fprintf(stderr, "Error: enlace inválido (%d -> %d).\n", src, dest);
        return;
    }

    //verificar si ya existe el enlace
    AdjListNode *current = graph->array[src].head;
    while (current != NULL) {
        if (current->dest == dest) {
            return;  // Enlace ya existe
        }
        current = current->next;
    }

    //agregar enlace si no existe
    AdjListNode *newNode = create_adj_list_node(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

void connect_graphs(Graph *graph1, Graph *graph2, int src, int dest) {
    if (src < 0 || src >= graph1->num_docs || dest < 0 || dest >= graph2->num_docs) {
        fprintf(stderr, "Error: Nodo fuera de rango al conectar grafos (%d -> %d).\n", src, dest);
        return;
    }

    //conectar usando el indice destino real de Web 2
    AdjListNode *newNode = create_adj_list_node(dest);
    newNode->next = graph1->array[src].head;
    graph1->array[src].head = newNode;
}