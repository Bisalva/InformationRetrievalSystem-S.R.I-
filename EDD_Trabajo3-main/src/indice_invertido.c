#include "indice_invertido.h"
#include <ctype.h>

#define MAX_STOPWORDS 1000
#define MAX_WORD_LENGTH 50

unsigned int hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % TAMANO_TABLA;
}

void inicializar_indice(IndiceInvertido *indice) {
    for (int i = 0; i < TAMANO_TABLA; i++) {
        indice->tabla[i] = NULL;
    }
}

void convertir_a_minusculas(char *palabra) {
    for (int i = 0; palabra[i]; i++) {
        palabra[i] = tolower((unsigned char)palabra[i]);
    }
}

void limpiar_palabra(char *palabra) {
    int inicio = 0;
    int fin = strlen(palabra) - 1;

    while (inicio <= fin && !isalnum((unsigned char)palabra[inicio])) {
        inicio++;
    }

    while (fin >= inicio && !isalnum((unsigned char)palabra[fin])) {
        fin--;
    }

    if (inicio > 0 || fin < (int)strlen(palabra) - 1) {
        int longitud = fin - inicio + 1;
        memmove(palabra, &palabra[inicio], longitud);
        palabra[longitud] = '\0';  
    }
}

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

void agregar_palabra(IndiceInvertido *indice, const char *palabra_original, const char *nombre_archivo) {
    char palabra[512];
    strncpy(palabra, palabra_original, sizeof(palabra) - 1);
    palabra[sizeof(palabra) - 1] = '\0';
    convertir_a_minusculas(palabra);
    limpiar_palabra(palabra);  

    unsigned int index = hash(palabra);
    PalabraNodo *nodo_palabra = indice->tabla[index];

    while (nodo_palabra != NULL) {
        if (strcmp(nodo_palabra->palabra, palabra) == 0) {
            agregar_documento(nodo_palabra, nombre_archivo);
            return;
        }
        nodo_palabra = nodo_palabra->siguiente;
    }

    nodo_palabra = malloc(sizeof(PalabraNodo));
    nodo_palabra->palabra = strdup(palabra);
    nodo_palabra->documentos = NULL;
    nodo_palabra->siguiente = indice->tabla[index];
    indice->tabla[index] = nodo_palabra;

    agregar_documento(nodo_palabra, nombre_archivo);
}

void buscar_palabra(IndiceInvertido *indice, const char *palabra_original) {
    char palabra[512];
    strncpy(palabra, palabra_original, sizeof(palabra) - 1);
    palabra[sizeof(palabra) - 1] = '\0';
    convertir_a_minusculas(palabra);
    limpiar_palabra(palabra); 

    unsigned int index = hash(palabra);
    PalabraNodo *nodo_palabra = indice->tabla[index];

    int encontrada = 0;

    printf("Buscando la palabra \"%s\":\n", palabra_original);

    while (nodo_palabra != NULL) {
        if (strcmp(nodo_palabra->palabra, palabra) == 0) {
            printf("\nDocumentos que contienen la palabra \"%s\":\n", palabra_original);
            DocumentoNodo *doc_nodo = nodo_palabra->documentos;
            while (doc_nodo != NULL) {
                printf("  - %s (Frecuencia: %d)\n", doc_nodo->nombre_archivo, doc_nodo->frecuencia);
                mostrar_vista_previa(doc_nodo->nombre_archivo, palabra);
                doc_nodo = doc_nodo->siguiente;
            }
            encontrada = 1;
            break;
        }
        nodo_palabra = nodo_palabra->siguiente;
    }

    if (!encontrada) {
        printf("\nLa palabra \"%s\" no se encontro en ningun documento.\n", palabra_original);
    }
    printf("\n");
}

void liberar_indice(IndiceInvertido *indice) {
    for (int i = 0; i < TAMANO_TABLA; i++) {
        PalabraNodo *nodo_palabra = indice->tabla[i];
        while (nodo_palabra != NULL) {
            DocumentoNodo *doc_nodo = nodo_palabra->documentos;
            while (doc_nodo) {
                DocumentoNodo *temp_doc = doc_nodo;
                doc_nodo = doc_nodo->siguiente;
                free(temp_doc->nombre_archivo);
                free(temp_doc);
            }
            PalabraNodo *temp_palabra = nodo_palabra;
            nodo_palabra = nodo_palabra->siguiente;
            free(temp_palabra->palabra);
            free(temp_palabra);
        }
    }
}
