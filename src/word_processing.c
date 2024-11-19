#include <ctype.h>
#include "word_processing.h"

/* Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */

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