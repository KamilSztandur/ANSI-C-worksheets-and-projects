#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tab.h"

/* Dodanie nowego zraszacza do listy */
location *set_new(location *tab, int x, int y, SprinklerType type,
                  int direction, int *spr_size, int *spr_count) {
  if (*spr_count >= *spr_size)
    tab = increase(tab, spr_size);

  if (tab == NULL)
    exit(0);

  location new_sprinkler;
  new_sprinkler.x = x;
  new_sprinkler.y = y;
  new_sprinkler.type = type;
  new_sprinkler.direction = direction;

  tab[(*spr_count)++] = new_sprinkler;

  return tab;
}

location *increase(location *tab, int *spr_size) {

  *spr_size *= 2;
  printf("Nowy rozmiar - %d\n", *spr_size);

  location *new;

  if ((new = realloc(tab, *spr_size * sizeof(location))) != NULL) {
    free(tab);
    return new;
  } else {
    printf("Za malo pamieci. Nie udalo sie powiekszyc tablicy\n");
    return NULL;
  }
}
