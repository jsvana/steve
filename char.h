#ifndef CHAR_H
#define CHAR_H

#include "util.h"

#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

typedef struct {
	Tile *data;
	Point position;
	int dir;
	int palette;
} Char;

Char *createChar();

void renderChar(Char *character, Palette *p);
void moveChar(Char *c, float x, float y);

void freeChar(Char *c);

#endif
