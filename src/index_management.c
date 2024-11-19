#include <ctype.h>
#include "index_management.h"

/* Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */

void inicializar_indice(IndiceInvertido *indice) {
    for (int i = 0; i < TAMANO_TABLA; i++) {
        indice->tabla[i] = NULL;
    }
}

void liberar_indice(IndiceInvertido *indice) {
    for (int i = 0; i < TAMANO_TABLA; i++) {
        PalabraNodo *nodo_palabra = indice->tabla[i];
        while (nodo_palabra != NULL) {
            DocumentoNodo *doc_nodo = nodo_palabra->documentos;
            while (doc_nodo) {
                DocumentoNodo *temp_doc = doc_nodo;
                doc_nodo = doc_nodo->siguiente;
                free(temp_doc->nombre_archivo);
                free(temp_doc);
            }
            PalabraNodo *temp_palabra = nodo_palabra;
            nodo_palabra = nodo_palabra->siguiente;
            free(temp_palabra->palabra);
            free(temp_palabra);
        }
    }
}
