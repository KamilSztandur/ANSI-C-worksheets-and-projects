#include <string.h>
#include "MT.h"

int interpreter( char *output ){
	int result = 0;
	for( int i = 0; i < strlen( output ); i++) 
		if( output[i] == '0' ) result ++;

	return result;
}
