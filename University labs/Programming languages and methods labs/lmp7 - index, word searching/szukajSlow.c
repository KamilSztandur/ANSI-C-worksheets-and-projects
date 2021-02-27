#include "skorowidz.h"
#include <string.h>
#include <ctype.h>

/* 
 * Funkcja wyszukace podane przez uzytkownika slowa w tekscie.
 * Tworzymy bufor dla pobranego wiersza o maksymalnej wielkosci definiowanej w stalej BUFSIZE (tutaj 8kb).
 * W kazdej linii szukamy kolejnych slow. Sprawdzamy, czy znak przed oraz po znalezionym slowie jest litera, aby wykluczyc slowa znalezione w srodku innych slow.
 * Jezeli szukane slowo wystepuje w tej linijce i pomyslnie przeszlo powyzsza weryfikacje, to zapalamy jedynke indeksowi w tabeli odpowiadajacemu tego nr wiersza
 * Zapisujemy do zmiennej skorowidz->ostatnieWystapienie obecny numer linijki, w ktorej to znalezlismy
 * W przypadku zakonczenia iteracji ten numer bedzie numerem wiersza, w ktorym ostatni raz to slowo sie pojawilo.
 * Jest to potrzebne do mojej funkcji wypisujacej skorowidz na ekran. Wiecej wyjasnie pozniej
*/

#define BUFSIZE 8192   // zakładamy, że linie będą krótsze niż 8kB

void szukajSlow( skorowidz_t *skorowidz, int **wystapieniaLinijki, FILE *in ) {
        char buf[BUFSIZE];
	int nrLinii = 0;
	while( fgets( buf, BUFSIZE, in ) != NULL ) {
                nrLinii++;
                for( int i = 0; i < skorowidz->ileSlow; i++ ) {
                        char* wskaznikSlowo = strstr( buf, skorowidz->slowa[i] );
                        if( wskaznikSlowo != NULL ) {
                                /* Niestety, ale funkcja isalpha() i ogolnie ta biblioteka nie traktuja polskich znakow jako litery :( */
                                if( isalpha( (wskaznikSlowo-1)[0] ) != 0 || isalpha( ( wskaznikSlowo + strlen( skorowidz->slowa[i] ) )[0] ) != 0  ) continue;
                                wystapieniaLinijki[i][nrLinii] = 1;
                                skorowidz->ostatnieWystapienie[i] = nrLinii;
                        }
                }
        }
}
