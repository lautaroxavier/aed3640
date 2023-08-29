#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pila.h"



int ponerEnPila(pila *pPila, const void *pSource, size_t sz)
{
    if (pPila->tope < sizeof(size_t) + sz)
    {
        return 0;
    }
    pPila->tope -= sz;
    memcpy(pPila->p + pPila->tope, pSource, sz);
    pPila->tope -= sizeof(size_t);
    memcpy(pPila->p + pPila->tope, &sz, sizeof(size_t));
    return 1;
}

int sacarDePila(pila *pPila, void *pDest, size_t sz)
{
    size_t sz_pila;
    // verificar si esta vacia
    if (pPila->tope == TAM_MAX)
    {
        pDest = NULL;
        return 0;
    }
    memcpy(&sz_pila, pPila->p + pPila->tope, sizeof(size_t));
    pPila->tope += sizeof(size_t);
    memcpy(pDest, pPila->p + pPila->tope, MIN(sz_pila, sz));
    pPila->tope += sz_pila;
    return 1;
}

int verTope(const pila *pPila, void *pDest, size_t sz)
{
    size_t sz_pila;
    int topeaux = pPila->tope;
    // verificar si esta vacia
    if (pPila->tope == TAM_MAX)
    {
        pDest = NULL;
        return 0;
    }
    memcpy(&sz_pila, pPila->p + topeaux, sizeof(size_t));
    topeaux += sizeof(size_t);
    memcpy(pDest, pPila->p + topeaux, MIN(sz_pila, sz));
    return 1;
}

void vaciarPila(pila *pPila)
{
    pPila->tope = TAM_MAX;
}

void crearPila(pila *pPila)
{
    pPila->tope = TAM_MAX;
}

int pilaLlena(const pila *pPila, size_t sz)
{
    return pPila->tope < sizeof(int) + sz;
}

int pilaVacia(const pila *pPila)
{
    return pPila->tope == TAM_MAX;
}