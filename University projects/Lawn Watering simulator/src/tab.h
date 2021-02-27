#ifndef _TABLE_H
#define _TABLE_H

#include <png.h>
#include <stdint.h>

#include "common.h"

/* Struktury potrzebne do eksportu do png */
typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} pixel_t;

typedef struct {
  pixel_t *pixels;
  size_t width;
  size_t height;
} bitmap_t;

/* Struktura przechowujaca wazne informacje o danym zraszaczu */
typedef struct {
  int x;
  int y;
  SprinklerType type;
  Direction direction;
} location;

/*
=============================
        sprinklers.c
=============================
*/

/* Funkcja tworzaca nowy zraszacz */
location *set_new(location *tab, int x, int y, SprinklerType type, int direcion,
                  int *spr_size, int *spr_count);

/* Funkcja zwiekszajaca pojemnosc tabeli zraszaczy w przypadku przepelnienia */
location *increase(location *tab, int *spr_size);

/*
=============================
        drawInArray.c
=============================
*/

/* Funkcja podnoszaca poziom nawodnienia wszystkich komorek w tabeli w zasiegu
 * ich zraszaczy */
void draw_circle(int **tab, int x, int y, SprinklerType type,
                 Direction direction, int add_value);

/*
=============================
        create_png.c
=============================
*/

/* Funkcja wskazujaca pixel, ktory w danym momencie jest modyfikowany */
static pixel_t *pixel_at(bitmap_t *bitmap, int r, int c);

/* Bebechy silnika zapisu do pliku png */
static int save_png_to_file(bitmap_t *bitmap, const char *path);

/* Glowna funkcja zapisu tabeli do pliku png */
int make_png(int **tab, int height, int width, int count, char *filename,
             double spr_average, double spr_deviation);

/*
=============================
        create_txt.c
=============================
*/

/* Funkcja wypisujaca do pliku txt tylko (jak na razie) koordynaty oraz typy
 * zraszaczy */
void make_txt(location *sprinklers, int count, char *filename,
              double spr_average, double spr_deviation, int spr_count);

#endif
