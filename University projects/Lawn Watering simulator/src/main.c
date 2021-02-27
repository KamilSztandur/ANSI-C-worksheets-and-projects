#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <dirent.h>
#include <errno.h>

#include "algorithm.h"
#include "input.h"
#include "stats.h"
#include "tab.h"

/* Zmienne pomocnicze do zarzadzania tabela struktur zraszaczy "sprinkler_tab"
 * typu "location" */

/* Tutaj wybieramy nazwe pliku, do ktorego chcemy eksportowac lokalizacje
 * naszych zraszaczy */

/* Tutaj wybieramy nazwe pliku png, ktory bedzie reprezentowac nasz trawnik */

int main(int argc, char **argv) {
  FILE *in;
  int i;
  char *txt_filename = "./output/koordynaty.txt";
  char *png_filename = "./output/trawnik.png";

  if (argc != 2)
    print_help();

  in = fopen(argv[1], "r");

  if (in == NULL) {
    printf("Niepoprawnie podano plik tekstowy\n");
    print_help();
  }

  printf("Pracuję nad rozstawieniem zraszaczy... (To może zająć chwilę)\n");

  int cycle_count;
  int **shape = parse_shape(in, &cycle_count);
  int **lawn = upscale_shape(shape);

  int spr_count = 0;
  int spr_size = 1000;
  location *sprinkler_tab = malloc(spr_size * sizeof(location));
  
  get_locations(shape, lawn, cycle_count, sprinkler_tab, &spr_count, &spr_size);
  printf("Sukces.\n\n");
  
  printf("Przeczytałem %d cykli.\n\n", cycle_count);

  printf("Tworzę folder 'output' do zapisu plików wyjściowych...\n");
  DIR *dir = opendir("output");
  if (ENOENT == errno) {
    /* W przypadku, gdy wskazany folder nie istnieje */
    system("mkdir output");
    dir = opendir("output");
  }
  printf("Sukces.\n\n");

  printf("Liczę srednią arytmetyczną...\n");
  double spr_average = average(lawn);
  printf("Sukces - %lf\n", spr_average);

  printf("Liczę odchylenie standardowe...\n");
  double spr_deviation = std_deviation(lawn, spr_average);
  printf("Sukces - %lf\n\n", spr_deviation);

  printf("Eksportuję tablicę do pliku %s...\n", png_filename);
  make_png(lawn, HEIGHT, WIDTH, spr_count, png_filename, spr_average,
           spr_deviation);
  printf("Sukces.\n\n");

  printf("Wypisuję dane zraszaczy i trawnika do pliku %s...\n", txt_filename);
  make_txt(sprinkler_tab, spr_count, txt_filename, spr_average, spr_deviation,
           spr_count);
  printf("Sukces.\n\n");

  closedir(dir);
  
  printf("Sprzątam...\n");
  free_array(shape, INPUT_HEIGHT);
  free_array(lawn, 2 * HEIGHT);
  free(sprinkler_tab);

  fclose(in);
  printf("Sukces.\n\nPomyślnie zakończono dzialanie programu.\n");
  return 0;
}
