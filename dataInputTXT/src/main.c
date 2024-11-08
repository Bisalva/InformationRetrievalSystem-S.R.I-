#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "datos_input.h"


int main(){
    char carpeta[] = "./"; //lee la carpeta "./" = Actual ; "./docs/" == ARREGLAR ya que no lee desde la carpeta docs y deberia :c
    struct dirent *entrada;
    DIR *dir = opendir(carpeta);

    if (dir == NULL) {
        perror("No se pudo abrir el directorio");
        return 1;
    }

    Nodo *lista = NULL; 

    while ((entrada = readdir(dir)) != NULL) {
        // Filtro de archivos
        if (verificar_extension_archivo(entrada->d_name)) {
            // Lee el archivo
            char *contenido = leer_archivo(entrada->d_name);
            if (contenido != NULL) {
                lista = agregar_nodo(lista, entrada->d_name, contenido);
                free(contenido);
            }
        }
    }

    closedir(dir);

    // printf (pasar a funcion)
    printf("Archivos de tipo texto encontrados y su contenido:\n");
    Nodo *temp = lista;
    while (temp != NULL) {
        printf("\nArchivo: %s\n", temp->nombre_archivo);
        printf("Contenido:\n%s\n", temp->contenido);
        temp = temp->siguiente;
    }

    liberar_lista(lista);

    return 0;
}