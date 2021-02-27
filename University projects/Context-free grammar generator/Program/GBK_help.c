#include "GBK.h"
#include <stdio.h>
#include <stdlib.h>

void help() {
        printf("\n");
        printf("Podaj programowi jako pierwszy parametr liczbe lancuchow, ktore\n");
        printf("chcesz wygenerowac. Zostana one wygenerowane na podstawie powyzszej\n");
        printf("gramatyki bezkontekstowej oraz jezyka.\n\n");
        printf("Przyklad uzycia:\n");
        printf("\n./GBKgen 5\n\n");
        exit(0);
}

