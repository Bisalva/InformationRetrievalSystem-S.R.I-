/* @Authors : Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */
#include <ctype.h>
#include "hash_utils.h"


unsigned int hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % TAMANO_TABLA;
}
