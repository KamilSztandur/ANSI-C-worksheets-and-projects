#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NKEYS 11

typedef struct stos {
	char *fun;
	int nawiasy;
	struct stos *next;
} stack_t;

struct keyWord {
	char *word;
	int count;
} keyTab[NKEYS] = {
	"int", 0,
	"double", 0,
	"char", 0,
	"struct", 0,
	"float", 0,
	"void", 0,
	"FILE", 0,
	"(", 0,
        ")", 0,
        "{", 0,
        "}", 0
};

void *put_on_fun_stack( stack_t **stack, char *napis, int n ) {
	if( *stack == NULL ) {
		*stack = (stack_t *)malloc( sizeof(stack_t) );
		(*stack)->fun = napis;
		(*stack)->nawiasy = n;
		(*stack)->next = NULL;
	}
	else {
		stack_t *new_stack;
		new_stack = (stack_t *)malloc( sizeof(stack_t) );
		new_stack->fun = napis;
		new_stack->nawiasy = n;
		new_stack->next = *stack;
		*stack = new_stack;
	}
}

char *get_from_fun_stack( stack_t **stack ){
	char *funame;
	if( *stack == NULL ) {
		printf("Stos jest pusty!\n");
		return NULL;
	}
	else {
		stack_t *temp = NULL;
		funame = (*stack)->fun;
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
		return funame;
	}
}

int top_of_funstack( stack_t *stack ){
        int n;
	if( stack == NULL ) {
                printf("Stos jest pusty!\n");
		return -5;
	}
        else {
                n = stack->nawiasy;
		return n;
	}
}

void show_fun_stack(stack_t *stack) {
	if(stack == NULL)
		printf("Stos jest pusty!\n");
	else {
		stack_t *temp = stack;
		do {
			printf("%s, %d",temp->fun, temp->nawiasy );
			printf("\n");
			temp = temp->next;
		}while(temp != NULL);
	}
}

int binSearch( char *word, struct keyWord keyTab[], int n ){
	int cond;
	int low, high, mid;
	low = 0;
	high = n - 1;
	
	while( low <= high ) {
		mid = (low + high)/2;
		if( (cond = strcmp( word, keyTab[mid].word )) < 0 )
			high = mid - 1;
		else if ( cond > 0 )
				low = mid + 1;
	    	     else return mid;
	}
	
	return -1;	
}

int main( int argc, char **argv ){
	stack_t *stos = NULL;
	FILE *in = fopen( argv[1], "r" );
	
	if( in == NULL ) {
		printf("Podaj mi plik z kodem!\n");
		return EXIT_FAILURE;
	}
	
	char *loadedWord;
	int isKeyWord;
         
	/*
	 * Instrukcja ponizej skanuje kod w poszukiwaniu deklaracji zmiennych, ktore wymienione sa w strukturze keyWord.
	 * Instrukcja zabezpieczona jest przed nieporozumieniami w liczeniu nawiasow, ktore moga zostac przyklejone do innego slowa
	 * przez funkcje fscanf dzieki pojedynczemu przeszukiwaniu kazdego slowa pod katem ich obecnosci.
	 *
	 * Niestety, z nieznanych przyczyn funkcja bez zadnych ingerencji w nia po kilku dniach zaczela zwracac Segmentation Fault (core dumped).
	 * Debuger takze nie mow nic pomocnego na temat wystepowania bledu poza tym, ze blad pojawia sie przy instrukcji:
	 * 
	 * 	while ( fscanf( in, "%s ", loadedWord ) != EOF )
	 * 
	 * ... ale wczesniej dzialala...
	
	while ( fscanf( in, "%s ", loadedWord ) != EOF ) {
		if( (isKeyWord = binSearch( loadedWord, keyTab, NKEYS )) >= 0 )
		      keyTab[isKeyWord].count++;

		if( strcmp( loadedWord, "{" ) == 0 ||  strcmp( loadedWord, "}" ) == 0  ) continue;
		for( int i = 0; loadedWord[i] != '\0'; i++ ) {
			if( loadedWord[i] == '(' ) keyTab[7].count++;
			if( loadedWord[i] == ')' ) keyTab[8].count++;
			if( loadedWord[i] == '{' ) keyTab[9].count++;
			if( loadedWord[i] == '}' ) keyTab[10].count++;
		}
		
	}
	*/

	printf("*---------(%s)---------*\n", argv[0] );
	
	printf( "W tym programie zadeklarowano:\n" );
	for( int i = 0; i < NKEYS; i++ )
		printf(" %s: %d razy\n", keyTab[i].word, keyTab[i].count );
	printf("\n");
	
	printf("Podaje stosowi funkcja_a(), zaglebienie nawiasowe: 12\n");
	put_on_fun_stack( &stos, "funkcja_a", 12 );

	printf("Podaje stosowi funkcja_b(), zaglebienie nawiasowe: 4\n");
	put_on_fun_stack( &stos, "funkcja_b", 4 );

	printf("Podaje stosowi main(), zaglebienie nawiasowe: 28\n");
	put_on_fun_stack( &stos, "main", 28 );
	
	printf("\nAktualny stan stosu:\n");
	show_fun_stack( stos );
	printf("\n");

	char *test = get_from_fun_stack( &stos );
	printf("Zdjalem nazwe '%s' ze stosu.\n", test);
	
	int test_n = top_of_funstack( stos );
	printf("Zaglebienie nawiasowe przechowywane na szczycie stosu to '%d'\n", test_n );
	
	printf("\nKoncowy stan stosu:\n");
	show_fun_stack( stos );
	
	printf("*--------------------------*\n");
	
	return 0;
}
