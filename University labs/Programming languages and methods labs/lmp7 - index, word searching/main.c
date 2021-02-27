#include <stdlib.h> 
#include "skorowidz.h"

int main( int argc, char **argv ) {
 	FILE *in= argc > 1 ? fopen( argv[1], "r" ) : NULL;

	/*Liczenie linijek w pliku */
	int maxLines = 0;
	char c;
	for( c = getc( in ); c != EOF; c = getc(in) )
		if ( c == '\n' )
			maxLines++;
	rewind( in );
	
	/* Inicjacja skorowidzu ze zmiennymi przechowujacymi ilosc slow, tabele slow oraz nr linijki z ostatnim wystapieniem tego slowa. */
	/* Ostatnia zmienna jest wymagana do prawidlowego dzialania mojej funkcji wypisujacej skorowidz na ekran. */
	skorowidz_t skorowidz;
 	inicjujSkorowidz( &skorowidz, argc, argv);
	
	/* Dynamiczne zaalokowanie i wypelnienie zerami tablicy przechowujacej informacje o wierszach, w ktorych wystapily dane slowa */
	int **wystapieniaLinijki;
	wystapieniaLinijki = (int**)malloc( skorowidz.ileSlow*sizeof(int*) );
	
	for(int i = 0; i < skorowidz.ileSlow; i++ )
		wystapieniaLinijki[i] = (int*)malloc(maxLines*sizeof(int) );
	for( int i = 0; i < skorowidz.ileSlow; i++ )
		for( int j = 0; j < maxLines; j++ )
			wystapieniaLinijki[i][j] = 0;
	
	/* Obsluga bledow */
	if( skorowidz.ileSlow == 0 ) {
    		fprintf( stderr, "%s: błąd: proszę podać słowa do wyszukiwania\n", argv[0] );
    		return EXIT_FAILURE;
  	}

  	if( in == NULL ) {
    		fprintf( stderr, "%s: błąd: nie mogę czytać pliku %s\n", argv[0], argv[1] );
    		return EXIT_FAILURE;
  	}
	
	szukajSlow( &skorowidz, wystapieniaLinijki, in );

  	wypiszSkorowidz( &skorowidz, wystapieniaLinijki );

  	return EXIT_SUCCESS;
}
