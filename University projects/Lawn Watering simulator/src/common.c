#include <stdlib.h>
#include <string.h>

#include "common.h"

int get_direction_horizontal_offset(Direction direction) {
  return direction == LEFT ? -1 : direction == RIGHT ? 1 : 0;
}

int get_direction_vertical_offset(Direction direction) {
  return direction == TOP ? -1 : direction == BOTTOM ? 1 : 0;
}

int get_edge_horizontal_offest(Direction direction, int external) {
  direction = external ? (direction + 1) % 4 : direction;

  return direction == LEFT || direction == BOTTOM ? 1 : 0;
}

int get_edge_vertical_offest(Direction direction, int external) {
  direction = external ? (direction + 1) % 4 : direction;

  return direction == LEFT || direction == TOP ? 1 : 0;
}

int get_point(int x, int y, int **shape, int width, int height) {
  return x >= 0 && x < width && y >= 0 && y < height ? shape[y][x] : -1;
}

void set_point(int x, int y, int value, int **shape, int width, int height) {
  if (x >= 0 && x < width && y >= 0 && y < height) {
    shape[y][x] = value;
  }
}

int check_line(int **array, int x, int y, int length, Direction direction,
               int value, int width, int height) {
  int horizontal_offset = get_direction_horizontal_offset(direction);
  int vertical_offset = get_direction_vertical_offset(direction);

  for (int i = 0; i < length; i++) {
    if (get_point(x + horizontal_offset * i, y + vertical_offset * i, array,
                  width, height) != value) {
      return 0;
    }
  }

  return 1;
}

void set_line(int x, int y, int length, Direction direction, int value,
              int **array, int width, int height) {
  int horizontal_offset = get_direction_horizontal_offset(direction);
  int vertical_offset = get_direction_vertical_offset(direction);

  for (int i = 0; i < length; i++) {
    set_point(x + horizontal_offset * i, y + vertical_offset * i, value, array,
              width, height);
  }
}

int **copy_array(int **array, int width, int height) {
  int **copy = malloc(sizeof(int *) * height);

  for (int i = 0; i < height; i++) {
    copy[i] = malloc(sizeof(int) * width);
    memcpy(copy[i], array[i], sizeof(int) * width);
  }

  return copy;
}

void free_array(int **array, int height) {
  for (int y = 0; y < height; y++) {
    free(array[y]);
  }

  free(array);
}
