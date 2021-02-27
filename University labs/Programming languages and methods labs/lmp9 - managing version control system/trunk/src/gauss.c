#include "gauss.h"

/*
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
*/

int eliminate(Matrix *mat, Matrix *b){
        double tmp = 0;
        for( int i = 0; i <= mat->r; i++ ){
                for( int j = 0; j <= mat->c; j++ ){
                        if( i > j ) {
                                if( mat->data[j][j] == 0 ) return 1; //macierz osobliwa - dzielenie przez 0

                                tmp = mat->data[i][j] / mat->data[j][j];

                                for( int k = 0; k <= mat->c; k++ )
                                        mat->data[i][k] = mat->data[i][k] - tmp*(mat->data[j][k]);
                        }
                }
        }

	return 0;
}

