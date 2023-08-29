#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_MAX 1024
#define TAM_VEC 8
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

typedef struct
{
    char p[TAM_MAX];
    int tope;
}
pila;

int ponerEnPila(pila *pPila, const void *pSource, size_t sz);
int sacarDePila(pila *pPila, void *pDest, size_t sz);
void crearPila(pila *pPila);
void vaciarPila(pila *pPila);
int verTope(const pila *pPila, void *pDest, size_t sz);
int pilaLlena(const pila *pPila, size_t sz);
int pilaVacia(const pila *pPila);