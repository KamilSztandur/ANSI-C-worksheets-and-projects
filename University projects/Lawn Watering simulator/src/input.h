#ifndef INPUT_H
#define INPUT_H

int **
parse_shape(FILE *in,
            int *cycles); /* przenosi zawartosc pliku do tablicy 2-wymiarowej*/

int **upscale_shape(int **input);

void print_help();

#endif
