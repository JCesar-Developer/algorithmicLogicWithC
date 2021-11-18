#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "paso2.h"
#include "cambiarBarra0.h"

//PASO 2: Preguntar al usuario el adaptador de red que quiere modificar y mostrar los
//servidores dns configurados en este.
void paso2(FILE* *archivoTemporal, char adaptador[]) {
	FILE* IPConfig;
	char linea[100];

	system("> 2.ipConfig.txt ipConfig /all");
	IPConfig = fopen("2.ipConfig.txt", "r");

	printf("\n--------------------------- (PASO 2) --------------------------\n");
	printf("Ingrese el nombre del adaptador de red a modificar: ");
	rewind(stdin);
	fgets(adaptador, 20, stdin);
	cambio(adaptador);

	bool encontrado = false;
	fgets(linea, 100, IPConfig);
	while (!feof(IPConfig) && !encontrado) {
		encontrado = (strstr(linea, adaptador) != NULL);
		if (!encontrado) {
			fgets(linea, 100, IPConfig);
		}
	}
	if (!encontrado) {
		printf("No se ha encontrado el adaptador sugerido. Por favor vuelve a intentarlo.");
		paso2(&*archivoTemporal, &adaptador);
	}
	else {
		//FILE* *archivoTemporal;
		*archivoTemporal = fopen("2.archivoTemporal.txt", "w+");

		if (*archivoTemporal == NULL) {
			printf("ERROR: No se pudo abrir el fichero.");
		}
		else {
			printf("Estas son las DNS del adaptador de red -> %s", linea);
			//2.1. Avanzamos a la linea donde se encuentran los DNS.
			for (int i = 0; i < 15; i++) {
				fgets(linea, 100, IPConfig);
			}
			//2.2. Avanzamos hasta el primer dígito de un DNS.
			char caracter;
			caracter = fgetc(IPConfig);
			while (caracter != ':') {
				caracter = fgetc(IPConfig);
			}
			//2.3. Printamos el DNS correspondiente.
			printf("\t- DNS1 -> ");
			caracter = fgetc(IPConfig);
			caracter = fgetc(IPConfig);
			while (caracter != '\n') {
				printf("%c", caracter);
				fprintf(*archivoTemporal, "%c", caracter);
				caracter = fgetc(IPConfig);
			}
			//2.4. Printamos el resto de DNS's del adaptador.
			int i = 2;
			while ((caracter - '0') < 10) {
				caracter = fgetc(IPConfig);
				while (caracter == ' ')	caracter = fgetc(IPConfig);
				if ((caracter - '0') < 10) {
					printf("\n\t- DNS%i -> ", i);
					//printf("%c", caracter);
					fprintf(*archivoTemporal, "\n");
					//fprintf(*archivoTemporal, "%c", caracter);
					while (caracter != '\n') {
						printf("%c", caracter);
						fprintf(*archivoTemporal, "%c", caracter);
						caracter = fgetc(IPConfig);
					}
				}
				i++;
			}
		}
		fclose(IPConfig);
	}
	/////////////////////////////////////////////////////////////
	int j = 0;
	while (adaptador[j] != ':') {
		j++;
	}
	if (adaptador[j] == ':') adaptador[j] = '\0';
	/////////////////////////////////////////////////////////////
	printf("\n\n");
	system("pause");
}