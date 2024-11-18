#ifndef INDICE_INVERTIDO_H
#define INDICE_INVERTIDO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANO_TABLA 1000

typedef struct DocumentoNodo {
    char *nombre_archivo;
    int frecuencia;
    struct DocumentoNodo *siguiente;
} DocumentoNodo;

typedef struct PalabraNodo {
    char *palabra;
    DocumentoNodo *documentos;
    struct PalabraNodo *siguiente;
} PalabraNodo;

typedef struct {
    PalabraNodo *tabla[TAMANO_TABLA];
} IndiceInvertido;

#endif
