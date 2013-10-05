#ifndef UTIL_H
#define UTIL_H

#include <GLFW/glfw3.h>

#define TILE_WIDTH 20
#define TILE_HEIGHT 20

#define PALETTE_COUNT 3
#define COLORS_PER_PALETTE 8

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef struct {
  GLdouble x, y;
} Point;

typedef struct {
  GLfloat r, g, b;
} Color;

typedef struct {
  Point points[4];
  int color;
} Tile;

typedef struct {
	Color colors[COLORS_PER_PALETTE];
	int id;
} Palette;

#endif
