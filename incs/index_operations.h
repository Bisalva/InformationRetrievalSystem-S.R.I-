/* @Authors : Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */
#ifndef INDEX_OPERATIONS_H
#define INDEX_OPERATIONS_H

#include "indice_invertido.h"


void agregar_palabra(IndiceInvertido *indice, const char *palabra_original, const char *nombre_archivo);
void buscar_palabra(IndiceInvertido *indice, const char *palabra);

#endif