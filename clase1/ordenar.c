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

int main()
{
    nodo vec[] =
    {
        {"HL", 4},
        {"SM", 2},
        {"PB", 3},
        {"JM", 1},
        {"IU", 6}
    };
    burbujeo(vec, TAM, sizeof(nodo), cmpNodoCad);
    for (int i = 0; i < TAM; i++)
    {
        printf("%s %i\n", vec[i].cad, vec[i].n);
    }
    printf("Hello world!\n");
    return 0;
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
