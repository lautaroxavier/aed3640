#include <stdint-gcc.h>
#include "pila-dinamica.h"

#define TAM_MAX 1024

int sumarConPilas(const char *s1, const char *s2, char *sRes);
int sumarYApilarDigitos(pila *pPila, uint8_t *carry, uint8_t res);

int main(int argc, char *argv[])
{
    char buffer[TAM_MAX];
    char s1[TAM_MAX];
    char s2[TAM_MAX];
    if (argc != 2)
    {
        printf("Error: cantidad de argumentos incorrecta.\n");
        return 1;
    }
    // abrir archivo
    FILE *archivo = fopen(argv[1], "r+t");
    if (!archivo)
    {
        printf("Error abriendo archivo.\n");
        return 1;
    }
    fgets(s1, TAM_MAX, archivo);
    fgets(s2, TAM_MAX, archivo);

    s1[strcspn(s1, "\n")] = 0;
    s2[strcspn(s2, "\n")] = 0;
    // mostrar sumandos
    printf("%*s\n", 20, s1);
    printf("+\n");
    printf("%*s\n", 20, s2);
    sumarConPilas(s1, s2, buffer);
    printf("%*s\n", 20, buffer);
    fprintf(archivo, "%s\n", buffer);
    fclose(archivo);
    return 0;
}

int sumarConPilas(const char *s1, const char *s2, char *sRes)
{
    uint8_t tmp, d1, d2, carry = 0;
    pila pila1, pila2, pilaResultado;
    // apilar primer sumando
    crearPila(&pila1);
    while (*s1)
    {
        tmp = *s1 - '0';
        ponerEnPila(&pila1, &tmp, sizeof(tmp));
        s1++;
    }
    // apilar segundo sumando
    crearPila(&pila2);
    while(*s2)
    {
        tmp = *s2 - '0';
        ponerEnPila(&pila2, &tmp, sizeof(tmp));
        s2++;
    }
    // sumar y apilar resultado en otra pila
    crearPila(&pilaResultado);
    while(!pilaVacia(&pila1) && !pilaVacia(&pila2))
    {
        sacarDePila(&pila1, &d1, sizeof(d1));
        sacarDePila(&pila2, &d2, sizeof(d2));
        sumarYApilarDigitos(&pilaResultado, &carry, d1 + d2 + carry);
    }
    while (sacarDePila(&pila1, &d1, sizeof(d1)))
    {
        sumarYApilarDigitos(&pilaResultado, &carry, d1 + carry);
    }
    while (sacarDePila(&pila2, &d1, sizeof(d1)))
    {
        sumarYApilarDigitos(&pilaResultado, &carry, d1 + carry);
    }
    // desapilar y guardar resultado
    while (sacarDePila(&pilaResultado, &tmp, sizeof(tmp)))
    {
        sprintf(sRes, "%i", tmp);
        sRes++;
    }
    return 1;
}

int sumarYApilarDigitos(pila *pPila, uint8_t *carry, uint8_t res)
{
    *carry = res / 10;
    res %= 10;
    ponerEnPila(pPila, &res, sizeof(res));
    return 1;
}