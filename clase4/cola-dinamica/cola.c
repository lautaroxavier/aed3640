#include <malloc.h>
#include <string.h>
#include <sys/param.h>
#include "cola.h"

void crear(tCola *pCola)
{
    pCola->first = NULL;
    pCola->last = NULL;
}

int vacia(tCola *pCola)
{
    return pCola->first == NULL;
}

int llena(tCola *pCola, size_t tam)
{
    tNodo *pNodo = malloc(sizeof(tNodo));
    void *tmp = malloc(tam);
    free(pNodo);
    free(tmp);
    return !tmp || !pNodo;
}

int encolar(tCola *pCola, void *pSource, size_t tam)
{
    tNodo *tmp_nodo = malloc(sizeof(tNodo));
    void *tmp_dato = malloc(tam);
    if (!tmp_dato || !tmp_nodo)
    {
        free(tmp_dato);
        free(tmp_nodo);
        return 0;
    }
    memcpy(tmp_dato, pSource, tam);
    tmp_nodo->next = NULL;
    tmp_nodo->tam = tam;
    tmp_nodo->dato = tmp_dato;
    if(pCola->first == NULL)
    {
        pCola->first = tmp_nodo;
    }
    else
    {
        pCola->last->next = tmp_nodo;
    }
    pCola->last = tmp_nodo;
    return 1;
}

int desencolar(tCola *pCola, void *pDest, size_t tam)
{
    tNodo *aux = pCola->first;
    if (!aux)
    {
        return 0;
    }
    pCola->first = aux->next;
    if(pCola->first == NULL)
    {
        pCola->last = NULL;
    }
    memcpy(pDest, aux->dato, MIN(aux->tam, tam));
    free(aux->dato);
    free(aux);
    return 1;
}

int frente(tCola *pCola, void *pDest, size_t tam)
{
    if (!pCola->first)
    {
        return 0;
    }
    memcpy(pDest, pCola->first->dato, MIN(tam, pCola->first->tam));
    return 1;
}

void vaciar(tCola *pCola)
{
    tNodo *aux;
    while (pCola->first)
    {
        aux = pCola->first;
        pCola->first = aux->next;
        free(aux->dato);
        free(aux);
    }
    pCola->last = NULL;
}