#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "tab.h"

int **parse_shape(FILE *in, int *cycles) {
  if (fscanf(in, "%d\n", cycles) != 1 || *cycles <= 0)
    print_help();

  char ch;

  int **result = malloc(sizeof(int *) * INPUT_HEIGHT);

  for (int i = 0; i < INPUT_HEIGHT; i++) {
    result[i] = malloc(sizeof(int) * INPUT_WIDTH);
  }

  for (int y = 0; y < 40; y++) {
    for (int x = 0; x < 80; x++) {
      fscanf(in, "%c", &ch);

      if (ch == '*' || ch == '-') {
        result[y][x] = (ch == '*') ? 0 : -1;
      } else if (ch == '\n')
        x--;
      else {
        printf("W podanym pliku tekstowym znajduje sie niedozwolony znak.\n");
        exit(1);
      }
    }
  }

  return result;
}

int **upscale_shape(int **input) {
  int **result = malloc(sizeof(int *) * HEIGHT * 2);

  for (int i = 0; i < HEIGHT * 2; i++) {
    result[i] = malloc(sizeof(int) * WIDTH * 2);
  }

  for (int y = 0; y < 40; y++) {
    for (int x = 0; x < 80; x++) {
      for (int l = 0; l < 100; l++) {
        for (int m = 0; m < 100; m++)
          result[100 * y + l][100 * x + m] = input[y][x];
      }
    }
  }

  return result;
}

void print_help(void) {
  printf("Program nalezy uruchamiac z jednym argumentem.\n");
  printf("Jest nim nazwa pliku tekstowego opisujacego trawnik.\nPlik musi "
         "zawierac liczbe cykli (dodatnia) w pierwszej linijce.\n\n");
  exit(1);
}
