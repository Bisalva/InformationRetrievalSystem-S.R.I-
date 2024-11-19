/* @Authors : Diego Galindo, Francisco Mercado, Benjamin Sanhueza, Duvan Figueroa */
#ifndef STOPWORDS_H
#define STOPWORDS_H

#define MAX_STOPWORDS 1000
#define MAX_WORD_LENGTH 50

int cargar_stopwords(const char *nombre_archivo, char stopwords[][MAX_WORD_LENGTH]);
int es_stopword(const char *palabra, char stopwords[][MAX_WORD_LENGTH], int num_stopwords);

#endif