#ifndef DOCS_MANAGEMENT_H
#define DOCS_MANAGEMENT_H

#include "indice_invertido.h"

/* Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */

void agregar_documento(PalabraNodo *nodo_palabra, const char *nombre_archivo);
void mostrar_vista_previa(const char *nombre_archivo, const char *palabra_original);

#endif