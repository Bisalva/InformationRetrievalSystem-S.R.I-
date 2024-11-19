#ifndef INDEX_OPERATIONS_H
#define INDEX_OPERATIONS_H

#include "indice_invertido.h"

/* Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */

void agregar_palabra(IndiceInvertido *indice, const char *palabra_original, const char *nombre_archivo);
void buscar_palabra(IndiceInvertido *indice, const char *palabra);

#endif