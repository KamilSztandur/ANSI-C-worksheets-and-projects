#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include "GBK.h"

int main( int argc, char *argv[] ) {
	if( argc < 2 ) {  /* Jezeli uzytkownik nie wpisze zadnego argumentu */
		printf(".-------------------------(GBK GENERATOR)-------------------------.\n");
        	printf("\n");
        	printf("              Zaimplementowana gramatyka:  S->aSa|ε\n");
        	printf("             Obslugiwany jezyk: { a^n a^n | n >= 0 }.\n");
        	printf("\n");
		printf("        Dodaj parametr -h / -help / -? aby wyswietlic Pomoc.\n");
		printf("\n");
		printf("*-----------------------------------------------------------------*\n");
		return 0;
	}
	
	printf(".-------------------------(GBK GENERATOR)-------------------------.\n");
        printf("\n");
        printf("                Zaimplementowana gramatyka:  S->aSa|ε\n");
        printf("               Obslugiwany jezyk: { a^n a^n | n >= 0 }.\n");
        printf("\n");
        printf("*-----------------------------------------------------------------*\n\n");
	if( strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-?") == 0 ) help();
	 
	if( atoi( argv[1] ) == 0 ) { /* Jezeli uzytkownik poda jako pierwszy parametr co innego, niz liczba */
	       	printf("Nieprawidlowe uzycie programu (%s to nie liczba calkowita).\n", argv[1] );	
		printf("Dodaj parametr -h / -help / -? aby wyswietlic Pomoc.\n\n");
		return 1;
	}
	int n = atoi( argv[1] );

	//displayChains(n);
	//displayTree(n);
	
	return 0;
}
