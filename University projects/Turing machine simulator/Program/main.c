#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MT.h"

int main( int argc, char *argv[] ) {
	printf(".------------------------(Maszyna Turinga)-------------------------.\n");
	printf("\n");
	printf("      Ten program stanowi emulator maszyny Turinga obliczajacej\n");
	printf("          roznice wlasciwa w postaci ponizszego dzialania:\n");
	printf("\n");
	printf("		        { m - n dla m >= n\n");
	printf("		m - n = {\n");
	printf("		        { 0     dla m < n\n");
	printf("\n");
	printf(" Postac MT:\n");
	printf("		M = ( Q, Σ, Γ, δ, q0, B, F )\n");
	printf("\n Gdzie:\n");
	printf(" 	Q = { q0, q1, q2, q3, q4, q5, q6 }\n");
	printf("	Σ = { 0, 1 }\n");
	printf("	Γ = { 0, 1, B }\n");
	printf("	q0 - stan poczatkowy\n");
	printf("	B - symbol pusty\n");
	printf("	F = { 0 }\n");
	printf("	 ___________________________________________\n");
	printf("	|__δ_|______0_____|______1_____|______B_____|\n");
	printf("	| q0 | (q1, B, P) | (q5, B, p) |      -     |\n");
	printf("	| q1 | (q1, 0, P) | (q2, 1, p) |      -     |\n");
	printf("	| q2 | (q3, 1, L) | (q2, 1, p) | (q4, B, L) |\n");
	printf("	| q3 | (q3, 0, L) | (q2, 1, L) | (q0, B, P) |\n");
	printf("	| q4 | (q4, 0, L) | (q4, B, L) | (q6, 0, P) |\n");
	printf("	| q5 | (q5, B, P) | (q5, B, p) | (q6, B, P) |\n");
	printf("	| q6 |      -     |      -     |      -     |\n");
	printf("	---------------------------------------------\n");
	printf("\n");
	if( argc < 2 ) { 
		printf("        Dodaj parametr -h / -help / -? aby wyswietlic Pomoc.\n");
		printf("\n");
	}
	printf("*-----------------------------------------------------------------*\n\n");
	if( argc < 2 ) return 0;
	
	if( strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-?") == 0 ) help();
	else if( atoi( argv[1] ) == 0 || argv[2] == NULL || atoi( argv[2] ) <= 0 || atoi( argv[1] ) <= 0 ) {
	       	printf("Nieprawidlowe uzycie programu. Oba parametry powinny byc liczbami naturalnymi.\n" );	
			printf("Dodaj parametr -h / -help / -? aby wyswietlic Pomoc.\n\n");
			return 1;
	}
	
	int m = atoi( argv[1] );
	int n = atoi( argv[2] );
	
	char *input = inputGen( m, n );
	printf("Wygenerowana tasma wejsciowa (kodowana unarnie):\n%s\n\n", input );
	
	printf("Ciag opisow chwilowych dla zadanej tasmy wejsciowej:\n\n");
	char *output = solver( input );
	
	int result = interpreter( output );
	printf("\n\nPowyzszy wynik roznicy wlasciwej (m - n) interpretujemy jako: %d.\n\n", result );

	return 0;
}
