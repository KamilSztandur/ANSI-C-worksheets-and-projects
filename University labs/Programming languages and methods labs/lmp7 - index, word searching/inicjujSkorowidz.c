#include "skorowidz.h"
#include <stdlib.h>

/* 
 * Struktura skorowidzu przechowujac wartosci takie jak:
 * - Ilosc slow podanych przez uzytkownika do wyszukania
 * - Tablice tych slow
 * - Nr linijki, w ktorym ostatni raz wystapilo to slowo.
 * Ostatnia zmienna jest wymagana do prawidlowego wypisywania skorowidzu na ekran 
 * 
 * Nastepnie funkcja przepisuje slowa do szukania do tabeli slowa
*/

void inicjujSkorowidz( skorowidz_t *skorowidz, int argc, char **argv ) {
        skorowidz->ileSlow = argc-2; 
        skorowidz->slowa = malloc( skorowidz->ileSlow * sizeof * skorowidz->slowa );
        skorowidz->ostatnieWystapienie = malloc( skorowidz->ileSlow * sizeof * skorowidz->ostatnieWystapienie );
	
        for( int i = 2; i < argc; i++ ) {
                skorowidz->slowa[i-2] = argv[i];
                skorowidz->ostatnieWystapienie[i-2] = 0;
        }
}
