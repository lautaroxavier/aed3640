#ifndef LISTA-ENLAZADA_H_INCLUDED
#define LISTA-ENLAZADA_H_INCLUDED

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//

typedef struct sNodo
{
    size_t tam;
    void *elem;
    struct sNodo *sig;
}
tNodo;

typedef tNodo* tLista;

// PRIMERAS PRIMITIVAS

void crearLista(tLista *pLista);

int listaVacia(const tLista *pLista);

int listaLlena(const tLista *pLista, size_t tam);

void vaciarLista(tLista *pLista);

void mostrarLista(tLista *pLista, void mostrar (const void *));

int ponerAlComienzo(tLista *pLista, const void *dato, size_t cantBytes);

int sacarPrimero(tLista *pLista, void *dest, size_t cantBytes);

int verPrimero(const tLista *pLista, void *dest, size_t cantBytes);

int ponerAlFinal(tLista *pLista, const void *dato, size_t tam);

int sacarUltimo(tLista *pLista, void *dest, size_t cantBytes);

int verUltimo(const tLista *pLista, void *dest, size_t cantBytes);

int insertarEnPos(tLista *pLista, const void *dato, size_t tam, unsigned pos);

int insertarOrdenado(tLista *pLista, const void *dato, size_t tam, int cmp (const void*, const void*));

int eliminarElemento(tLista *pLista, void *dato, size_t tam, int cmp(const void *, const void *));

void ordenarLista(tLista *pLista, int cmp(const void*, const void*));

#endif // LISTA-ENLAZADA_H_INCLUDED
