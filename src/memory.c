/* @Authors : Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "memory.h"
#include "nodes.h"

void liberar_memoria(Nodo *inicio){
    Nodo *temp;
    while (inicio != NULL) {
        temp = inicio;
        inicio = inicio->siguiente;

        free(temp->nombre_archivo);
        free(temp->contenido);
        free(temp);
    }
}
