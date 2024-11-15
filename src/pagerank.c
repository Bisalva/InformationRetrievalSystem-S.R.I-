#include "pagerank.h"
#include <stdlib.h>
#include <string.h>

Node* create_node(int out_links) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->pagerank = 1.0;
    node->out_links = out_links;
    node->keyword_relevance = 0.0; // Inicializar la relevancia
    node->in_links = NULL;
    return node;
}

void add_inlink(Node *node, int source_id) {
    InLinkNode *new_inlink = (InLinkNode*)malloc(sizeof(InLinkNode));
    new_inlink->node_id = source_id;
    new_inlink->next = node->in_links;
    node->in_links = new_inlink;
}

// Establecer relevancia basada en palabras clave
void set_keyword_relevance(Node *nodes[], int node_count, const char *keywords[], int keyword_count) {
    for (int i = 0; i < node_count; i++) {
        nodes[i]->keyword_relevance = 0.0; // Reiniciar relevancia
        // Simular búsqueda de palabras clave en documentos
        for (int j = 0; j < keyword_count; j++) {
            if (/* Documento i contiene keywords[j] */) {
                nodes[i]->keyword_relevance += 1.0; // Incrementar relevancia
            }
        }
    }
}

void calculate_pagerank(Node *nodes[], int node_count, double damping_factor, int iterations) {
    double base_rank = (1.0 - damping_factor) / node_count;

    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < node_count; i++) {
            double rank_sum = 0.0;
            InLinkNode *inlink = nodes[i]->in_links;

            // Calcular suma PageRank
            while (inlink != NULL) {
                int source_id = inlink->node_id;
                rank_sum += nodes[source_id]->pagerank / nodes[source_id]->out_links;
                inlink = inlink->next;
            }

            // Actualizar PageRank con ponderación de relevancia
            nodes[i]->pagerank = base_rank + damping_factor * rank_sum;
            nodes[i]->pagerank *= (1.0 + nodes[i]->keyword_relevance); // Ajustar por relevancia
        }
    }
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
