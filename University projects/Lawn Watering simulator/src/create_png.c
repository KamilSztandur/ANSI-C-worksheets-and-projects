#include <png.h>
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>

#include "tab.h"

/* Funkcja glowna modulu tworzacego plik png */
int make_png(int **tab, int height, int width, int count, char *filename,
             double spr_average, double spr_deviation) {
  bitmap_t picture;
  picture.height = height;
  picture.width = width;
  picture.pixels = calloc(picture.width * picture.height, sizeof(pixel_t));

  if (!picture.pixels)
    return -1;

  int min_range, max_range, avg;
  if (spr_average < spr_deviation) {
    min_range = 0;
  } else
    min_range = spr_average - spr_deviation;

  max_range = (int)spr_average + (int)spr_deviation;

  for (int i = 0; i < picture.height; i++) {
    for (int j = 0; j < picture.width; j++) {
      pixel_t *pixel = pixel_at(&picture, i, j);

      if (tab[i][j] == -1) {
        pixel->red = 0;
        pixel->green = 0;
        pixel->blue = 0;
      } else if (tab[i][j] == 0) {
        pixel->red = 255;
        pixel->green = 255;
        pixel->blue = 255;
      } else if (tab[i][j] > max_range) {
        pixel->red = 220;
        pixel->green = 30;
        pixel->blue = 30;
      } else if (tab[i][j] > (int)spr_average) {
        pixel->red = 0;
        pixel->green = 60 + (int)(180 * (max_range - tab[i][j]) /
                                  (max_range - spr_average));
        pixel->blue = 0;
      } else if (tab[i][j] > (int)min_range) {
        pixel->red =
            (int)(180 * (spr_average - tab[i][j]) / (spr_average - min_range));
        pixel->green = 255;
        pixel->blue =
            (int)(180 * (spr_average - tab[i][j]) / (spr_average - min_range));
      } else {
        pixel->red = 185;
        pixel->green = 140;
        pixel->blue = 30;
      }
    }
  }

  if (save_png_to_file(&picture, filename))
    fprintf(stderr, "Error writing file.\n");

  free(picture.pixels);
  return 0;
}

static pixel_t *pixel_at(bitmap_t *bitmap, int r, int c) {
  return bitmap->pixels + bitmap->width * r + c;
}

static int save_png_to_file(bitmap_t *bitmap, const char *path) {
  FILE *fp;
  png_structp png_ptr = NULL;
  png_infop info_ptr = NULL;

  size_t x, y;
  png_byte **row_pointers = NULL;

  /* "status" contains the return value of this function. At first
         it is set to a value which means 'failure'. When the routine
         has finished its work, it is set to a value which means
         'success'. */
  int status = -1;

  /* The following number is set by trial and error only. I cannot
        see where it it is documented in the libpng manual.
      */
  int pixel_size = 3;
  int depth = 8;

  fp = fopen(path, "wb");

  if (!fp)
    goto fopen_failed;

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (png_ptr == NULL)
    goto png_create_write_struct_failed;

  info_ptr = png_create_info_struct(png_ptr);
  if (info_ptr == NULL)
    goto png_create_info_struct_failed;

  /* Set up error handling. */
  if (setjmp(png_jmpbuf(png_ptr)))
    goto png_failure;

  /* Set image attributes. */
  png_set_IHDR(png_ptr, info_ptr, bitmap->width, bitmap->height, depth,
               PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

  /* Initialize rows of PNG. */
  row_pointers = png_malloc(png_ptr, bitmap->height * sizeof(png_byte *));

  for (y = 0; y < bitmap->height; y++) {
    png_byte *row =
        png_malloc(png_ptr, sizeof(uint8_t) * bitmap->width * pixel_size);
    row_pointers[y] = row;

    for (x = 0; x < bitmap->width; x++) {
      pixel_t *pixel = pixel_at(bitmap, y, x);
      *row++ = pixel->red;
      *row++ = pixel->green;
      *row++ = pixel->blue;
    }
  }

  /* Write the image data to "fp". */
  png_init_io(png_ptr, fp);
  png_set_rows(png_ptr, info_ptr, row_pointers);
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  /* The routine has successfully written the file, so we set
         "status" to a value which indicates success. */
  status = 0;

  for (y = 0; y < bitmap->height; y++)
    png_free(png_ptr, row_pointers[y]);

  png_free(png_ptr, row_pointers);

png_failure:
png_create_info_struct_failed:
  png_destroy_write_struct(&png_ptr, &info_ptr);
png_create_write_struct_failed:
  fclose(fp);
fopen_failed:
  return status;
}
