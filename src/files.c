#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "files.h"
#define MAX_ARCHIVO_MB 104857600 // Tamaño máximo de archivo = 100MB


// Verifica la extension del archivo
int verificar_extension_archivo(const char *nombre_archivo){
    
    const char *extensiones_texto[] = {".txt", ".md", ".csv", ".log", ".ini", ".conf", ".rst", ".doc", ".docx",".pdf",".tex", NULL};
    size_t len_nombre = strlen(nombre_archivo);

    for (int i = 0; extensiones_texto[i] != NULL; i++) {
        size_t len_extension = strlen(extensiones_texto[i]);
        //Si termina en alguna extension de "extensiones_texto"
        if (len_nombre > len_extension && strcmp(nombre_archivo + len_nombre - len_extension, extensiones_texto[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

char* leer_archivo(const char *archivo){
    FILE *archivo_input = fopen(archivo, "r");

    if (!archivo_input) {
        perror("No se pudo abrir el archivo");
        return NULL;
    }

    char *contenido = malloc(MAX_ARCHIVO_MB);
    
    if (contenido == NULL) {
        perror("No se pudo reservar memoria.");
        fclose(archivo_input);
        return NULL;
    }

    size_t tamano_leido = fread(contenido, 1, MAX_ARCHIVO_MB - 1, archivo_input);
    contenido[tamano_leido] = '\0';

    fclose(archivo_input);
    return contenido;
}