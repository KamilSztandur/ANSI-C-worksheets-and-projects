#include <stdio.h>  // wiadomo po co
#include <stdlib.h> // qsort
#include <string.h> // strstr

#define BUFSIZE 8192    // zakładamy, że linie będą krótsze niż 8kB

int main( int argc, char **argv ) {
	int nr_linii = 0;
	int loopHelper; //Zmienna pomocnicza przy obsludze petli for w celu unikniecia uzycia "goto"
	char buf[BUFSIZE];
	
	int mode = argc > 1 ? atoi( argv[1] ) : -1;
	FILE *text = argc > 2 ? fopen( argv[2], "r" ) : NULL;
  	
	if( mode != 1 && mode != 0 ) { 
		fprintf( stderr, "%s: Błąd: proszę wybrać prawidłowy tryb wyszukiwania.\n", argv[0] );
		return EXIT_FAILURE;
	}

  	if( text == NULL ) {
    		fprintf( stderr, "%s: błąd: nie mogę czytać pliku %s\n", argv[0], argv[2] );
    		return EXIT_FAILURE;
  	}
	
	if( argc <= 3 ) {
		fprintf( stderr, "%s: błąd: proszę podać co najmniej jeden wyraz do wyszukania.\n", argv[0] );
		return EXIT_FAILURE;
	}

	if( mode == 0 ) {
		while( fgets( buf, BUFSIZE, text ) != NULL ) {
			nr_linii++;
			loopHelper = 1;
			for( int i = 0; loopHelper == 1 && i < (argc-3); i++) { //Wyszukiwanie kolejno podanych slow 
				if( strstr( buf, argv[i+3]) != NULL) { 
						printf("%d. %s", nr_linii,  buf);
						loopHelper = 0;
						//Zakonczy wykonywanie petli po znalezieniu wyrazu, aby uniknac powtorzen
					}
			}
		}
	} 
	else {
		while( fgets( buf, BUFSIZE, text ) != NULL ) {
			nr_linii++;
			loopHelper = 1;
			for( int i = 0; loopHelper == 1 && i < (argc-3); i++) {
				if( strstr( buf, argv[i+3]) == NULL )
						loopHelper = 0;
			}
			if( loopHelper == 1 ) 
				printf("%d. %s", nr_linii, buf);
		}
	}

  	return EXIT_SUCCESS;
}

