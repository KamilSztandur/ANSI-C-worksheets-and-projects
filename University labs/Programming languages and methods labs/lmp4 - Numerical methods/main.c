#include <stdio.h>
#include <stdlib.h>

#include "bibl.h"               /* dzieki temu kompilator moze sprawdzic, czy
                                 * dobrze wywolujemy funkcje z naszej
                                 * biblioteki */

int
main(int argc, char *argv[])
{
        double           w_1[10];
        double           w_2[10];
        int             n1;
        int             n2;
        int             i;

        FILE           *we = argc > 1 ? fopen(argv[1], "r") : stdin;    /* jesli argc > 1 to
                                                                         * program zostal
                                                                         * wywolany z argumentem
                                                                         * - probujemy otworzyc
                                                                         * taki plik do czytania */

        if (we == NULL) {       /* stdin != NULL, a wiec to mozliwe tylko,
                                 * gdy argv[1] zawiera cos, co nie jest nazwa
                                 * istniejacego pliku */
                fprintf(stderr, "Plik wejsciowy %s nie istnieje!\n", argv[1]);
                exit(1);
        }
        n1 = read(we, w_1, 10);   /* czytamy z wejscia wektor i pakujemy go
                                 * do w_1 */

        if (n1 > 0) {
                printf("Wczytano %i-elementowy wektor:\n( ", n1);
                for (i = 0; i < n1; i++)
                        printf("%f ", w_1[i]);
                printf(")\n");
        } else {
                fprintf(stderr, "Wystapil blad przy wczytywaniu wektora: kod bledu=%i\n", n1);
                return 1;
        }

        printf("Norma L2 wczytanego wektora = %f\n", L2(w_1, n1));

        n2 = read(we, w_2, 10);   /* czytamy z wejscia wektor i pakujemy go
                                 * do w_2 */

        if (n2 > 0) {
                printf("Wczytano %i-elementowy wektor:\n( ", n2);
                for (i = 0; i < n2; i++)
                        printf("%f ", w_2[i]);
                printf(")\n");
        } else {
                fprintf(stderr, "Wystapil blad przy wczytywaniu wektora: kod bledu=%i\n", n2);
                return 1;
        }

        printf("Norma L2 wczytanego wektora = %f\n", L2(w_2, n2));

        if (n1 == n2 ) {
                printf("Iloczyn skalarny wczytanych wektorow = %f\n", dot_product(w_1, w_2, n1));
        } else {
                printf("Wczytane wektory maja rozna dlugosci i nie mozna ich pomnozyc przez siebie\n" );
        }
        return 0;

	printf("Zapisuje wektor 1 pliku 'Wektor1.txt'...\n");
	zapiszDoPliku(w_1, n1);
	
	printf("Maksymalna wartosc wektora 1, to %lf\n", normaMax(w_1, n1));
	
	double liczba = 10; 
	printf("Mnoze wartosc wektora przez %lf\n", liczba);
	mnozenie(w_1, n1, liczba);

	printf("Pora na normalizacja wektora. Normalizuje przez Maksymalna norme Wektora to %lf.\n", normalizacja(w_1, n1, normaMax(w_1, n1)));
	printf("Suma wektor w_1 oraz w_2 to: w_s = {");
	suma(w_1, w_2, n1, n2);

	for(int i = 0; i < n1; i++)
		printf("%lf ", w_1[i]);
	printf("}\n");
}
