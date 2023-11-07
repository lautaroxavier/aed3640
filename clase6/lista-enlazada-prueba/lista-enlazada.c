#include <sys/param.h>
#include "lista-enlazada.h"

void crearLista(tLista *pLista)
{
    *pLista = NULL;
}

int listaVacia(const tLista *pLista)
{
    *pLista == NULL;
}

int listaLlena(const tLista *pLista, size_t tam)
{
    // se recibe el puntero a lista por compatibilidad con
    // con la implementacion en memoria estatica, aunque no se use
    tNodo *aux = (tNodo*)malloc(sizeof(tNodo));
    void *info = malloc(tam);

    free(aux);
    free(info);

    return aux == NULL || info == NULL;
}

void vaciarLista(tLista *pLista)
{
    while(*pLista)
    {
        tNodo *aux = *pLista;
        *pLista = aux->sig;
        free(aux->elem);
        free(aux);
    }
}

void mostrarLista(tLista *pLista, void mostrar (const void *))
{
    while(*pLista)
    {
        mostrar((*pLista)->elem);
        printf("\n");
        pLista = &((*pLista)->sig);
    }
}

int ponerAlComienzo(tLista *pLista, const void *dato, size_t cantBytes)
{
    tNodo *nuevo;

    nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(nuevo == NULL)
    {
        return 0;
    }
    nuevo->elem = malloc(cantBytes);
    if (nuevo->elem == NULL)
    {
        free(nuevo);
        return 0;
    }

    memcpy(nuevo->elem, dato, cantBytes);
    nuevo->tam = cantBytes;
    nuevo->sig = *pLista;
    *pLista = nuevo;

    return 1;
}

int sacarPrimero(tLista *pLista, void *dest, size_t cantBytes)
{
    tNodo *aux = *pLista;

    if (aux == NULL)
    {
        return 0;
    }

    *pLista = aux->sig;
    memcpy(dest, aux->elem, MIN(cantBytes, aux->tam));
    free(aux->elem);
    free(aux);

    return 1;
}

int verPrimero(const tLista *pLista, void *dest, size_t cantBytes)
{
    if (*pLista == NULL)
    {
        return 0;
    }

    memcpy(dest, (*pLista)->elem, MIN(cantBytes, (*pLista)->tam));

    return 1;
}

int ponerAlFinal(tLista *pLista, const void *dato, size_t tam)
{
    tNodo *nuevo;
    // avanzar hasta el ultimo nodo
    while(*pLista)
    {
        pLista = &((*pLista)->sig);
    }
    // crear nodo
    nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(nuevo == NULL)
    {
        return 0;
    }
    nuevo->elem = malloc(tam);
    if (nuevo->elem == NULL)
    {
        free(nuevo);
        return 0;
    }
    // asignar valores al nuevo nodo
    nuevo->tam = tam;
    nuevo->sig = *pLista; // NULL
    memcpy(nuevo->elem, dato, tam);
    // enganchar al ultimo nodo
    *pLista = nuevo;

    return 1;
}

int sacarUltimo(tLista *pLista, void *dest, size_t cantBytes)
{
    if (*pLista == NULL)
    {
        return 0;
    }

    while((*pLista)->sig)
    {
        pLista = &(*pLista)->sig;
    }

    memcpy(dest, (*pLista)->elem, MIN((*pLista)->tam, cantBytes));

    free((*pLista)->elem);
    free(*pLista);

    *pLista = NULL;

    return 1;
}

int verUltimo(const tLista *pLista, void *dest, size_t cantBytes)
{
    if(*pLista == NULL)
    {
        return 0;
    }

    while ((*pLista)->sig)
    {
        pLista = &(*pLista)->sig;
    }

    memcpy(dest, (*pLista)->elem, MIN((*pLista)->tam, cantBytes));

    return 1;
}

int insertarEnPos(tLista *pLista, const void *dato, size_t tam, unsigned pos)
{
    tNodo *nuevo;
    // avanzar hasta el puntero que apunta al nodo en la posicion 'pos'
    // o hasta el puntero que se encuentra en el ultimo nodo (NULL)
    while(*pLista && pos)
    {
        pLista = &((*pLista)->sig);
        pos--;
    }
    // crear nodo
    nuevo = malloc(sizeof(tNodo));
    if (!nuevo)
    {
        return 0;
    }
    nuevo->elem = malloc(tam);
    if (!nuevo->elem)
    {
        free(nuevo);
        return 0;
    }
    // asignar valores al nuevo nodo
    nuevo->tam = tam;
    nuevo->sig = *pLista;
    memcpy(nuevo->elem, dato, tam);
    // enganchar al ultimo nodo
    *pLista = nuevo;

    return 1;
}

int insertarOrdenado(tLista *pLista, const void *dato, size_t tam, int cmp (const void*, const void*))
{
    // la lista debe estar ordenada
    int comp;
    while(*pLista && (comp = cmp(dato, (*pLista)->elem)) > 0)
    {
        pLista = &((*pLista)->sig);
    }
    // chequear si el dato esta duplicado
    // y no llegue al final de la lista
    if (*pLista && comp == 0)
    {
        return 0;
    }
    // crear nodo
    tNodo *nuevo = malloc(sizeof(tNodo));
    if (!nuevo)
    {
        return 0;
    }
    nuevo->elem = malloc(tam);
    if (!nuevo->elem)
    {
        free(nuevo);
        return 0;
    }
    // asignar valores al nuevo nodo
    nuevo->tam = tam;
    nuevo->sig = *pLista;
    memcpy(nuevo->elem, dato, tam);
    // enganchar al ultimo nodo
    *pLista = nuevo;

    return 1;
}

int eliminarElemento(tLista *pLista, void *dato, size_t tam, int cmp(const void *, const void *))
{
    int comp;
    tNodo *eliminado;
    // en una lista ordenada solo hay que buscar hasta que sea menor
    while (*pLista && (comp = cmp(dato, (*pLista)->elem)) > 0)
    {
        pLista = &((*pLista)->sig);
    }
    // si no se encuentra el elemento
    if (!(*pLista) || comp != 0)
    {
        return 0;
    }
    // para lista no ordenada
    //while (*pLista && cmp(dato, (*pLista)->elem))
    //{
    //    pLista = &((*pLista)->sig);
    //}
    //if (!(*pLista))
    //{
    //    return 0;
    //}
    eliminado = *pLista;
    *pLista = eliminado->sig;
    // se copia el dato porque el dato pasado por parametro puede estar incompleto
    memcpy(dato, eliminado->elem, MIN(tam, eliminado->tam));
    free(eliminado->elem);
    free(eliminado);
    return 0;
}

void ordenarLista(tLista *pLista, int cmp(const void*, const void*))
{
    // la estrategia es crear una nueva lista vacia e ir enganchando los nodos
    // en la nueva lista ordenada hasta que la lista recibida por parametro quede vacia
    tLista lista_ordenada = NULL;
    tLista *p_lista_ordenada = &lista_ordenada;
    tNodo *pNodo;

    while(*pLista)
    {
        // apuntar la lista ordenada al principio
        p_lista_ordenada = &lista_ordenada;
        // desenganchar
        pNodo = *pLista;
        *pLista = pNodo->sig;
        // insertar ordenado
        while(*p_lista_ordenada && cmp(pNodo->elem, (*p_lista_ordenada)->elem) > 0)
        {
            p_lista_ordenada = &(*p_lista_ordenada)->sig;
        }
        // enganchar
        pNodo->sig = *p_lista_ordenada;
        *p_lista_ordenada = pNodo;
    }

    *pLista = lista_ordenada;
}
