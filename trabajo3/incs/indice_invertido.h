#ifndef INDICE_INVERTIDO_H
#define INDICE_INVERTIDO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANO_TABLA 1000
#define MAX_STOPWORDS 1000
#define MAX_WORD_LENGTH 50

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

int cargar_stopwords(const char *nombre_archivo, char stopwords[][MAX_WORD_LENGTH]);
int es_stopword(const char *palabra, char stopwords[][MAX_WORD_LENGTH], int num_stopwords);
void inicializar_indice(IndiceInvertido *indice);
void agregar_palabra(IndiceInvertido *indice, const char *palabra, const char *nombre_archivo);
void buscar_palabra(IndiceInvertido *indice, const char *palabra);
void liberar_indice(IndiceInvertido *indice);
void convertir_a_minusculas(char *palabra);

#endif
