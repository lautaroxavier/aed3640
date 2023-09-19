#include <stdio.h>
#include "queue.h"

int main(void)
{
    Queue cola_prueba;
    char *names[5] = {"lautaro", "horacio", "javier", "patricia", "sergio"};
    char buffer[20] = "nothing here";
    inicializar(&cola_prueba);
    for (int i = 0; i < 5; i++)
    {
        printf("%s\n", names[i]);
        if(!encolar(&cola_prueba, names[i], strlen(names[i]) + 1))
        {
            printf("Error encolando\n");
        }
    }
    while (desencolar(&cola_prueba, buffer, 20))
    {
        printf("%s\n", buffer);
    }
}
