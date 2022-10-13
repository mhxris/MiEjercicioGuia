#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>


int main(int argc, char argv[]) 
{

    char peticion[100];
    char respuesta[100];

    strcpy (peticion, "Miguel/47/Juan/12/Maria/22/MArcos/19");
    //     Resultado: "Miguel47-Maria22-Marcos19"

    char nombre[20];
    int edad;
    char p = strtok (peticion, "/");

    while (p!=NULL)
    {
        strcpy (nombre, p);
        p = strtok(NULL, "/");
        edad = atoi (p);
        if(edad > 18)
            sprintf (respuesta, "%s%s%d-", respuesta, nombre, edad);

        p = strtok (NULL, "/");
    }
    respuesta [strlen (respuesta) -1 ] = '\0';
    printf ("Resultado: %s\n", respuesta);
}