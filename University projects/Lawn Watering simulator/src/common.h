#ifndef _COMMON_H
#define _COMMON_H

/* Array dimmensions */
#define INPUT_WIDTH 80
#define INPUT_HEIGHT 40
#define WIDTH 8000
#define HEIGHT 4000

/* Sprinkler watering radiuses */
#define FULL_RADIUS 200
#define THREE_QUARTERS_RADIUS 300
#define HALF_RADIUS 400
#define QUARTER_RADIUS 500

#define FULL_CYCLE 1
#define HALF_AND_QUARTER_CYCLE 4 / 3
#define HALF_CYCLE 2
#define QUARTER_CYCLE 4

typedef enum {
  FULL = 1,
  THREE_QUARTERS = 2,
  HALF = 3,
  QUARTER = 4
} SprinklerType;

typedef enum {
  LEFT,
  TOP,
  RIGHT,
  BOTTOM,
} Direction;

int get_direction_horizontal_offset(Direction direction);

int get_direction_vertical_offset(Direction direction);

int get_edge_horizontal_offest(Direction direction, int external);

int get_edge_vertical_offest(Direction direction, int external);

int get_point(int x, int y, int **shape, int width, int height);

void set_point(int x, int y, int value, int **shape, int width, int height);

int check_line(int **array, int x, int y, int length, Direction direction,
               int value, int width, int height);

void set_line(int x, int y, int length, Direction direction, int value,
              int **array, int width, int height);

int **copy_array(int **array, int width, int height);

void free_array(int **array, int height);

#endif