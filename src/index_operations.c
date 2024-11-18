#include <ctype.h>
#include "index_operations.h"
#include "word_processing.h"
#include "docs_management.h"
#include "hash_utils.h"

void agregar_palabra(IndiceInvertido *indice, const char *palabra_original, const char *nombre_archivo) {
    char palabra[512];
    strncpy(palabra, palabra_original, sizeof(palabra) - 1);
    palabra[sizeof(palabra) - 1] = '\0';
    convertir_a_minusculas(palabra);
    limpiar_palabra(palabra);  

    unsigned int index = hash(palabra);
    PalabraNodo *nodo_palabra = indice->tabla[index];

    while (nodo_palabra != NULL) {
        if (strcmp(nodo_palabra->palabra, palabra) == 0) {
            agregar_documento(nodo_palabra, nombre_archivo);
            return;
        }
        nodo_palabra = nodo_palabra->siguiente;
    }

    nodo_palabra = malloc(sizeof(PalabraNodo));
    nodo_palabra->palabra = strdup(palabra);
    nodo_palabra->documentos = NULL;
    nodo_palabra->siguiente = indice->tabla[index];
    indice->tabla[index] = nodo_palabra;

    agregar_documento(nodo_palabra, nombre_archivo);
}

void buscar_palabra(IndiceInvertido *indice, const char *palabra_original) {
    char palabra[512];
    strncpy(palabra, palabra_original, sizeof(palabra) - 1);
    palabra[sizeof(palabra) - 1] = '\0';
    convertir_a_minusculas(palabra);
    limpiar_palabra(palabra); 

    unsigned int index = hash(palabra);
    PalabraNodo *nodo_palabra = indice->tabla[index];

    int encontrada = 0;

    printf("Buscando la palabra \"%s\":\n", palabra_original);

    while (nodo_palabra != NULL) {
        if (strcmp(nodo_palabra->palabra, palabra) == 0) {
            printf("\nDocumentos que contienen la palabra \"%s\":\n", palabra_original);
            DocumentoNodo *doc_nodo = nodo_palabra->documentos;
            while (doc_nodo != NULL) {
                printf("  - %s (Frecuencia: %d)\n", doc_nodo->nombre_archivo, doc_nodo->frecuencia);
                mostrar_vista_previa(doc_nodo->nombre_archivo, palabra);
                doc_nodo = doc_nodo->siguiente;
            }
            encontrada = 1;
            break;
        }
        nodo_palabra = nodo_palabra->siguiente;
    }

    if (!encontrada) {
        printf("\nLa palabra \"%s\" no se encontro en ningun documento.\n", palabra_original);
    }
    printf("\n");
}