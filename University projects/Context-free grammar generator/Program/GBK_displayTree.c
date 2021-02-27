#include "GBK.h"
#include <stdio.h>

void displayTree( int n ) {
        printf("2. Wypisuje drzewo najdluzszego lancucha:\n\n");
        
	printf("       S\n");
	if( n == 1 ) printf("       |\n");
        else {
                for( int i = 0; i < n; i++) {
                        if( i != 0 ) printf("       S\n");
                        if( i != n-1 ) {
				printf("      /|\\ \n");
                        	printf("     / | \\ \n");
                        	printf("    a  |  a\n");
			} else {
				printf("       |\n");
				printf("       |\n");
			}
                }
        }

        printf("       ε\n\n");
}
