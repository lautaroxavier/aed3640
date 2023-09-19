#ifndef PILA_ESTATICA_QUEUE_H
#define PILA_ESTATICA_QUEUE_H

#include <string.h>

#define MAX_TAM 1000

typedef struct
{
    char vec[MAX_TAM];
    size_t front;
    size_t rear;
    size_t space;
}
Queue;

void inicializar(Queue *pq);

int esta_vacia(Queue *pq);

int esta_llena(Queue *pq, size_t size);

void vaciar(Queue *pq);

int encolar(Queue *pq, const void *pSource, size_t size);

int desencolar(Queue *pq, void *pDest, size_t size);

int pispear(Queue *pq, void *pDest, size_t size);

#endif //PILA_ESTATICA_QUEUE_H
