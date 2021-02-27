#include "MT.h"
#include <stdio.h>
#include <stdlib.h>

void help() {
	printf("\n");
	printf("Podaj programowi dwie liczby, ktorych roznice wlasciwa\n");
	printf("chcesz otrzymac. Obie liczby powinny byc naturalne oraz\n"); 
	printf("podane w formie parametru przy wywolaniu programu oddzielone\n");
	printf("spacja.\n");
	printf("\n");
	printf("Przyklad:\n");
	printf("./MT_solver 3 1\n");
	printf("\nPowyzszy przyklad wyswietla opis postaci MT, tlumaczy\n");
	printf("liczby wejsciowa na tasme zakodowana unarnie oblicza roznice\n");
	printf("wlasciwa (3 - 1), a nastepnie zwraca decymalny wynik 2.\n");
	printf("\n");
    exit(0);
}

