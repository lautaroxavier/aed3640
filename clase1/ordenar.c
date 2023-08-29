#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 5

typedef struct
{
    char cad[3];
    int n;
}
nodo;

int cmpNodoCad(const void *a, const void *b);
int cmpNodoInt(const void *a, const void *b);
void burbujeo(void *vec, int tam, int sz, int cmp(const void*,const void*));
void mostrarVector(const void *vec, size_t sz, int items, void mostrar(const void*));
void mostrarNodo(const void *n);

int main()
{
    nodo vec[TAM] =
    {
        {"HL", 4},
        {"SM", 2},
        {"PB", 3},
        {"JM", 1},
        {"IU", 6}
    };
    printf("Vector desordenado\n");
    mostrarVector(vec, sizeof(nodo), TAM, mostrarNodo);
    burbujeo(vec, TAM, sizeof(nodo), cmpNodoCad);
    printf("Vector ordenado por nombre\n");
    mostrarVector(vec, sizeof(nodo), TAM, mostrarNodo);
    burbujeo(vec, TAM, sizeof(nodo), cmpNodoInt);
    printf("Vector ordenado por posicion\n");
    mostrarVector(vec, sizeof(nodo), TAM, mostrarNodo);
    return 0;
}

void mostrarNodo(const void *n)
{
    const nodo *pNodo = (const nodo*) n;
    printf("nombre: %s pos: %i\n", pNodo->cad, pNodo->n);
}

void mostrarVector(const void *vec, size_t sz, int items, void mostrar(const void*))
{
    char *end = vec + (items * sz);
    while (vec != end)
    {
        mostrar(vec);
        vec += sz;
    }
}

int cmpNodoCad(const void *a, const void *b)
{
    const nodo *n1 = (const nodo*)a;
    const nodo *n2 = (const nodo*)b;
    const char *s1 = (const char *)(n1->cad);
    const char *s2 = (const char *)(n2->cad);
    return strcmp(s1, s2);
}

int cmpNodoInt(const void *a, const void *b)
{
    const nodo *n1 = (const nodo*)a;
    const nodo *n2 = (const nodo*)b;
    const int s1 = (const int)(n1->n);
    const int s2 = (const int)(n2->n);
    return s1 - s2;
}

void burbujeo(void *vec, int tam, int sz, int cmp(const void*,const void*))
{
    void *start = vec;
    void *tmp = malloc(sz);
    int huboIntercambio = 1;
    int i, j;
    if (!tmp)
    {
        return;
    }
    for (i = 0; i < tam && huboIntercambio; i++)
    {
        vec = start;
        huboIntercambio = 0;
        for (j = 0; j < tam - i - 1; j++)
        {
            if (cmp(vec, vec + sz) > 0)
            {
                // intercambiar
                huboIntercambio = 1;
                memcpy(tmp, vec, sz);
                memcpy(vec, vec + sz, sz);
                memcpy(vec + sz, tmp, sz);
            }
            vec += sz;
        }
    }
    free(tmp);
}
