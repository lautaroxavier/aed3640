#include <stdio.h>
#include <stdlib.h>
#include "indice.h"
#include "string.h"

typedef struct
{
    int dia;
    int mes;
    int anio;
}
T_Fecha;

typedef struct
{
    long nro_socio; // 2 - 9.999.999
    char nya[61];
    long dni; // 10.001 - 99.999.999
    T_Fecha fecha_nac;
    char sexo; // 'F', 'M', 'O'
    T_Fecha fecha_afiliacion;
    char categoria[10]; // 'MENOR', 'CADETE', 'ADULTO', 'VITALICIO', 'HONORARIO', 'JUBILADO'
    T_Fecha fecha_ultima_cuota_paga;
    char estado; // 'A', 'I'
    T_Fecha fecha_baja; // debe ser vacio si el estado es 'A'
}
T_Reg_Socio;

int trozar_campos_socio(char *src, T_Reg_Socio *p_socio)
{
    // eliminar salto de linea
    char *aux = strchr(src, '/n');
    *aux = '/0';
    // leer la fecha de baja
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%d/%d/%d", p_socio->fecha_baja.dia,
                                p_socio->fecha_baja.mes,
                                p_socio->fecha_baja.anio);
    return 1;
}

// convertir archivo de texto a binario
// abrir archivo de texto
// crear archivo binario
// leer linea por linea y cargarlo en un registro
// grabar registro en el archivo binario

int crear_arch_bin()
{
    const char *archivo_txt = "socios.txt";
    char buffer[1000];
    T_Reg_Socio socio;
    FILE *p_arch_txt = fopen(archivo_txt, "r");
    FILE *p_arch_bin = fopen("socios.dat", "w");
    while(fgets(buffer, 1000, p_arch_txt))
    {
        if(!trozar_campo_socio(buffer, &socio))
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    // convertir archivo de texto de socios a binario
    // crear indice y guardarlo en un archivo
    // usar indice para realizar consultas
    crear_arch_bin();
    return 0;
}
