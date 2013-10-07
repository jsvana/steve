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

#define RIGHT 3
#define UP 2
#define LEFT 1
#define DOWN 0

typedef struct {
  GLdouble x, y;
} Point;

typedef struct {
  GLfloat r, g, b;
	unsigned char walkable;
} TileColor;

typedef struct {
  Point points[4];
  int color;
} Tile;

typedef struct {
	TileColor colors[COLORS_PER_PALETTE];
	int id;
} Palette;

typedef struct {
	void *data;
	size_t elemSize;
	int top;
	int maxSize;
} Stack;

Stack *stackCreate(int size, size_t elemSize);
int stackSize(Stack *s);
void *stackData(Stack *s);
int stackPush(Stack *s, void *val);
void *stackPeek(Stack *s);
void *stackPop(Stack *s);
void stackDestroy(Stack *s);

#endif
