#include <stdio.h>
#include <stdlib.h>

typedef struct structure {
	int par_level;
	char *funame;
	struct structure *next;
} fun_stack;

void *put_on_funstack(fun_stack **stack, char *name, int number) {
	if(*stack == NULL) {
		*stack = (fun_stack *) malloc(sizeof(fun_stack));
		(*stack)->funame = name;
		(*stack)->par_level = number;
		(*stack)->next = NULL;
	}
	else {
		fun_stack *new_fun_stack;
		new_fun_stack = (fun_stack *) malloc(sizeof(fun_stack));
		new_fun_stack->funame = name;
		new_fun_stack->par_level = number;
		new_fun_stack->next = *stack;
		*stack = new_fun_stack;
	}
}

char *get_from_fun_stack(fun_stack **stack) {
	char *funameToReturn;
	if(*stack == NULL) {
		printf("Stack underflow!\n");
		return NULL;
	} else {
		fun_stack *temp = NULL;
		funameToReturn = (*stack)->funame;
		temp = (*stack)->next;
		free(*stack);
		*stack = temp;
		return funameToReturn;
	}
}

int top_of_funstack( fun_stack *stack ){
        int n;
        if( stack == NULL ) {
                printf("Stos jest pusty!\n");
                return -5;
        }
        else {
                n = stack->par_level;
                return n;
        }
}


void show(fun_stack *stack) {
	if(stack == NULL)
		printf("Stack is empty!\n");
	else {
		fun_stack *temp = stack;
		do {
			printf("%i ",temp->par_level);
			printf("%s",temp->funame);
			printf("\n");
			temp = temp->next;
		}while(temp != NULL);
	}
}
int main() {
	fun_stack *stos;
	stos = NULL;
	
	printf("Podaje stosowi firstf(), zaglebienie nawiasowe: 5\n");
	put_on_funstack( &stos, "firstf", 5 );
	
	printf("Podaje stosowi secondf(), zaglebienie nawiasowe: 7\n");
	put_on_funstack( &stos, "secondf", 7 );
	
	printf("Podaje stosowi thirdf(), zaglebienie nawiasowe: 6\n");
	put_on_funstack( &stos, "thirdf", 6 );
	
	printf("\nAktualny stan stosu:\n");
	show( stos );
	printf("\n\n");
	
	char *test = get_from_fun_stack( &stos );
        printf("Zdjalem nazwe %s ze stosu.\n", test);

        int test_n = top_of_funstack( stos );
        printf("Zaglebienie nawiasowe przechowywane na szczycie stosu to %d\n", test_n );
	
	printf("\nKoncowy stan stosu:\n");
	show(stos);

}

