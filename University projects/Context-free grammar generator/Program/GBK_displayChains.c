#include "GBK.h"
#include <stdio.h>

void displayChains( int n ) {
        int nr_wyrazu = 0; //Zmienna pomocnicza do wypisywania w petli while ponizej

        printf("1. Wypisuje pozadana ilosc lancuchow (%d):\n", n );
        for( int i = 0; i < n+1 ; i++ ) { 
		/* Tutaj obslugujemy kolejne linijki */ 

                for( int j = 0; j < i; j++) { //Ta petla wypisuje kolejne wyrazy w danej linijce o numerze 'i'
                        
			/* Tutaj obslugujemy pojedynczy wyraz */

			for( int a = 0; a < nr_wyrazu; a++)
                                printf("a");
			
			printf("S");
                        
			for(int a = 0; a < nr_wyrazu; a++)
                                printf("a");
                        
			printf(" -> ");
			
			if( i == 1) printf("ε");
                        
			nr_wyrazu++;
                }
		
		/* Wypisanie lancucha koncowego po usunieciu symbolu pustego, jezeli wyraz na koncu linijki */
		for( int k = 0; k < 2*(i-1); k++ ) 
			printf("a");

                if( i != n ) printf("\n");
                nr_wyrazu = 0; /* Przejscie do nastepnej linijki, wiec wyzerowanie numeru aktualnie obslugiwanego wyrazu w linijce */
        }

        printf("\n\n");
}

