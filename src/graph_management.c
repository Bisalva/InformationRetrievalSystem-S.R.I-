#include <stdio.h>
#include <stdlib.h>
#include "graph_management.h"
#include "graph_links.h"

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