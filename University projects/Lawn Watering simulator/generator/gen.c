#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAIN_HEIGHT 36
#define MAIN_WIDTH 72
#define BLOCK_HEIGHT 6
#define BLOCK_WIDTH 8

int main(void) {
  char line[MAIN_WIDTH + 1];
  char type;

  FILE *f = fopen("trawnik.txt", "w");

  srand(time(NULL));
  fprintf(f, "%d\n", rand() % 50 + 1);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 80; j++) {
      fprintf(f, "%c", '-');
    }
    fprintf(f, "\n");
  }

  for (int i = 0; i < MAIN_HEIGHT; i += BLOCK_HEIGHT) {
    for (int j = 0; j < MAIN_WIDTH; j += BLOCK_WIDTH) {
      type = rand() % 100 >= 20 ? '*' : '-';

      for (int k = 0; k < BLOCK_WIDTH; k++)
        line[k + j] = type;
    }

    line[MAIN_WIDTH] = '\0';

    for (int j = 0; j < BLOCK_HEIGHT; j++) {
      fprintf(f, "----");
      fprintf(f, "%s", line);
      fprintf(f, "----\n");
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 80; j++) {
      fprintf(f, "%c", '-');
    }
    fprintf(f, "\n");
  }

  fclose(f);

  return 0;
}
