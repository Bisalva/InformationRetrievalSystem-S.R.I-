#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stopwords.h"

/* Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */

// carga las stopwords desde un archivo a un arreglo
int cargar_stopwords(const char *nombre_archivo, char stopwords[][MAX_WORD_LENGTH]) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo de stopwords.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(archivo, "%49s", stopwords[count]) == 1 && count < MAX_STOPWORDS) {
        count++;
    }
    fclose(archivo);
    return count;
}

int es_stopword(const char *palabra, char stopwords[][MAX_WORD_LENGTH], int num_stopwords) {
    for (int i = 0; i < num_stopwords; i++) {
        if (strcmp(palabra, stopwords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}