#include <stdio.h>
#include <stdlib.h>

#include "tab.h"

void make_txt(location *sprinklers, int count, char *filename,
              double spr_average, double spr_deviation, int spr_count) {
  FILE *out = fopen(filename, "w");

  fprintf(out, "%d\t%lf\t%lf\n", spr_count, spr_average, spr_deviation);

  if (out) {
    for (int i = 0; i < count; i++) {
	fprintf(out, "Type: ");
	switch( sprinklers[i].type ) {
	    case 1:
		fprintf(out, "FULL\t\t");
		break;
	    case 2:
		fprintf(out, "THREE_QUARTERS\t");
		break;
            case 3:
		fprintf(out, "HALF\t\t");
		break;
	    case 4:
		fprintf(out, "QUARTER\t\t");
	}

	fprintf(out, "Direction: ");
	switch( sprinklers[i].direction ) {
            case TOP:
                fprintf(out, "TOP\t\t");
                break;
            case LEFT:
                fprintf(out, "LEFT\t\t"); 
                break;
            case RIGHT:
                fprintf(out, "RIGHT\t");
                break;
            case BOTTOM:
                fprintf(out, "BOTTOM\t");
        }
        fprintf(out, "Location: (%d, %d)\n",
              sprinklers[i].x, sprinklers[i].y);
    }
    fclose(out);
  } else
    printf("Wystapil blad podczas proby zapisu pliku.\n");
}
