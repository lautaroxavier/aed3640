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

int validar_categoria(char *categoria)
{
    char categorias[6][10] = {
        "MENOR",
        "CADETE",
        "ADULTO",
        "VITALICIO",
        "HONORARIO",
        "JUBILADO"
    };
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(categoria, categorias[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int validar_socio(T_Reg_Socio *p_socio)
{
    // validar nro socio
    if (p_socio->nro_socio < 2 || p_socio->nro_socio > 9999999)
    {
        return 0;
    }
    // validar dni
    if (p_socio->dni < 10001 || p_socio->dni > 99999999)
    {
        return 0;
    }
    // validar sexo
    if (p_socio->sexo != 'M' && p_socio->sexo != 'F' && p_socio->sexo != 'O')
    {
        return 0;
    }
    // verificar categoria
    if(!validar_categoria(p_socio->categoria))
    {
        return 0;
    }
    // verificar estado y fecha de baja
    if(p_socio->estado == 'A')
    {
        if (p_socio->fecha_baja.dia != 0 ||
            p_socio->fecha_baja.mes != 0 ||
            p_socio->fecha_baja.anio != 0)
            {
                return 0;
            }
    }
    else if (p_socio->estado != 'I')
    {
        return 0;
    }
    return 1;
}

void mostrar_socio(T_Reg_Socio *p_socio)
{
    printf("%ld | %s | %ld | %d/%d/%d | %c | %d/%d/%d | %s | %d/%d/%d | %c | %d/%d/%d\n",
            p_socio->nro_socio,
            p_socio->nya,
            p_socio->dni,
            p_socio->fecha_nac.dia,
            p_socio->fecha_nac.mes,
            p_socio->fecha_nac.anio,
            p_socio->sexo,
            p_socio->fecha_afiliacion.dia,
            p_socio->fecha_afiliacion.mes,
            p_socio->fecha_afiliacion.anio,
            p_socio->categoria,
            p_socio->fecha_ultima_cuota_paga.dia,
            p_socio->fecha_ultima_cuota_paga.mes,
            p_socio->fecha_ultima_cuota_paga.anio,
            p_socio->estado,
            p_socio->fecha_baja.dia,
            p_socio->fecha_baja.mes,
            p_socio->fecha_baja.anio);
}

void trozar_campos_socio(char *src, T_Reg_Socio *p_socio)
{
    // eliminar salto de linea
    char *aux = strchr(src, '\n');
    *aux = '\0';
    // leer la fecha de baja
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%d/%d/%d", &(p_socio->fecha_baja.dia),
                                &(p_socio->fecha_baja.mes),
                                &(p_socio->fecha_baja.anio));
    *aux = '\0';
    // leer el estado
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%c", &(p_socio->estado));
    *aux = '\0';
    // leer fecha ultima cuota paga
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%d/%d/%d", &(p_socio->fecha_ultima_cuota_paga.dia),
                                &(p_socio->fecha_ultima_cuota_paga.mes),
                                &(p_socio->fecha_ultima_cuota_paga.anio));
    *aux = '\0';
    // leer categoria
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%s", p_socio->categoria);
    *aux = '\0';
    // leer fecha afiliacion
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%d/%d/%d", &(p_socio->fecha_afiliacion.dia),
                                &(p_socio->fecha_afiliacion.mes),
                                &(p_socio->fecha_afiliacion.anio));
    *aux = '\0';
    // leer sexo
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%c", &(p_socio->sexo));
    *aux = '\0';
    // leer fecha de nacimiento
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%d/%d/%d", &(p_socio->fecha_nac.dia),
                                &(p_socio->fecha_nac.mes),
                                &(p_socio->fecha_nac.anio));
    *aux = '\0';
    // leer dni
    aux = strrchr(src, '|');
    sscanf(aux + 1, "%ld", &(p_socio->dni));
    *aux = '\0';
    /// leer nombre y apellido
    aux = strrchr(src, '|');
    strcpy(p_socio->nya, aux + 1);
    *aux = '\0';
    // leer nro socio
    aux = src;
    sscanf(aux, "%ld", &(p_socio->nro_socio));
    *aux = '\0';
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
        trozar_campos_socio(buffer, &socio);
        if (!validar_socio(&socio))
        {
            printf("ERROR SOCIO INVALIDO\n");
            mostrar_socio(&socio);
            fclose(p_arch_bin);
            fclose(p_arch_txt);
            return 0;
        }
        fwrite(&socio, sizeof(T_Reg_Socio), 1, p_arch_bin);
    }
    fclose(p_arch_bin);
    fclose(p_arch_txt);
    return 1;
}

void mostrar_menu()
{
    printf("A - Dar de alta nuevo socio\n");
    printf("M - Modificar nombre y apellido\n");
    printf("B - Dar de baja a un socio\n");
    printf("L - Mostrar socios dados de baja\n");
    printf("V - Mostrar socios activos ordenados por nro de socio\n");
    printf("P - Mostrar los 10 socios con mayor atraso en la cuota\n");
    printf("S - Salir\n");
}

void verificar_arch_bin_socios()
{
    FILE *fp = fopen("socios.dat", "r");
    T_Reg_Socio socio;
    printf("LEYENDO socios.dat\n");
    while(fread(&socio, sizeof(T_Reg_Socio), 1, fp))
    {
        mostrar_socio(&socio);
    }
    fclose(fp);
}

int main()
{
    char opcion;
    // convertir archivo de texto de socios a binario
    // crear indice y guardarlo en un archivo
    // usar indice para realizar consultas
    crear_arch_bin();
    // verificar_arch_bin_socios();
    // gestion de socios
    do {
        mostrar_menu();
        scanf("%c", &opcion);
        opcion = toupper(opcion);
        
    } while (opcion != 'S');
    

    return 0;
}
