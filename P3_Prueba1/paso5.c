#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "paso5.h"
#include "cambiarBarra0.h"

//PASO 5: Cambiar en caso de no tener configurado el dns más rápido, 
//el dns del adaptador indicado en el punto 6 por el más veloz.
void paso5(FILE* ipsValidas, char adaptador[], char string[]) {

	printf("\n--------------------------- (PASO 5) --------------------------\n");
	printf("Cambiando el DNS actual por el mas veloz (si procede):\n");
	rewind(ipsValidas);

	char linea[20], netsh[150];

	printf("\n");
	fgets(linea, 20, ipsValidas);
	cambio(linea);
	if (strcmp(string, linea) == 0) printf("\tTu, ya tienes el DNS mas rapido: %s.\n\tNO HACE FALTA HACER NINGUN CAMBIO EN EL DNS", string);
	else {
		printf("\tCambiando DNS %s -por> DNS %s ", linea, string);
		//netsh interface ip add dns name="Wi-Fi" addr=212.166.211.2
		printf("\n\t");
		strcpy(netsh, "netsh interface ip add dns name=");
		strcat(netsh, adaptador);
		strcat(netsh, " addr=");
		strcat(netsh, string);
		system(netsh);
		printf("\t... La DNS se ha cambiado correctamente.");
	}

	printf("\n\n");
	system("pause");
}