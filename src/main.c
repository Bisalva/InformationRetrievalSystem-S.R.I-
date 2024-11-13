#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "datos_input.h"
#include "indice_invertido.h"
#include "web_graph.h"
#include "pagerank.h"

#define DAMPING_FACTOR 0.85
#define ITERATIONS 20

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "uso: %s <palabra_a_buscar> [<otra_palabra> ...]\n", argv[0]);
        return 1;
    }

    char stopwords[MAX_STOPWORDS][MAX_WORD_LENGTH];
    int num_stopwords = cargar_stopwords("docs/stopwords.txt", stopwords);
    if (num_stopwords == 0) {
        printf("No se cargaron los stopwords.\n");
        return 1;
    }

    IndiceInvertido indice;  
    inicializar_indice(&indice);

    // Inicializar el grafo de documentos
    int num_docs = 10;  // Asignar el número de documentos (o ajustarlo dinámicamente)
    Graph *graph = create_graph(num_docs);

    char carpeta[] = "./docs/";
    struct dirent *entrada;
    DIR *dir = opendir(carpeta); 

    if (dir == NULL) {
        perror("No se pudo abrir el directorio.");
        return 1;
    }

    int doc_id = 0;
    while ((entrada = readdir(dir)) != NULL) {
        if (verificar_extension_archivo(entrada->d_name)) {
            char ruta_completa[512];
            snprintf(ruta_completa, sizeof(ruta_completa), "%s%s", carpeta, entrada->d_name);

            char *contenido = leer_archivo(ruta_completa);
            if (contenido != NULL) {
                char *token = strtok(contenido, " \t\n\r");
                while (token != NULL) {
                    convertir_a_minusculas(token);
                    limpiar_palabra(token);
                    agregar_palabra(&indice, token, entrada->d_name);
                    token = strtok(NULL, " \t\n\r");
                }
                
                // Ejemplo de enlaces ficticios (actualiza según tus necesidades)
                if (doc_id > 0) {
                    add_link(graph, doc_id - 1, doc_id);  // Crear un enlace al siguiente documento
                }
                
                doc_id++;
                free(contenido);
            }
        }
    }
    closedir(dir);

    // Crear nodos para PageRank en función de los documentos
    Node *nodes[num_docs];
    for (int i = 0; i < num_docs; i++) {
        nodes[i] = create_node(1);  // Inicializa con un enlace de salida ficticio
    }

    // Asignar in-links basados en el grafo creado
    for (int i = 0; i < graph->num_docs; i++) {
        AdjListNode *node = graph->array[i].head;
        while (node != NULL) {
            add_inlink(nodes[node->dest], i);
            node = node->next;
        }
    }

    // Calcular PageRank
    calculate_pagerank(nodes, num_docs, DAMPING_FACTOR, ITERATIONS);

    // Imprimir los resultados de PageRank
    printf("\n=== PageRank Results ===\n");
    for (int i = 0; i < num_docs; i++) {
        printf("Documento %d - PageRank: %f\n", i, nodes[i]->pagerank);
    }

    // Liberar memoria del grafo y de PageRank
    free_graph(graph);
    free_nodes(nodes, num_docs);

    for (int i = 1; i < argc; i++) {
        char palabra_a_buscar[512];
        strncpy(palabra_a_buscar, argv[i], sizeof(palabra_a_buscar) - 1);
        palabra_a_buscar[sizeof(palabra_a_buscar) - 1] = '\0';
        convertir_a_minusculas(palabra_a_buscar);
        limpiar_palabra(palabra_a_buscar);

        if (es_stopword(palabra_a_buscar, stopwords, num_stopwords)) {
            printf("\"%s\" es un stopword. Omitiendo busqueda...\n", palabra_a_buscar);
            continue;
        }

        printf("\n\n=== RESULTADOS PARA \"%s\" ===\n", palabra_a_buscar);
        buscar_palabra(&indice, palabra_a_buscar);
    }

    liberar_indice(&indice);

    return 0;
}
