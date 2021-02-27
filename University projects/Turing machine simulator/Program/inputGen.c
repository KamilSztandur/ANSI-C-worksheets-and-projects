#include <stdlib.h>
#include "MT.h"

char *inputGen( int m, int n ) {
	int inputLength = m + n + 1;
	
	char *input = malloc( sizeof(char) * inputLength );
	for( int i = 0; i < inputLength; i++ ) {
		if( i == m ) input[i] = '1';
		else input[i] = '0';
	}
	
	return input;
}
