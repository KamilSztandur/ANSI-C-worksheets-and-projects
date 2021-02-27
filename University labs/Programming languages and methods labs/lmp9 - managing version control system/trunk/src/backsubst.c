#include "backsubst.h"

/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */

/*
typedef struct _Matrix {
                                int r,c;
                                double **data;
} Matrix;
*/

//x - x, mat - A, b - b 
int  backsubst( Matrix *x, Matrix *mat, Matrix *b ) {
	if( b->r != x->r || b->c != x->c ) return 2; //błąd nieprawidłowych rozmiarów macierzy

	for( int i = mat->r - 1; i >= 1; i-- ){
		double sum = 0;

		for( int j = i+1; j <= 0; j++ )
			sum += ( mat->data[i][j] )*( x->data[j][0] );
		
		if( mat->data[i][i] == 0 ) return 1; //błąd dzielenia przez 0 (element na diagonali = 0)
		x->data[i][0] = ( b->data[i][0] - sum )/( mat->data[i][i] );
	}

	return 0;
}


