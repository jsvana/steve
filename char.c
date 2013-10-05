#include "char.h"

#define CHAR_TILE_WIDTH 5
#define CHAR_TILE_HEIGHT 5

#define SPRITE_TILE_COUNT 162

int sprite[SPRITE_TILE_COUNT][3] = {
	{4, 0, 1},
	{5, 0, 1},
	{6, 0, 1},
	{7, 0, 1},
	{8, 0, 1},
	{9, 0, 1},
	{3, 1, 1},
	{4, 1, 1},
	{5, 1, 1},
	{6, 1, 1},
	{7, 1, 1},
	{8, 1, 1},
	{9, 1, 1},
	{10, 1, 1},
	{1, 2, 2},
	{3, 2, 1},
	{4, 2, 3},
	{5, 2, 3},
	{6, 2, 3},
	{7, 2, 3},
	{8, 2, 3},
	{9, 2, 3},
	{10, 2, 1},
	{12, 2, 2},
	{1, 3, 2},
	{3, 3, 3},
	{4, 3, 3},
	{5, 3, 3},
	{6, 3, 3},
	{7, 3, 3},
	{8, 3, 3},
	{9, 3, 3},
	{10, 3, 3},
	{12, 3, 2},
	{1, 4, 2},
	{2, 4, 2},
	{3, 4, 3},
	{4, 4, 2},
	{5, 4, 1},
	{6, 4, 2},
	{7, 4, 2},
	{8, 4, 1},
	{9, 4, 2},
	{10, 4, 3},
	{11, 4, 2},
	{12, 4, 2},
	{1, 5, 2},
	{2, 5, 2},
	{3, 5, 3},
	{4, 5, 2},
	{5, 5, 3},
	{6, 5, 2},
	{7, 5, 2},
	{8, 5, 3},
	{9, 5, 2},
	{10, 5, 3},
	{11, 5, 2},
	{12, 5, 2},
	{2, 6, 2},
	{3, 6, 2},
	{4, 6, 2},
	{5, 6, 2},
	{6, 6, 2},
	{7, 6, 2},
	{8, 6, 2},
	{9, 6, 2},
	{10, 6, 2},
	{11, 6, 2},
	{12, 6, 3},
	{3, 7, 1},
	{4, 7, 2},
	{5, 7, 2},
	{6, 7, 3},
	{7, 7, 3},
	{8, 7, 2},
	{9, 7, 2},
	{10, 7, 1},
	{11, 7, 3},
	{12, 7, 3},
	{1, 8, 3},
	{2, 8, 3},
	{3, 8, 3},
	{4, 8, 3},
	{5, 8, 3},
	{6, 8, 2},
	{7, 8, 2},
	{8, 8, 2},
	{9, 8, 1},
	{10, 8, 1},
	{11, 8, 1},
	{12, 8, 2},
	{0, 9, 3},
	{1, 9, 3},
	{2, 9, 2},
	{3, 9, 3},
	{4, 9, 3},
	{5, 9, 3},
	{6, 9, 3},
	{7, 9, 1},
	{8, 9, 1},
	{9, 9, 1},
	{10, 9, 1},
	{11, 9, 1},
	{12, 9, 2},
	{0, 10, 3},
	{1, 10, 2},
	{2, 10, 2},
	{3, 10, 2},
	{4, 10, 3},
	{5, 10, 3},
	{6, 10, 2},
	{7, 10, 3},
	{8, 10, 3},
	{9, 10, 1},
	{10, 10, 1},
	{11, 10, 3},
	{0, 11, 3},
	{1, 11, 3},
	{2, 11, 2},
	{3, 11, 3},
	{4, 11, 3},
	{5, 11, 3},
	{6, 11, 2},
	{7, 11, 1},
	{8, 11, 3},
	{9, 11, 3},
	{10, 11, 3},
	{11, 11, 1},
	{0, 12, 3},
	{1, 12, 3},
	{2, 12, 2},
	{3, 12, 3},
	{4, 12, 3},
	{5, 12, 3},
	{6, 12, 2},
	{7, 12, 3},
	{8, 12, 3},
	{9, 12, 1},
	{10, 12, 1},
	{11, 12, 1},
	{0, 13, 3},
	{1, 13, 3},
	{2, 13, 3},
	{3, 13, 3},
	{4, 13, 3},
	{5, 13, 3},
	{6, 13, 2},
	{7, 13, 1},
	{8, 13, 1},
	{9, 13, 1},
	{10, 13, 3},
	{1, 14, 2},
	{2, 14, 2},
	{3, 14, 2},
	{4, 14, 2},
	{5, 14, 2},
	{8, 14, 3},
	{9, 14, 3},
	{10, 14, 3},
	{8, 15, 3},
	{9, 15, 3},
	{10, 15, 3}
};

static void setTile(Char *character, int i) {
	character->data[i].points[0].x = sprite[i][0] * CHAR_TILE_WIDTH;
	character->data[i].points[0].y = sprite[i][1] * CHAR_TILE_HEIGHT;
	character->data[i].points[1].x = (sprite[i][0] + 1) * CHAR_TILE_WIDTH;
	character->data[i].points[1].y = sprite[i][1] * CHAR_TILE_HEIGHT;
	character->data[i].points[2].x = (sprite[i][0] + 1) * CHAR_TILE_WIDTH;
	character->data[i].points[2].y = (sprite[i][1] + 1) * CHAR_TILE_HEIGHT;
	character->data[i].points[3].x = sprite[i][0] * CHAR_TILE_WIDTH;
	character->data[i].points[3].y = (sprite[i][1] + 1) * CHAR_TILE_HEIGHT;
	character->data[i].color = sprite[i][2];
}

Char *createChar() {
	int i;
	Char *c = malloc(sizeof(Char));

	c->position.x = 10.0f;
	c->position.y = 10.0f;

	c->data = malloc(sizeof(Tile) * SPRITE_TILE_COUNT);

	for (i = 0; i < SPRITE_TILE_COUNT; i++) {
		setTile(c, i);
	}

	return c;
}

void renderChar(Char *character, Palette *palettes) {
	int i;
	Color c;
	Palette p = palettes[character->palette];
	Tile t;

	glPushMatrix();
	glTranslatef(character->position.x, character->position.y, 0.0f);

	glBegin(GL_QUADS);
	for (i = 0; i < SPRITE_TILE_COUNT; i++) {
		t = character->data[i];
		c = p.colors[t.color];
		glColor3f(c.r, c.g, c.b);
		glVertex2f(t.points[0].x, t.points[0].y);
		glVertex2f(t.points[1].x, t.points[1].y);
		glVertex2f(t.points[2].x, t.points[2].y);
		glVertex2f(t.points[3].x, t.points[3].y);
	}
	glEnd();

	glPopMatrix();
}

void moveChar(Char *c, float x, float y) {
	c->position.x += 5 * x;
	c->position.y += 5 * y;
}

void freeChar(Char *c) {
	free(c->data);
	free(c);
}
