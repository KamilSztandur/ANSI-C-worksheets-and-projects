#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>


int main( int argc, char **argv ){
	int res;
	Matrix *A = readFromFile( "A" );
	Matrix *b = readFromFile( "b" );
	Matrix *x;

	if ( A == NULL ) return -1;
	if ( b == NULL ) return -2;
	
	printf("%s:\n", argv[1] );
	printToScreen( A );
	
	printf("%s:\n", argv[2] );
	printToScreen( b );

	res = eliminate( A, b );
	x = createMatrix( b->r, 1 );
	
	if ( x != NULL ){
		res = backsubst( x, A, b );
		printToScreen( x );
	 	freeMatrix( x );
	} else fprintf( stderr, "Błąd! Nie mogłem utworzyć wektora wynikowego x.\n" );

	freeMatrix( A );
	freeMatrix( b );

	return 0;
}
