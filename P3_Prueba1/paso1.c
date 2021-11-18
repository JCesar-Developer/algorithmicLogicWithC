#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "paso1.h"
#include "cambiarBarra0.h"

//PASO 1: Preguntar inicialmente el nombre y la ruta del archivo dnsips.txt y mostrar el 
//contenido de este archivo por pantalla
void paso1(FILE* *IPS){
	char direccion[20], linea[20];
	printf("\n--------------------------- (PASO 1) --------------------------\n");
	printf("Introduce la direccion del archivo donde se encuentran las IPS's: \n");
	fgets(direccion, 20, stdin);
	cambio(direccion);
	*IPS = fopen(direccion, "r"); 

	printf("------------------------------------------------------ \n");
	if (*IPS == NULL) {
		printf("No se ha podido abrir el archivo. \nPor favor, vuelve a intentarlo.");
		paso1(&*IPS);
	}
	else {
		printf("Las direcciones DNS's encontradas en el fichero son: \n");
		while (!feof(*IPS)) {
			fgets(linea, 20, *IPS);
			printf("%s", linea);
		}
	}

	printf("\n\n");
	system("pause");
}