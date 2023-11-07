#ifndef INDICE_H_INCLUDED
#define INDICE_H_INCLUDED

#include "lista-enlazada.h"

typedef struct
{
    size_t tam_clave;
    tLista indice;
    int (*cmp)(const void*, const void*);
}
T_Indice;

// crea un indice que alberga una clave del tamanio especificado y una funcion para ordenar segun las claves
void indice_crear(T_Indice *p_indice, size_t tam_clave, int cmp(const void*, const void*));

// inserta la clave de forma ordenada junto al numero de registro
int indice_insertar(T_Indice *p_indice, void *p_clave, unsigned nro_reg);

// recibe una clave a eliminar y devuelve el numero de registro
int indice_eliminar(T_Indice *p_indice, void *p_clave, unsigned *p_nro_reg);

// busca la clave y devuelve el nro de registro
int indice_buscar(T_Indice *p_indice, void *p_clave, unsigned *p_nro_reg);

// carga el indice a partir del archivo ordenado
int indice_cargar(T_Indice *p_indice, const char *path);

// graba un archivo con el contenido del indice
void indice_grabar(T_Indice *p_indice, const char *path);

// vacia el indice
void indice_vaciar(T_Indice *p_indice);

// recorre el indice en orden y ejecuta la accion en cada elemento
int indice_recorrer(T_Indice *p_indice, void accion(const void*, unsigned, void *));



#endif // INDICE_H_INCLUDED