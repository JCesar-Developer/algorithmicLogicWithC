#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "paso4.h"
#include "cambiarBarra0.h"

//PASO 4: Abrir el archivo temporal creado en el punto anterior y confirmar que
//printar por pantalla las IP's validas para la comparación de velocidades.
void paso4(FILE* archivoTemporal, FILE* *ipsValidas) {

	printf("\n--------------------------- (PASO 4) --------------------------\n");
	printf("Comprobando que los pings a comparar, funcionen... \n");

	//Elaboramos un segundo proceso de filtrado con las IPS y los servidoders DNS
	//almacenadas en el fichero con las ipsValidas
	rewind(archivoTemporal);
	*ipsValidas = fopen("4.ipsValidas.txt", "w+");

	char ip[20], ping[50], linea[100];
	while (!feof(archivoTemporal)) {
		fgets(ip, 20, archivoTemporal);
		//cambio(ip);
		strcpy(ping, "> 3.analisisIP.txt ping ");
		strcat(ping, ip);
		system(ping);

		FILE* analisisIP;
		analisisIP = fopen("3.analisisIP.txt", "r");

		bool encontrado = false;

		fgets(linea, 100, analisisIP);
		while (!feof(analisisIP) && !encontrado) {
			encontrado = (strstr(linea, "milisegundos") != NULL);
			if (!encontrado) fgets(linea, 100, analisisIP);
		}

		if (encontrado) {
			printf("\t  Ping con coneccion CORRECTA: %s", ip);
			fprintf(*ipsValidas, "%s", ip);
			//fprintf(*ipsValidas, "\n");
		}
		else printf("\t  Ping con coneccion INCORRECTA: %s", ip);
		fclose(analisisIP);
	}
	printf("\n\n");
	system("pause");
}