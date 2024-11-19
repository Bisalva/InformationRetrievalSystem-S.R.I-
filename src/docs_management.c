/* @Authors : Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */
#include <ctype.h>
#include "docs_management.h"
#include "word_processing.h"


void agregar_documento(PalabraNodo *nodo_palabra, const char *nombre_archivo) {
    DocumentoNodo *doc_nodo = nodo_palabra->documentos;

    while (doc_nodo != NULL) {
        if (strcmp(doc_nodo->nombre_archivo, nombre_archivo) == 0) {
            doc_nodo->frecuencia++;
            return;
        }
        doc_nodo = doc_nodo->siguiente;
    }

    DocumentoNodo *nuevo_documento = malloc(sizeof(DocumentoNodo));
    nuevo_documento->nombre_archivo = strdup(nombre_archivo);
    nuevo_documento->frecuencia = 1;
    nuevo_documento->siguiente = nodo_palabra->documentos;
    nodo_palabra->documentos = nuevo_documento;
}

void mostrar_vista_previa(const char *nombre_archivo, const char *palabra_original) {
    char ruta_completa[512];
    snprintf(ruta_completa, sizeof(ruta_completa), "./docs/%s", nombre_archivo);

    FILE *file = fopen(ruta_completa, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo para vista previa.");
        return;
    }

    char linea[512];
    int contador = 0;

    char palabra_min[512];
    strncpy(palabra_min, palabra_original, sizeof(palabra_min) - 1);
    palabra_min[sizeof(palabra_min) - 1] = '\0';
    convertir_a_minusculas(palabra_min);

    while (fgets(linea, sizeof(linea), file) != NULL) {
        char linea_minusculas[512];
        strncpy(linea_minusculas, linea, sizeof(linea_minusculas) - 1);
        linea_minusculas[sizeof(linea_minusculas) - 1] = '\0';
        convertir_a_minusculas(linea_minusculas);

        char *pos_palabra = strstr(linea_minusculas, palabra_min);
        if (pos_palabra != NULL) {
            int posicion = pos_palabra - linea_minusculas;
            int inicio = posicion, fin = posicion + strlen(palabra_min);

            int palabras_antes = 0;
            while (inicio > 0 && palabras_antes < 5) {
                if (linea_minusculas[inicio - 1] == ' ') {
                    palabras_antes++;
                }
                inicio--;
            }

            int palabras_despues = 0;
            while (linea[fin] != '\0' && palabras_despues < 5) {
                if (linea_minusculas[fin] == ' ') {
                    palabras_despues++;
                }
                fin++;
            }

            printf("    ");
            for (int i = inicio; i < fin; i++) {
                printf("%c", linea[i]);
            }
            printf("\n");

            contador++;
            if (contador >= 3) break;  
        }
    }

    fclose(file);
    printf("\n");
}