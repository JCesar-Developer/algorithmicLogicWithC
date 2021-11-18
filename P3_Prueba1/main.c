#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "paso1.h"
#include "paso2.h"
#include "paso3.h"
#include "paso4.h"
#include "paso4_2.h"
#include "paso5.h"
#include "cambiarBarra0.h"

int main() {
	printf("------------------------------- Bienvenido a la aplicacion de Julito -------------------------------");
	FILE* IPS = NULL;
	FILE* archivoTemporal = NULL; 
	FILE* ipsValidas = NULL;
	char string[20], adaptador[20];
/* PASO 1: Preguntar inicialmente el nombre y la ruta del archivo dnsips.txt y mostrar el
   contenido de este archivo por pantalla. */
	paso1(&IPS);
/* PASO 2: Preguntar al usuario el adaptador de red que quiere modificar y mostrar los
   servidores dns configurados en este. */
	paso2(&archivoTemporal, adaptador);
//PASO 3: Leer el archivo proporcionado inicialmente con las ip de los servidores
//dns, y chequear si esas ips son accesibles, y en caso de que lo sean es necesario
//escribirlas en un archivo temporal(esto se considerará un requisito).	
	paso3(IPS, archivoTemporal);
	fclose(IPS);
//PASO 4: Abrir el archivo temporal creado en el punto anterior y chequear de entre los
//dns configurados en el adaptador determinado en el punto 6 y de los escritos
//en este archivo, cuál de estos es más rápido.;
	paso4(archivoTemporal, &ipsValidas);
	fclose(archivoTemporal);
	paso4_2(ipsValidas, string);
//PASO 5: Cambiar en caso de no tener configurado el dns más rápido, el dns del
//adaptador indicado en el punto 6 por el más veloz.
	paso5(ipsValidas, adaptador, string);
	fclose(ipsValidas);
//CIERRE DE APLICACIÓN.
	printf("\n----------------------------- Gracias por usar la aplicacion de Julito -----------------------------\n");
	return 0;
}