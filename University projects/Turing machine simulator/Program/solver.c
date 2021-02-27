#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "MT.h"

/* Zmienne pomocnicze okreslajace aktualne atrybuty glowicy MT */
int currentState = 0;
char charToWrite;
char direction;
int position = 1;

int moveHead( char input ) {
	switch( currentState ) {
		case 0:
			if( input == '0' ) {
				currentState = 1;
				charToWrite = 'B';
				direction = 'P';
				return 1;
			} else if( input == '1' ) {
				      currentState = 5;
				      charToWrite = 'B';
				      direction = 'P';
				      return 1;
				} else return 0;
			break;
		
		case 1:
			if( input == '0' ) {
                                currentState = 1;
                                charToWrite = '0';
                                direction = 'P';
                                return 1;
                        } else if( input == '1' ) {
                                      currentState = 2;
                                      charToWrite = '1';
                                      direction = 'P';
                                      return 1;
                                } else return 0;
			break;
		
		case 2:
			if( input == '0' ) {
                                currentState = 3;
                                charToWrite = '1';
                                direction = 'L';
                                return 1;
                        } else if( input == '1' ) {
                                      currentState = 2;
                                      charToWrite = '1';
                                      direction = 'P';
                                      return 1;
                                } else if( input == 'B' ) {
					currentState = 4;
                                      	charToWrite = 'B';
                                      	direction = 'L';
                                      	return 1;
					}
			break;
		
		case 3: 
			if( input == '0' ) {
                                currentState = 3;
                                charToWrite = '0';
                                direction = 'L';
                                return 1;
                        } else if( input == '1' ) {
                                      currentState = 3;
                                      charToWrite = '1';
                                      direction = 'L';
                                      return 1;
                                } else if( input == 'B' ) {
                                        currentState = 0;
                                        charToWrite = 'B';
                                        direction = 'P';
                                        return 1;
                                        }
			break;
		
		case 4:
			if( input == '0' ) {
                                currentState = 4;
                                charToWrite = '0';
                                direction = 'L';
                                return 1;
                        } else if( input == '1' ) {
                                      currentState = 4;
                                      charToWrite = 'B';
                                      direction = 'L';
                                      return 1;
                                } else if( input == 'B' ) {
                                        currentState = 6;
                                        charToWrite = '0';
                                        direction = 'P';
                                        return 1;
                                        }
			break;
		
		case 5:
			if( input == '0' ) {
                                currentState = 5;
                                charToWrite = 'B';
                                direction = 'P';
                                return 1;
                        } else if( input == '1' ) {
                                      currentState = 5;
                                      charToWrite = 'B';
                                      direction = 'P';
                                      return 1;
                                } else if( input == 'B' ) {
                                        currentState = 6;
                                        charToWrite = 'B';
                                        direction = 'P';
                                        return 1;
                                        }
			break;
		
		case 6:
			return 0;
	}
	return 0;
}

char *solver( char *input ) {
	char *tape = malloc( sizeof(char) * ( strlen( input ) + 3 ) );
	
	tape[1] = 'H';  //Pozycja glowicy na tasmie ( H -> head (glowica) )
	
	/* Nakreslenie obu granic naszej tasmy wejsciowej */
	tape[0] = 'B';
	tape[strlen( input ) +2] = 'B';
	
	for( int i = 2; i < strlen( input ) + 2; i++ )
		tape[i] = input[i-2];

	int iterationCount = 1; //Zmienna pomocnicza do wyswietlania opisow chwilowych
	while( 1 ) {	
		for( int j = 0; j < strlen( tape ); j++ ) {
			if( tape[j] == 'H' ) printf("[q%d]", currentState );
			else if( tape[j] == 'B' && ( j == 0 || j == ( strlen( tape ) -1 ) ) ) continue;
			     else printf("%c", tape[j] );
		}	
		if( iterationCount%7 == 0 ) printf("\n");
		if( currentState != 6 ) printf("|-> ");
		
		char currentInput = tape[position + 1];
		
		if( moveHead( currentInput ) == 0 ) break;
		
		if( direction == 'P' ) {
			tape[position] = charToWrite;
			tape[position + 1] = 'H';
			position++;
		} else {
			tape[position + 1] = charToWrite;
			tape[position] = tape[position - 1];
			tape[position - 1] = 'H';
			position--;
		}
		iterationCount++;
	}
	
	if( currentState != 6 ) {
		printf("Maszyna Turinga zatrzymala sie na niedozwolonym stanie.\n");
		printf("Ponizszy wynik jest definitywnie nieprawidlowy.\n");
		return tape;
	}
		
	return tape;	
}
