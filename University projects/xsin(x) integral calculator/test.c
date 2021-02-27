#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calnum.h"

double f( double x ) {   
	return x*sin(x);
}
   
int main( int argc, char **argv ) {
     	double min = argc > 1 ? atof( argv[1] ) : 0;
     	double max  = argc > 2 ? atof( argv[2] ) : M_PI;
     	int    n = argc > 3 ? atoi( argv[3] ) : 10;
     
     	printf("\n============================================\n");
     	
	if( min > max ) 
	    printf("Uwaga! Zakres minimalny funkcji jest wiekszy niz maksymalny!\n");
	else if ( min == max) 
		printf("Uwaga! Zakres funkcji jest jest jednym punktem!\n");

	printf("Przedział całkowania: <%g,%g>\nPodział na: %i podprzedziałów.\nUżyta funkcja podcałkowa: f(x) = x*sin(x)\n", min, max, n);
	printf("Wynik całki = %lf\n", calnum( f, min, max, n ) );
	printf("============================================\n\n");

     	return 0;
}

