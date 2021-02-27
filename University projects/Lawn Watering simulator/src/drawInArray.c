#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tab.h"

int contains_quarter(int quarter, SprinklerType type, Direction direction) {
  switch (type) {
  case FULL:
    return 1;
  case THREE_QUARTERS:
    return quarter != (direction - 1) % 4;
  case HALF:
    return quarter == direction || quarter == (direction + 1) % 4;
  case QUARTER:
    return quarter == direction;
  }
}

/* "X, Y" to wspolrzedne
 * "direction" odpowiada za to jak zwrocony jest zraszacz.
 * Pelna dokumentacje i wariacje wyslalem na konfie jako zdjecie
 */

void draw_circle(int **tab, int x, int y, SprinklerType type,
                 Direction direction, int add_value) {
  int r, r2;
  int point_x, point_y;

  switch (type) {
  case FULL:
    r = FULL_RADIUS;
    break;
  case THREE_QUARTERS:
    r = THREE_QUARTERS_RADIUS;
    break;
  case HALF:
    r = HALF_RADIUS;
    break;
  case QUARTER:
    r = QUARTER_RADIUS;
    break;
  }

  r2 = pow(r, 2);
  for (int i = 0; i <= r; i++) {
    for (int j = 0; j <= r; j++) {
      if (pow(i, 2) + pow(j, 2) <= r2) {
        /* GÓRA-LEWO */
        if (contains_quarter(LEFT, type, direction) && ((y - i) < HEIGHT) &&
            ((y - i) >= 0) && ((x - j) < WIDTH) && ((x - j) >= 0)) {

          if (tab[y - i][x - j] == -1) {

            int d = 0;
            int e = 0;

            while (y - i + d >= 0 && y - i + d < 4000 &&
                   tab[y - i + d][x - j] == -1)
              ++d;
            while (x - j + e >= 0 && x - j + e < 8000 &&
                   tab[y - i][x - j + e] == -1)
              ++e;

            if (d < e) {

              point_y = y - i + 2 * d;
              point_x = x - j;

              if ((point_y >= 0) && (point_y < 4000) &&
                  (tab[point_y][point_x] != -1))
                tab[point_y][point_x] += add_value;
            } else {

              point_y = y - i;
              point_x = x - j + 2 * e;

              if ((point_x >= 0) && (point_x < 8000) &&
                  (tab[point_y][point_x] != -1))
                tab[point_y][point_x] += add_value;
            }
          } else
            tab[y - i][x - j] += add_value;
        }

        /* GÓRA - PRAWO */
        if (contains_quarter(TOP, type, direction) && ((y - i) < HEIGHT) &&
            ((y - i) >= 0) && ((x + j) < WIDTH) && ((x + j) >= 0)) {

          if (tab[y - i][x + j] == -1) {

            int d = 0;
            int e = 0;

            while (y - i + d >= 0 && y - i + d < 4000 &&
                   tab[y - i + d][x + j] == -1)
              ++d;

            while (x + j - e >= 0 && x + j - e < 8000 &&
                   tab[y - i][x + j - e] == -1)
              ++e;

            if (d < e) {

              point_y = y - i + 2 * d;
              point_x = x + j;

              if ((point_y >= 0) && (point_y < 4000) &&
                  (tab[point_y][point_x] != -1))
                tab[point_y][point_x] += add_value;
            } else {

              point_y = y - i;
              point_x = x + j - 2 * e;

              if ((point_x >= 0) && (point_x < 8000) &&
                  (tab[point_y][point_x] != -1))
                tab[point_y][point_x] += add_value;
            }
          } else
            tab[y - i][x + j] += add_value;
        }

        /* DÓŁ - PRAWO */
        if (contains_quarter(RIGHT, type, direction) && ((y + i) < HEIGHT) &&
            ((y + i) >= 0) && ((x + j) < WIDTH) && ((x + j) >= 0)) {

          if (tab[y + i][x + j] == -1) {

            int d = 0;
            int e = 0;

            while (y + i - d >= 0 && y + i - d < HEIGHT &&
                   tab[y + i - d][x + j] == -1)
              ++d;

            while (x + j - e >= 0 && x + j - e < WIDTH &&
                   tab[y + i][x + j - e] == -1)
              ++e;

            if (d < e) {

              point_y = y + i - 2 * d;
              point_x = x + j;

              if (point_y < HEIGHT && point_y >= 0 &&
                  tab[point_y][point_x] != -1)
                tab[point_y][point_x] += add_value;
            } else {

              point_y = y + i;
              point_x = x + j - 2 * e;

              if (point_x < 8000 && point_x >= 0 && tab[point_y][point_x] != -1)
                tab[point_y][point_x] += add_value;
            }
          } else
            tab[y + i][x + j] += add_value;
        }

        /* DÓŁ - LEWO */
        if (contains_quarter(BOTTOM, type, direction) && ((y + i) < HEIGHT) &&
            ((y + i) >= 0) && ((x - j) < WIDTH) && ((x - j) >= 0)) {

          if (tab[y + i][x - j] == -1) {

            int d = 0;
            int e = 0;

            while (y + i - d >= 0 && y + i - d < HEIGHT &&
                   tab[y + i - d][x - j] == -1)
              ++d;

            while (x - j + e >= 0 && x - j + e < WIDTH &&
                   tab[y + i][x - j + e] == -1)
              ++e;

            if (d < e) {

              point_y = y + i - 2 * d;
              point_x = x - j;

              if (point_y >= 0 && point_y < 4000 && tab[point_y][point_x] != -1)
                tab[point_y][point_x] += add_value;
            } else {

              point_y = y + i;
              point_x = x - j + 2 * e;

              if (point_x >= 0 && point_x < 8000 && tab[point_y][point_x] != -1)
                tab[point_y][point_x] += add_value;
            }
          } else
            tab[y + i][x - j] += add_value;
        }
      }
    }
  }

  /* Skorygowanie komórek, ktore powiekszyly sie kilka razy przez przypadek */
  switch (type) {
  case 1:
    tab[y][x] += add_value;
    for (int i = 0; i < r + 1; i++) {
      if ((y + i < HEIGHT) && (tab[y + i][x] != -1))
        tab[y + i][x] -= add_value;
      if ((y - i >= 0) && (y - i < HEIGHT) && (tab[y - i][x] != -1))
        tab[y - i][x] -= add_value;
      if ((x + i < WIDTH) && (tab[y][x + i] != -1))
        tab[y][x + i] -= add_value;
      if ((x - i >= 0) && (x - i < WIDTH) && (tab[y][x - i] != -1))
        tab[y][x - i] -= add_value;
    }
    break;

  case 2:
    tab[y][x] -= 2 * add_value;
    for (int i = 1; i <= r; i++)
      if ((x - i >= 0) && (x - i < WIDTH) && (tab[y][x - i] != -1))
        tab[y][x - i] -= add_value;

    switch (direction) {
    case 1:
      for (int i = 1; i <= r; i++)
        if ((y + i < HEIGHT) && (tab[y + i][x] != -1))
          tab[y + i][x] -= add_value;
      break;
    case 2:
      for (int i = 1; i <= r; i++)
        if ((y - i >= 0) && (y - i < HEIGHT) && (tab[y - i][x] != -1))
          tab[y - i][x] -= add_value;
      break;
    case 3:
      for (int i = 1; i <= r; i++) {
        if ((x - i >= 0) && (x - i < WIDTH) && (tab[y][x - i] != -1))
          tab[y][x - i] += add_value;
        if ((x + i < WIDTH) && (tab[y][x + i] != -1))
          tab[y][x + i] -= add_value;
        if ((y - i >= 0) && (y - i < HEIGHT) && (tab[y - i][x] != -1))
          tab[y - i][x] -= add_value;
      }
      break;

    case 4:
      for (int i = 1; i <= r; i++) {
        if ((x + i < WIDTH) && (tab[y][x + i] != -1))
          tab[y][x + i] -= add_value;
        if ((x - i >= 0) && (x - i < WIDTH) && (tab[y][x - i] != -1))
          tab[y][x - i] += add_value;
        if ((y + i < HEIGHT) && (tab[y + i][x] != -1))
          tab[y + i][x] -= add_value;
      }
      break;
    }
    break;

  case 3:
    tab[x][y] -= add_value;
    for (int i = 1; i < r + 1; i++) {
      if (direction != 3 && (y - i >= 0) && (y - i < HEIGHT) &&
          (tab[y - i][x] != -1))
        tab[y - i][x] -= add_value;
    }

    switch (direction) {
    case 2:
      for (int i = 1; i <= r; i++) {
        if ((x + i < WIDTH) && (tab[y][x + i] != -1))
          tab[y][x + i] -= add_value;
        if ((y - i >= 0) && (y - i < HEIGHT) && (tab[y - i][x] != -1))
          tab[y - i][x] += add_value;
      }
      break;

    case 3:
      for (int i = 1; i <= r; i++) {
        if ((y + i < HEIGHT) && (tab[y + i][x] != -1))
          tab[y + i][x] -= add_value;
      }
      break;
    case 4:
      for (int i = 1; i <= r; i++) {
        if ((x - i >= 0) && (x - i < WIDTH) && (tab[y][x + i] != -1))
          tab[y][x - i] -= add_value;
        if ((y - i >= 0) && (y - i < HEIGHT) && (tab[y - i][x] != -1))
          tab[y - i][x] += add_value;
      }
      break;
    }
    break;
  }
}
