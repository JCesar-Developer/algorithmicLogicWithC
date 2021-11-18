#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "paso4_2.h"
#include "cambiarBarra0.h"

//PASO 4_2: Chequear de entre los dns configurados en el adaptador determinado en el 
//punto 6 y de los escritos en este archivo, cuál de estos es más rápido.;
void paso4_2(FILE* ipsValidas, char string[]) {

	printf("\n-------------------------- (PASO 4_2) -------------------------\n");
	printf("Extrayendo velocidades de las IP's validas:\n");
	rewind(ipsValidas);

	char ip[20], ping[100], linea[100], aux[20];
	char velocidadSTRING[10][20];
	int velocidadINT[10];
	int i = 0, j = 0;

	while (!feof(ipsValidas)) {
		fgets(ip, 20, ipsValidas);
		strcpy(velocidadSTRING[j], ip);
		strcpy(ping, "> 3.analisisIP.txt ping ");
		strcat(ping, ip);
		system(ping);

		FILE* analisisIP;
		analisisIP = fopen("3.analisisIP.txt", "r");

		//printf("\n");
		for (int i = 0; i < 11; i++) fgets(linea, 100, analisisIP);
		for (int i = 0; i < 9; i++) fscanf(analisisIP, "%s", aux);
		printf("\t%s -> velocidad MEDIA de la ip %s", aux, ip);

		//Transformemos la cadena en un entero y lo guardamos en un arreglo.
		i = 0;
		while (aux[i] != '\0') {
			i++;
			if (aux[i] == 'm') aux[i] = '\0';
		}
		velocidadINT[j] = atoi(aux);
		j++;
		fclose(analisisIP);
	}	
	//Comparamos velocidades
	int min = velocidadINT[0];
	for (i = 0; i < j; i++) {
		if (velocidadINT[i] <= min) {
			min = velocidadINT[i];
			strcpy(string, velocidadSTRING[i]);
		}
	}

	printf("\n\tRESULTADO: La IP mas veloz es: %s\n", string);
	printf("\n");
	system("pause");
}