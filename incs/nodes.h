#ifndef NODES_H
#define NODES_H

typedef struct Nodo {
    char *nombre_archivo;
    char *contenido;
    struct Nodo *siguiente;
} Nodo;

Nodo* agregar_nodo(Nodo *inicio, const char *nombre_archivo, const char *contenido);

#endif