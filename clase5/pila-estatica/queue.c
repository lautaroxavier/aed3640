#include <sys/param.h>
#include <stdio.h>
#include "queue.h"

void inicializar(Queue *pq)
{
    pq->front = 0;
    pq->rear = 0;
    pq->space = MAX_TAM;
}

int esta_vacia(Queue *pq)
{
    return pq->space == MAX_TAM;
}

int esta_llena(Queue *pq, size_t size)
{
    return pq->space < size + sizeof(size_t);
}

void vaciar(Queue *pq)
{
    pq->front = 0;
    pq->rear = 0;
    pq->space = MAX_TAM;
}

int encolar(Queue *pq, const void *pSource, size_t size)
{
    if (pq->space < size + sizeof(size_t))
    {
        return 0;
    }
    // guardar el tamaño del dato
    for (int i = 0; i < sizeof(size_t); i++)
    {
        memcpy(pq->vec + pq->rear, (char*)(&size) + i, 1);
        pq->rear = (pq->rear + 1) % MAX_TAM;
    }
    // guardar dato
    for (int j = 0; j < size; j++)
    {
        memcpy(pq->vec + pq->rear, pSource + j, 1);
        pq->rear = (pq->rear + 1) % MAX_TAM;
    }
    pq->space -= size + sizeof(size_t);
    return 1;
}

int desencolar(Queue *pq, void *pDest, size_t size)
{
    if (pq->space == MAX_TAM)
    {
        return 0;
    }
    // obtener tamanio
    size_t size_in_queue;
    for (int i = 0; i < sizeof(size_t); i++)
    {
        memcpy((char*)(&size_in_queue) + i, pq->vec + pq->front, 1);
        pq->front = (pq->front + 1) % MAX_TAM;
    }
    // copiar dato
    for (int j = 0; j < size_in_queue; j++)
    {
        if (j < size)
        {
            memcpy(pDest + j, pq->vec + pq->front, 1);
        }
        pq->front = (pq->front + 1) % MAX_TAM;
    }

    pq->space += sizeof(size_t) + size_in_queue;
    return 1;
}

int pispear(Queue *pq, void *pDest, size_t size)
{
    size_t size_in_queue;
    size_t front_start_value = pq->front;
    if (pq->space == MAX_TAM)
    {
        return 0;
    }
    // obtener tamanio
    for (int i = 0; i < sizeof(size_t); i++)
    {
        memcpy((char*)(&size_in_queue) + i, pq->vec + pq->front, 1);
        pq->front = (pq->front + 1) % MAX_TAM;
    }
    // copiar dato
    for (int j = 0; j < MIN(size_in_queue, size); j++)
    {
        memcpy(pDest + j, pq->vec + pq->front, 1);
        pq->front = (pq->front + 1) % MAX_TAM;
    }
    pq->front = front_start_value;
    return 1;
}
