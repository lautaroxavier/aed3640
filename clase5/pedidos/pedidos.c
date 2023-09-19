#include <stdint-gcc.h>
#include "pedidos.h"

typedef struct
{
    uint32_t nro_ped;
    uint32_t cod_prod;
    uint32_t cant;
}
tPedido;

typedef struct
{
    uint32_t cod_prod;
    uint32_t stock;
}
tStock;

typedef struct
{
    uint32_t cod_prod;
    float precio;
}
tPrecio;

int main(void)
{

}


// crear otro archivo binario con el stock de cada producto
// COD_PRODUCTO | STOCK
int crearArchivoStocks(char *nombre_archivo)
{
    tStock stocks[] = {
            {120, 34},
            {134, 23},
            {570, 12},
            {890, 0},
            {950, 5}
    };
    return 1;
}

// crear otro archivo binario con el precio de cada producto
// COD_PROD | PRECIO
int crearArchivoPrecios(char *nombre_archivo)
{
    return 1;
}


// crear archivo binario con pedidos con la forma
// NRO_PEDIDO | COD_PRODUCTO | CANTIDAD
int crearArchivoPedidos(char *nombre_archivo)
{
    tPedido pedidos[] = {
            {1, 120, 15},
            {1, 570, 10},
            {1, 950, 2},
            {2, }
    };
    return 1;
}