#include <stdio.h>
#ifndef SKOROWIDZ_H
#define SKOROWIDZ_H

typedef struct {
        int ileSlow; //Ile argumentow wpisal uzytkownik
        char **slowa; //Tabelka przechowujaca te argumenty
        int *ostatnieWystapienie; //Numer linii ostatniego wystapienia slowa (pomocne przy wypisywaniu)
} skorowidz_t;

void inicjujSkorowidz( skorowidz_t *skorowidz, int argc, char **argv );

void szukajSlow( skorowidz_t *skorowidz, int **wystapieniaLinijki, FILE* in );

void wypiszSkorowidz( skorowidz_t *skorowidz, int **wystapieniaSlow );

#endif                 
