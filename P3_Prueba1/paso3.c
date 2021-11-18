#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "paso3.h"
#include "cambiarBarra0.h"

//PASO 3: Leer el archivo proporcionado inicialmente con las ip de los servidores
//dns, y chequear si esas ips son accesibles, y en caso de que lo sean es necesario
//escribirlas en un archivo temporal(esto se considerará un requisito).

void paso3(FILE* IPS, FILE* archivoTemporal) {
	rewind(IPS);
	char linea[20], ping[100], linea2[100];

	printf("\n--------------------------- (PASO 3) --------------------------\n");
	printf("Lanzando ping a las IP's del fichero abierto en el paso 1.\n");

	while (!feof(IPS)) {
		fgets(linea, 20, IPS);
		cambio(linea);
		strcpy(ping, "> 3.analisisIP.txt ping ");
		strcat(ping, linea);
		printf("\t- Lanzando ping a %s", linea);
		system(ping);

		FILE* analisisIP;
		bool encontrado = false;
		analisisIP = fopen("3.analisisIP.txt", "r");

		fgets(linea2, 100, analisisIP);
		while (!feof(analisisIP) && !encontrado) {
			encontrado = (strstr(linea2, "milisegundos") != NULL);
			if (!encontrado) {
				fgets(linea2, 100, analisisIP);
			}
		}
		if (encontrado) {
			printf("\n\t  Ping con %s > CONECCION CORRECTA\n\n", linea);
			fprintf(archivoTemporal, "\n");
			fprintf(archivoTemporal, "%s", linea);
		}
		else printf("\n\t  Ping con %s > CONECCION INCORRECTA\n\n", linea);
		fclose(analisisIP);
	}
	system("pause");
}