#include "cambiarBarra0.h"

void cambio(char s[]) {
	int i;
	for (i = 0; i < 50; i++) {
		if (s[i] == '\n') {
			s[i] = '\0';
		}
	}
}