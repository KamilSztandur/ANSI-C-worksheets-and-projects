#include <math.h>

#include "stats.h"

double average(int **tab) {

  long double sum = 0;
  int grass_number = 0;

  for (int i = 0; i < 4000; i++) {

    for (int j = 0; j < 8000; j++) {

      if (tab[i][j] != -1) {
        sum += tab[i][j];
        ++grass_number;
      }
    }
  }

  return sum / (double)grass_number;
}

double std_deviation(int **tab, double average) {

  long double sum = 0;
  int grass_number = 0;
  int i;
  int j;

  for (i = 0; i < 4000; i++) {

    for (j = 0; j < 8000; j++) {

      if (tab[i][j] != -1) {
        sum += pow(tab[i][j] - average, 2);
        ++grass_number;
      }
    }
  }

  return sqrt(sum / (double)grass_number);
}
