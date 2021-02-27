#include "skorowidz.h"

/*
 * Funkcja wypisujaca skorowidz na ekran.
 * 
 * Tabela wystapieniaLinijki zostala utworzona w main i uzupelniona w szukajSlow.c. Jej struktura jest np.:
 * 
 * wystapieniaLinijki[0] = 0 0 1 0 0 1 1 1 
 * wystapieniaLinijki[1] = 1 1 1 0 1 0 1 1 
 * wystapieniaLinijki[2] = 0 1 0 1 1 1 0 0
 * (...)
 * wystapieniaLinijki[n]
 *
 * Gdzie pierwszy indeks to numer slowa, ktoremu przypisana jest liniowa tabela o dlugosci liczby linijek w pliku.
 * Numer indeksu odpowiada numerom poszczegolnych wierszy.
 * 0 oznacza, ze dane slowo nie wystapilo w tym wierszu. 1 oznacza, ze wystapilo
 *
 * Na poczatku funkcja sprawdza, czy wartosc skorowidz->ostatnieWystapienie[nr_slowa] jest wieksze od zera, czyli czy slowo w ogole wystapilo.
 * Jezeli nie, to zwraca komunikat i przechodzi do nastepnego slowa.
 * Jezeli tak, to rozpoczyna wypisywanie numerow linii na podstawie "zapalonych" indeksow tabeli wystapienialinjki
*/

void wypiszSkorowidz( skorowidz_t *skorowidz, int **wystapieniaLinijki ) {
        printf(".----------------*( Skorowidz )*-----------------.\n");
        for( int i = 0; i < skorowidz->ileSlow; i++ ) {
		if( skorowidz->ostatnieWystapienie[i] > 0 ) {
                        printf( "%d. Słowo \"%s\" wystąpiło w liniach nr: ", i+1, skorowidz->slowa[i] );
                         for( int j = 1; j <= skorowidz->ostatnieWystapienie[i]; j++ )
                                if ( wystapieniaLinijki[i][j] > 0 ) printf( " %d", j );
                        printf( ".\n" );
                } else printf( "%d. Nie napotkano słowa \"%s\".\n", i+1, skorowidz->slowa[i] );
        }
	printf("*------------------*( KONIEC )*------------------*\n");
}
