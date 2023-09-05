#include <sys/param.h>
#include "pila-dinamica.h"

int ponerEnPila(pila *pPila, const void *pSource, size_t sz)
{
    nodo *nuevo = malloc(sizeof(nodo));
    void *dato = malloc(sz);
    if (!nuevo || !dato) {
        free(nuevo);
        free(dato);
        return 0;
    }

    nuevo->elem = dato;
    nuevo->size = sz;

    memcpy(dato, pSource, sz);

    nuevo->next = *pPila;
    *pPila = nuevo;

    return 1;
}

int sacarDePila(pila *pPila, void *pDest, size_t sz)
{
    if (*pPila == NULL)
    {
        return 0;
    }

    nodo *tope = *pPila;
    *pPila = tope->next;

    memcpy(pDest, tope->elem, MIN(sz, tope->size));

    free(tope->elem);
    free(tope);

    return 1;
}

void crearPila(pila *pPila)
{
    *pPila = NULL;
}

void vaciarPila(pila *pPila)
{
    nodo *tmp;
    while (*pPila)
    {
        tmp = *pPila;
        *pPila = tmp->next;
        free(tmp->elem);
        free(tmp);
    }
}

int verTope(const pila *pPila, void *pDest, size_t sz)
{
    if (*pPila == NULL)
    {
        return 0;
    }

    nodo *tope = *pPila;
    memcpy(pDest, tope->elem, MIN(tope->size, sz));

    return 1;
}

int pilaLlena(const pila *pPila, size_t sz)
{
    nodo *tmp = malloc(sizeof(nodo) + sz);
    void *elem = malloc(sz);
    int esta_llena = !tmp || !elem;
    free(tmp);
    free(elem);
    return esta_llena;
}

int pilaVacia(const pila *pPila)
{
    return *pPila == NULL;
}