#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "datos_input.h"
#include "indice_invertido.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "uso: %s <palabra_a_buscar> [<otra_palabra> ...]\n", argv[0]);
        return 1;
    }

    char stopwords[MAX_STOPWORDS][MAX_WORD_LENGTH];
    int num_stopwords = cargar_stopwords("docs/stopwords.txt", stopwords);
    if (num_stopwords == 0) {
        printf("No se cargaron los stopwords.\n");
        return 1;
    }

    IndiceInvertido indice;  
    inicializar_indice(&indice);

    char carpeta[] = "./docs/";
    struct dirent *entrada;
    DIR *dir = opendir(carpeta); 

    if (dir == NULL) {
        perror("No se pudo abrir el directorio.");
        return 1;
    }

    while ((entrada = readdir(dir)) != NULL) {
        if (verificar_extension_archivo(entrada->d_name)) {
            char ruta_completa[512];
            snprintf(ruta_completa, sizeof(ruta_completa), "%s%s", carpeta, entrada->d_name);

            char *contenido = leer_archivo(ruta_completa);
            if (contenido != NULL) {
                char *token = strtok(contenido, " \t\n\r");
                while (token != NULL) {
                    convertir_a_minusculas(token);
                    agregar_palabra(&indice, token, entrada->d_name);
                    token = strtok(NULL, " \t\n\r");
                }
                free(contenido);
            }
        }
    }

    closedir(dir);

    for (int i = 1; i < argc; i++) {
        char palabra_a_buscar[512];
        strncpy(palabra_a_buscar, argv[i], sizeof(palabra_a_buscar) - 1);
        palabra_a_buscar[sizeof(palabra_a_buscar) - 1] = '\0';
        convertir_a_minusculas(palabra_a_buscar);

        if (es_stopword(palabra_a_buscar, stopwords, num_stopwords)) {
            printf("\"%s\" es un stopword. Omitiendo busqueda...\n", palabra_a_buscar);
            continue;
        }

        printf("\n\n=== RESULTADOS PARA \"%s\" ===\n", palabra_a_buscar);
        buscar_palabra(&indice, palabra_a_buscar);
    }

    liberar_indice(&indice);

    return 0;
}
