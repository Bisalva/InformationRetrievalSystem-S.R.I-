#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "datos_input.h"
#define MAX_ARCHIVO_MB 104857600 // Tamaño máximo de archivo = 100MB


// Verifica la extension del archivo
int verificar_extension_archivo(const char *nombre_archivo){
    const char *extensiones_texto[] = {".txt", ".md", ".csv", ".log", ".ini", ".conf", ".rst", ".tex", NULL};
    size_t len_nombre = strlen(nombre_archivo); //tamaño del nombre del archivo

    for (int i = 0; extensiones_texto[i] != NULL; i++) {
        size_t len_extension = strlen(extensiones_texto[i]); // tamaño de la extension
        //Si termina en alguna extension de "extensiones_texto"
        if (len_nombre > len_extension && strcmp(nombre_archivo + len_nombre - len_extension, extensiones_texto[i]) == 0) {
            return 1;  // Si tiene una extension de "extensiones_texto"
        }
    }

    return 0;  // No tiene una extension nombrada
}

// Lee el archivo
char* leer_archivo(const char *archivo){
    FILE *archivo_input = fopen(archivo, "r");

    if (!archivo_input) {
        perror("No se pudo abrir el archivo");
        return NULL;
    }

    char *contenido = malloc(MAX_ARCHIVO_MB);
    
    if (contenido == NULL) {
        perror("No se pudo reservar memoria");
        fclose(archivo_input);
        return NULL;
    }

    size_t tamano_leido = fread(contenido, 1, MAX_ARCHIVO_MB - 1, archivo_input);
    contenido[tamano_leido] = '\0';  // revisa si el archivo termino

    fclose(archivo_input);
    return contenido;
}


Nodo* agregar_nodo(Nodo *inicio, const char *nombre_archivo, const char *contenido){
    Nodo *nuevo_nodo = malloc(sizeof(Nodo));
    if (nuevo_nodo == NULL) {
        perror("No se pudo reservar memoria para un nuevo nodo");
        return inicio; //vuelve al inicio la lista
    }

    // guarda memoria para el nombre del archivo
    nuevo_nodo->nombre_archivo = malloc(strlen(nombre_archivo) + 1);
    if (nuevo_nodo->nombre_archivo == NULL) {
        perror("No se pudo reservar memoria para el nombre del archivo");
        free(nuevo_nodo);
        return inicio;
    }
    strcpy(nuevo_nodo->nombre_archivo, nombre_archivo);

    // guarda memoria para el contenido y copiarlo
    nuevo_nodo->contenido = malloc(strlen(contenido) + 1);
    if (nuevo_nodo->contenido == NULL) {
        perror("No se pudo reservar memoria para el contenido del archivo");
        free(nuevo_nodo->nombre_archivo);
        free(nuevo_nodo);
        return inicio;
    }
    strcpy(nuevo_nodo->contenido, contenido);

    nuevo_nodo->siguiente = NULL;

    // Lista vacia = vuelve al primer nodo
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