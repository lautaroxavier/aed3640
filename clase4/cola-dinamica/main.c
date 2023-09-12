#include <stdio.h>
#include "cola.h"
#include "string.h"

int main(void)
{
    tCola cola_prueba;
    char *names[5] = {"lautaro", "horacio", "javier", "patricia", "sergio"};
    char buffer[20] = "nothing here";
    crear(&cola_prueba);
    for (int i = 0; i < 5; i++)
    {
        encolar(&cola_prueba, names[i], strlen(names[i]) + 1);
    }
    while (!vacia(&cola_prueba))
    {
        desencolar(&cola_prueba, buffer, 20);
        printf("%s\n", buffer);
    }
}
