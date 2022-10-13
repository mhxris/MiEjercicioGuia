#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>



int main(int argc, char *argv[])
{
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creando socket");
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// establecemos el puerto de escucha
	serv_adr.sin_port = htons(9000);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	
	int i;
	//inicia un bucle
	for (;;){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("Estoy recibido conexion\n");
		
		int terminar =0;
		//entramos en un bucle para atender todas las peticiones del cliente hasta su desconexion
		while (terminar ==0)
		{		
			ret=read(sock_conn,peticion, sizeof(peticion));
			printf ("Recibido\n");			
			
			peticion[ret]='\0';			
			
			printf ("Peticion: %s\n",peticion);
			
			char *p = strtok( peticion, "/");
			int codigo =  atoi (p);
			//ya tenemos el codigo
			char nombre[20];
			
			if (codigo !=0)
			{
				p = strtok( NULL, "/");

				strcpy (nombre, p);
				  //conseguimos el nomnbre
				printf ("Codigo: %d, Nombre: %s\n", codigo, nombre);
			}
			
			if (codigo ==0) //peticion de desconexzion
				terminar=1;
			else if (codigo ==1) //piden la longitd del nombre
				sprintf (respuesta,"%d",strlen (nombre));
			else if (codigo ==2)
				// quieren saber si el nombre es bonito
				if((nombre[0]=='M') || (nombre[0]=='S'))
				strcpy (respuesta,"SI");
				else
					strcpy (respuesta,"NO");
			else //quiere saber si es alto
			{
				p = strtok( NULL, "/");
				float altura =  atof (p);
				if (altura > 1.70)
					sprintf (respuesta, "%s: eres alto",nombre);
				else
					sprintf (respuesta, "%s: eres bajo",nombre);
			}
				
			if (codigo !=0)
			{
				
				printf ("respuesta: %s\n", respuesta);
				//enviamos respuesta
				write (sock_conn,respuesta, strlen(respuesta));
			}
		}
		   //se acaba el servicio para el cliente
		close(sock_conn); 
	}
}
