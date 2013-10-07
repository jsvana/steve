#include "conway.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALIVE 1
#define DEAD 0
#define CELL(i, j, w) (field[(i)*(w)+(j)])
#define KILL(i, j, w) (field[(i)*(w)+(j)]) = DEAD
#define VIVIFY(i, j, w) (field[(i)*(w)+(j)]) = ALIVE

static int countAlive(const char *field, int i, int j, int w, int h) {
	int x, y, alive = 0;
	for (x = i - 1; x <= i + 1; x++) {
		for (y = j - 1; y <= j + 1; y++) {
			if (x == i && y == j) {
				continue;
			}
			if (y < h && x < w && x >= 0 && y >= 0) {
				alive += CELL(i, j, w);
			}
		}
	}
	return alive;
}

static void evolve(char *field, int w, int h) {
	int i, j, alive, cell;

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			alive = countAlive(field, i, j, w, h);
			cell = CELL(i, j, w);

			if (cell == ALIVE) {
				if (alive > 3 || alive < 2) {
					KILL(i, j, w);
				} else {
					VIVIFY(i, j, w);
				}
			} else {
				if (alive == 3) {
					VIVIFY(i, j, w);
				} else {
					KILL(i, j, w);
				}
			}
		}
	}
}

void print(const char *field, int w, int h) {
	int i, j;
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			printf("%c", CELL(i, j, w) == 1 ? 'X' : ' ');
		}
		printf("\n");
	}
}

char *genField(int w, int h) {
	int i, j;
	char *field = malloc(sizeof(char) * w * h);

	srand(time(NULL));

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			field[i * w + j] = rand() % 2;
		}
	}

	print(field, w, h);
	for (i = 0; i < 2; i++) {
		evolve(field, w, h);
		print(field, w, h);
	}

	return field;
}
