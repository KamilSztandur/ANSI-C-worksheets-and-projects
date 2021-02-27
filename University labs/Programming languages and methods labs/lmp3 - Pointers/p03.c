#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double min(double t[], int tsize) 
{
	double act_min = t[0];
	for(int i = 0; i < tsize; i++)
	{
		if( t[i] < act_min) act_min = t[i];
	}

	return act_min;
}
	
double average(double t[], int tsize)
{
	double avg = 0, sum = 0;
	for(int i = 0; i < tsize; i++) sum += t[i];

	avg = sum/tsize;

	return avg;
}

int main(int argc, char *argv[])
{
	FILE *in = argc > 1 ? fopen( argv[1], "r") : stdin;

	if (in != NULL) 
	{
		int words = 0;
		char ch;

		while( (ch=fgetc(in)) != EOF) //Policzenie ilosci liczb w celu utworzenia odpowiedniej tabeli
		{
			if( ch == '\n' || ch == ' ') words++;
		}
		
		double *r = malloc(words*sizeof(double));
		
		fclose(in);
	 	
		fopen( argv[1], "r");
			
		int j = 0; //Pomocnicza zmienna dla petli do przepisywania liczb do tabeli
		double x; //Pomocnicza zmienna przechowujaca dany ulamek
		while( fscanf( in, "%lf", &x) == 1) //Przepisywanie liczb z txt do tabeli
		{
			r[j] = x;
			j++;
		}	

		printf("===================================\n");
		for( int i = 0; i < words; i++) printf("%lf\n", r[i]); //Wydrukowanie liczb na ekran

		fclose(in);

		printf("====================================\n");
		printf("Minimalna wartosc w pliku to: %lf\n", min(r, words));
		printf("Srednia tych liczb to: %lf\n", average(r, words));

		return 0;
	}
	else return 1;
}
