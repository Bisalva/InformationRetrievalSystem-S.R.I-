#ifndef ADJ_LIST_H
#define ADJ_LIST_H

// Nodo de la lista de adyacencia
typedef struct AdjListNode {
    int dest;
    struct AdjListNode *next;
} AdjListNode;

// Lista de adyacencia
typedef struct AdjList {
    int document_id;
    AdjListNode *head;
} AdjList;

#endif
