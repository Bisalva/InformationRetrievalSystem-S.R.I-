/* @Authors : Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */
#include "pagerank.h"
#include "node_management.h"
#include <stdlib.h>
#include <string.h>


void set_keyword_relevance(Node *nodes[], int node_count, const char *keywords[], int keyword_count, const char *documents[]) {
    for (int i = 0; i < node_count; i++) {
        nodes[i]->keyword_relevance = 0.0; //reiniciar relevancia
        //simular búsqueda de palabras clave en documentos
        for (int j = 0; j < keyword_count; j++) {
            if (strstr(documents[i], keywords[j]) != NULL) {
                nodes[i]->keyword_relevance += 1.0; //incrementar relevancia
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

            //calcular suma PageRank
            while (inlink != NULL) {
                int source_id = inlink->node_id;
                rank_sum += nodes[source_id]->pagerank / nodes[source_id]->out_links;
                inlink = inlink->next;
            }

            //actualizar PageRank con ponderacion de relevancia
            nodes[i]->pagerank = base_rank + damping_factor * rank_sum;
            nodes[i]->pagerank *= (1.0 + nodes[i]->keyword_relevance); //ajustar por relevancia
        }
    }
}
