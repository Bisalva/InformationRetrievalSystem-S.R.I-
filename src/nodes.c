/* @Authors : Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "nodes.h"

Nodo* agregar_nodo(Nodo *inicio, const char *nombre_archivo, const char *contenido){
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    if (nuevo_nodo == NULL) {
        perror("No se pudo reservar memoria para un nuevo nodo.");
        return inicio; //vuelve al inicio la lista
    }

    // guarda memoria para el nombre del doc
    nuevo_nodo->nombre_archivo = malloc(strlen(nombre_archivo) + 1);
    if (nuevo_nodo->nombre_archivo == NULL) {
        perror("No se pudo reservar memoria para el nombre del archivo.");
        free(nuevo_nodo);
        return inicio;
    }
    strcpy(nuevo_nodo->nombre_archivo, nombre_archivo);

    //guarda memoria para el contenido del doc y copiarlo
    nuevo_nodo->contenido = malloc(strlen(contenido) + 1);
    if (nuevo_nodo->contenido == NULL) {
        perror("No se pudo reservar memoria para el contenido del archivo.");
        free(nuevo_nodo->nombre_archivo);
        free(nuevo_nodo);
        return inicio;
    }
    strcpy(nuevo_nodo->contenido, contenido);

    nuevo_nodo->siguiente = NULL;

    //lista vacia = vuelve al primer nodo
    if (inicio == NULL) {
        return nuevo_nodo;
    }
    // sigue con normalidad
    Nodo *temp = inicio;
    while (temp->siguiente != NULL) {
        temp = temp->siguiente;
    }
    temp->siguiente = nuevo_nodo;

    return inicio;
}