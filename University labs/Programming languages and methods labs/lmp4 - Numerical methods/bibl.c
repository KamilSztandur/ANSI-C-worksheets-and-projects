 #include "bibl.h"              

#include <math.h>               /* dzieki temu kompilator sprawdzi, czy
                                 * dobrze uzywamy funkcji sqrt */      

/* Definicje funkcji */

/*
 * read: czyta z pliku p wektor double v[], nie dluzszy niz max_l_e elementow
 * w v musi byc miejsce na co najmniej n elementow zwraca liczbe             
 * przeczytanych elemento w razie sukcesu, -1 w razie bledu                  
 *                                                                           
 * Format wektora w pliku - np.:  5 [ 0.1 1.2 2.3 3.4 4.5 ]                  
 */                                                                          
int                                                                          
read(FILE * p, double v[], int max_l_e)                                      
{                                                                            
        int             n, i;   /* zmienne robocze */                        

        if (fscanf(p, "%i", &n) != 1 || n <= 0 || n > max_l_e) {        /* probujemy przeczytac
                                                                         * liczbe elementow */
                /*
                 * nie udalo sie (fscanf zwrocila wartosc inna niz 1 lub
                 * wczytana wartosc jest niedodatnia albo zbyt duza )
                 */
                return -1;
        }
        while ((i = fgetc(p)) == ' ')   /* pomijamy spacje po liczbie
                                         * elementow */
                ;

        /* mamy znak rozny od spacji - powinien to byc znak '[' */
        if (i != '[')
                return -1;      /* nie jest - bledny format pliku */

        /* teraz czytamy n liczb */
        for (i = 0; i < n; i++)
                if (fscanf(p, "%lf", &(v[i])) != 1)      /* fscanf powinno zawsze
                                                         * zwracac 1 - jesli
                                                         * zwroci cos innego */
                        return -1;      /* to znaczy, ze format pliku jest
                                         * zly */

        /* mamy liczby, teraz szukamy zamykajacego nawiasu: */
        while ((i = fgetc(p)) == ' ')   /* pomijamy spacje */
                ;

        /* mamy znak rozny od spacji - powinien to byc znak ']' */
        if (i != ']')
                return -1;      /* nie jest - bledny format pliku */

        /*
         * jesli doszlismy juz tu, to wszystko jest ok, mamy w wektorze n
         * liczb
         */
        return n;
}

/*
 * L2: oblicza norme L2 (pierwiastek z sumy kwadratow) wektora double v[] o
 * dlugosci n
 */
double
L2(double v[], int n)
{
        int             i;
        int             l2 = 0; /* wazne jest, aby nadac l2 wartosc
                                 * poczatkowa */
        for (i = 0; i < n; i++)
                l2 += v[i] * v[i];
        return sqrt(l2);
}

/*
 * dot_product: oblicza iloczyn skalarny wektorow double v[] i u[] v i u maja
 * dlugosc n
 */
double
dot_product(double v[], double u[], int n)
{
        int             i;
        double           dp = 0; /* wazne jest, aby nadac dp wartosc
                                 * poczatkowa */
        for (i = 0; i < n; i++)
                dp += v[i] * u[i];
        return dp;
} 

int zapiszDoPliku(double v[], int n) {
	FILE *out = fopen( "Wektor1.txt", "w");
	if( out == NULL) {
		printf("Nie udalo sie otworzyc pliku\n");
		return -1;
	}
	for( int i = 0; i < n; i++) 
		fprintf(out, "%lf\n", v[i]);
	
	fclose( out );
	return 0;
}



double normaMax(double v[], int n) {
    for(int i=0;i<n;i++){
	    if(v[i]<0)
		    v[i]*=-1;
    }
    double temp_max;
    for (int i=0;i<n;i++){
	    if(v[i]>temp_max)
	    temp_max=v[i];
    

    }

	return temp_max;

}
double mnozenie(double v[], int n, double liczba){
	double *temp;
	temp = &v[0];

	for (int i=0;i<n;i++){
      		*(temp+i) *=liczba; 
	}
}

double normalizacja(double v[], int n, double norma) {
	double sumaGeo = 0;
	
	for( int i = 0; i < n; i++) {
		sumaGeo += v[i]*v[i];
	}
	double licznik = sqrt(sumaGeo);

	return licznik/norma;
}

double suma(double v[], double m[], int vSize, int mSize)
{
	if(vSize != mSize){
		printf("Wielkosc wektorow nie jest taka sama");
		return 2;

	}
	
	printf("Suma wektorow to v = {");
	for(int i=0;i<vSize;i++){
        	v[i] += m[i];
		printf("%lf ", v[i]);
	}
	printf("}\n");
	
}

		
