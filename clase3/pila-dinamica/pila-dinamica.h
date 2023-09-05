#ifndef PILA_DINAMICA_PILA_DINAMICA_H
#define PILA_DINAMICA_PILA_DINAMICA_H

#include <malloc.h>
#include <string.h>
#include <stddef.h>

typedef struct sNodo
{
    void *elem;
    size_t size;
    struct sNodo *next;
}
nodo;

typedef nodo* pila;

int ponerEnPila(pila *pPila, const void *pSource, size_t sz);
int sacarDePila(pila *pPila, void *pDest, size_t sz);
void crearPila(pila *pPila);
void vaciarPila(pila *pPila);
int verTope(const pila *pPila, void *pDest, size_t sz);
int pilaLlena(const pila *pPila, size_t sz);
int pilaVacia(const pila *pPila);

#endif //PILA_DINAMICA_PILA_DINAMICA_H
