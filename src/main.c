/* @Authors : Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "indice_invertido.h"
#include "stopwords.h"
#include "index_management.h"
#include "index_operations.h"
#include "pagerank.h"
#include "graph_links.h"
#include "graph_management.h"
#include "files.h"
#include "word_processing.h"
#include "nodes.h"
#include "node_management.h"
#include "hash_utils.h"
#include "memory.h"
#include "docs_management.h"

#define DAMPING_FACTOR 0.85
#define ITERATIONS 20
#define TOTAL_DOCS 10


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "uso: %s <palabra_a_buscar> [<otra_palabra> ...]\n", argv[0]);
        return 1;
    }

    // Cargar stopwords
    char stopwords[MAX_STOPWORDS][MAX_WORD_LENGTH];
    int num_stopwords = cargar_stopwords("docs/stopwords.txt", stopwords);
    if (num_stopwords == 0) {
        printf("No se cargaron los stopwords.\n");
        return 1;
    }

    // Crear índice invertido
    IndiceInvertido indice;
    inicializar_indice(&indice);

    // Dividir documentos entre dos webs
    int docs_web1 = TOTAL_DOCS / 2;
    int docs_web2 = TOTAL_DOCS - docs_web1;

    // Crear los grafos
    Graph *web1 = create_graph(docs_web1);
    Graph *web2 = create_graph(docs_web2);

    if (web1 == NULL || web2 == NULL) {
        fprintf(stderr, "Error al crear los grafos.\n");
        return 1;
    }

    // Agregar enlaces en Web 1
    for (int i = 0; i < docs_web1 - 1; i++) {
        add_link(web1, i, i + 1);
    }

    // Agregar enlaces en Web 2
    for (int i = 0; i < docs_web2 - 1; i++) {
        add_link(web2, i, i + 1);
    }

    // Conectar las dos webs
    if (docs_web1 > 0 && docs_web2 > 0) {
    connect_graphs(web1, web2, docs_web1 - 1, 0);
    }

    // Procesar documentos desde la carpeta "docs"
    char carpeta[] = "./docs/";
    struct dirent *entrada;
    DIR *dir = opendir(carpeta);

    if (dir == NULL) {
        perror("No se pudo abrir el directorio.");
        return 1;
    }

    int doc_id = 0;
    while ((entrada = readdir(dir)) != NULL) {
        if (!verificar_extension_archivo(entrada->d_name)) {
            continue;
        }

        char ruta_completa[512];
        snprintf(ruta_completa, sizeof(ruta_completa), "%s%s", carpeta, entrada->d_name);

        char *contenido = leer_archivo(ruta_completa);
        if (contenido == NULL) {
            fprintf(stderr, "Error al leer el archivo: %s\n", ruta_completa);
            continue;
        }

        // Procesar contenido del archivo
        char *token = strtok(contenido, " \t\n\r");
        while (token != NULL) {
            convertir_a_minusculas(token);
            limpiar_palabra(token);
            agregar_palabra(&indice, token, entrada->d_name);
            token = strtok(NULL, " \t\n\r");
        }

        // Crear enlaces ficticios entre documentos en Web 1 o Web 2
        if (doc_id < docs_web1 - 1) {
            add_link(web1, doc_id, doc_id + 1);
        } else if (doc_id >= docs_web1 && doc_id < TOTAL_DOCS - 1) {
            add_link(web2, doc_id - docs_web1, doc_id - docs_web1 + 1);
        }

        doc_id++;
        free(contenido);
    }
    closedir(dir);

    // Crear nodos para PageRank
    Node *nodes_web1[docs_web1];
    Node *nodes_web2[docs_web2];

    for (int i = 0; i < docs_web1; i++) {
        nodes_web1[i] = create_node(1);
        if (nodes_web1[i] == NULL) {
            fprintf(stderr, "Error al crear nodo %d en Web 1.\n", i);
            return 1;
        }
    }
    for (int i = 0; i < docs_web2; i++) {
        nodes_web2[i] = create_node(1);
        if (nodes_web2[i] == NULL) {
            fprintf(stderr, "Error al crear nodo %d en Web 2.\n", i);
            return 1;
        }
    }

    // Asignar in-links basados en los grafos
    for (int i = 0; i < web1->num_docs; i++) {
        AdjListNode *node = web1->array[i].head;
        while (node != NULL) {
            if (node->dest < 0 || node->dest >= docs_web1) {
                fprintf(stderr, "Índice fuera de rango en Web 1: %d\n", node->dest);
                break;
            }
            add_inlink(nodes_web1[node->dest], i);
            node = node->next;
        }
    }
    for (int i = 0; i < web2->num_docs; i++) {
        AdjListNode *node = web2->array[i].head;
        while (node != NULL) {
            if (node->dest < 0 || node->dest >= docs_web2) {
                fprintf(stderr, "Índice fuera de rango en Web 2: %d\n", node->dest);
                break;
            }
            add_inlink(nodes_web2[node->dest], i);
            node = node->next;
        }
    }


    // Calcular PageRank
    calculate_pagerank(nodes_web1, docs_web1, DAMPING_FACTOR, ITERATIONS);
    calculate_pagerank(nodes_web2, docs_web2, DAMPING_FACTOR, ITERATIONS);

    // Imprimir resultados de PageRank
    printf("\n=== PageRank Resultados Web 1 ===\n");
    for (int i = 0; i < docs_web1; i++) {
        printf("Documento %d - PageRank: %f\n", i, nodes_web1[i]->pagerank);
    }

    printf("\n=== PageRank Resultados Web 2 ===\n");
    for (int i = 0; i < docs_web2; i++) {
        printf("Documento %d - PageRank: %f\n", i, nodes_web2[i]->pagerank);
    }

    // Procesar palabras clave de búsqueda
    for (int i = 1; i < argc; i++) {
        char palabra_a_buscar[512];
        strncpy(palabra_a_buscar, argv[i], sizeof(palabra_a_buscar) - 1);
        palabra_a_buscar[sizeof(palabra_a_buscar) - 1] = '\0';
        convertir_a_minusculas(palabra_a_buscar);
        limpiar_palabra(palabra_a_buscar);

        if (es_stopword(palabra_a_buscar, stopwords, num_stopwords)) {
            printf("\"%s\" es un stopword. Omitiendo búsqueda...\n", palabra_a_buscar);
            continue;
        }

        printf("\n\n=== RESULTADOS PARA \"%s\" ===\n", palabra_a_buscar);
        buscar_palabra(&indice, palabra_a_buscar);
    }


    // Liberar memoria
    if (web1 != NULL) free_graph(web1);
    if (web2 != NULL) free_graph(web2);
    if (nodes_web1 != NULL) free_nodes(nodes_web1, docs_web1);
    if (nodes_web2 != NULL) free_nodes(nodes_web2, docs_web2);
    liberar_indice(&indice);

    return 0;
}
