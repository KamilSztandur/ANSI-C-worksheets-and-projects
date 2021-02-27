#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "tab.h"

int check_facing(int **array, int x, int y, Direction direction, int width,
                 int height) {
  int horizontal_offset = get_direction_horizontal_offset(direction) +
                          get_direction_horizontal_offset((direction + 1) % 4);
  int vertical_offset = get_direction_vertical_offset(direction) +
                        get_direction_vertical_offset((direction + 1) % 4);

  return get_point(x + horizontal_offset, y + vertical_offset, array, width,
                   height) == 0;
}

int check_edge_sprinkler(SprinklerType type, int **array, int x, int y,
                         Direction direction, int width, int height) {
  if (!check_facing(array, x, y, direction, width, height)) {
    return 0;
  }

  if (type == QUARTER &&
      check_line(array, x, y, 5, direction, 1, width, height) &&
      check_line(array, x, y, 5, (direction + 1) % 4, 1, width, height)) {
    set_line(x, y, 5, direction, 2, array, width, height);
    set_line(x, y, 5, (direction + 1) % 4, 2, array, width, height);
    return 1;
  } else if (type == HALF &&
             check_line(array, x, y, 4, direction, 1, width, height) &&
             check_line(array, x, y, 4 + 1, (direction + 2) % 4, 1, width,
                        height)) {
    set_line(x, y, 4, direction, 2, array, width, height);
    set_line(x, y, 4 + 1, (direction + 2) % 4, 2, array, width, height);
    return 1;
  } else if (type == THREE_QUARTERS &&
             check_line(array, x, y, 3, direction, 1, width, height) &&
             check_line(array, x, y, 3, (direction + 3) % 4, 1, width,
                        height)) {
    set_line(x, y, 3, direction, 2, array, width, height);
    set_line(x, y, 3, (direction + 3) % 4, 2, array, width, height);
    return 1;
  } else {
    return 0;
  }
}

int check_edge_point(int **shape, int x, int y) {
  if (get_point(x, y, shape, INPUT_WIDTH, INPUT_HEIGHT) != 0) {
    return 0;
  }

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (get_point(x + i, y + j, shape, INPUT_WIDTH, INPUT_HEIGHT) != 0 &&
          !(i == 0 && j == 0)) {
        return 1;
      }
    }
  }

  return 0;
}

int find_edges(int **shape, int **edges) {
  for (int x = 0; x < INPUT_WIDTH; x++) {
    for (int y = 0; y < INPUT_HEIGHT; y++) {
      if (check_edge_point(shape, x, y)) {
        edges[y][x] = 1;
      }
    }
  }
}

int get_sprinkler_radius(SprinklerType type) {
  switch (type) {
  case FULL:
    return FULL_RADIUS;
  case THREE_QUARTERS:
    return THREE_QUARTERS_RADIUS;
  case HALF:
    return HALF_RADIUS;
  case QUARTER:
    return QUARTER_RADIUS;
  }
}

int get_sprinkler_cycle(SprinklerType type) {
  switch (type) {
  case FULL:
    return FULL_CYCLE;
  case THREE_QUARTERS:
    return HALF_AND_QUARTER_CYCLE;
  case HALF:
    return HALF_CYCLE;
  case QUARTER:
    return QUARTER_CYCLE;
  }
}

void add_edge_sprinklers(SprinklerType type, int **shape, int **lawn,
                         int cycles, location *sprinkler_tab, int *spr_count,
                         int *spr_size) {
  int radius = get_sprinkler_radius(type);

  for (int x = 0; x < INPUT_WIDTH; x++) {
    for (int y = 0; y < INPUT_HEIGHT; y++) {
      for (int direction = LEFT; direction <= BOTTOM; direction++) {
        int horizontal_offset =
            get_edge_horizontal_offest(direction, type == THREE_QUARTERS);
        int vertical_offset =
            get_edge_vertical_offest(direction, type == THREE_QUARTERS);

        if (check_edge_sprinkler(type, shape, x, y, direction, INPUT_WIDTH,
                                 INPUT_HEIGHT)) {
          draw_circle(lawn, x * 100 + horizontal_offset * 99,
                      y * 100 + vertical_offset * 99, type, direction,
                      get_sprinkler_cycle(type) * cycles);
          set_new(sprinkler_tab, (x + horizontal_offset) * 100,
                  (y + vertical_offset) * 100, type, direction, spr_size,
                  spr_count);
        }
      }
    }
  }
}

void add_fulls(int **lawn, int cycles, location *sprinkler_tab, int *spr_count,
               int *spr_size) {
  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      if (lawn[y][x] == 0) {
        draw_circle(lawn, x, y, 1, 1, FULL_CYCLE * cycles);
        set_new(sprinkler_tab, x, y, 1, 1, spr_size, spr_count);
      }
    }
  }
}

void get_locations(int **shape, int **lawn, int cycles, location *sprinkler_tab,
                   int *spr_count, int *spr_size) {
  int **edges = copy_array(shape, INPUT_WIDTH, INPUT_HEIGHT);

  find_edges(shape, edges);

  make_png(edges, 40, 80, 1, "edges.png", 1, 1);

  add_edge_sprinklers(QUARTER, edges, lawn, cycles, sprinkler_tab, spr_count,
                      spr_size);
  add_edge_sprinklers(THREE_QUARTERS, edges, lawn, cycles, sprinkler_tab,
                      spr_count, spr_size);
  add_edge_sprinklers(HALF, edges, lawn, cycles, sprinkler_tab, spr_count,
                      spr_size);

  add_fulls(lawn, cycles, sprinkler_tab, spr_count, spr_size);

  free_array(edges, INPUT_HEIGHT);
}