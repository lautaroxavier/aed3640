#ifndef COLA_DINAMICA_COLA_H
#define COLA_DINAMICA_COLA_H

#include <stddef.h>

typedef struct sNodo
{
    size_t tam;
    void *dato;
    struct sNodo *next;
}
tNodo;

typedef struct
{
    tNodo *first;
    tNodo *last;
}
tCola;

// crear
// poner ambos punteros en NULL
void crear(tCola *pCola);

// encolar
// puede fallar, no puede estar llena
int encolar(tCola *pCola, void *pSource, size_t tam);

// llena
int llena(tCola *pCola, size_t tam);

// frente
// puede fallar si esta vacia
int frente(tCola *pCola, void *pDest, size_t tam);

// desencolar
// no puede estar vacia
int desencolar(tCola *pCola, void *pDest, size_t tam);

// vacia
int vacia(tCola *pCola);

// vaciar
void vaciar(tCola *pCola);

#endif //COLA_DINAMICA_COLA_H
