#include "util.h"
#include "char.h"
#include "conway.h"

#include <GLFW/glfw3.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define TILE(t, x, y) ((t)[(y)][(x)])
#define COLOR(p, t, i, j) ((p).colors[TILE(t, i, j).color])

GLFWwindow *window;

int screenWidth = 400; //default screen window width
int screenHeight = 400; //default screen window height

GLfloat paletteVals[PALETTE_COUNT][COLORS_PER_PALETTE][4] = {
	{
		{0.0f, 0.0f, 0.0f, FALSE},
		{152.0f, 100.0f, 33.0f, TRUE},
		{89.0f, 173.0f, 42.0f, TRUE},
		{177.0f, 152.0f, 124.0f, TRUE},
		{129.0f, 212.0f, 106.0f, TRUE},
		{30.0f, 82.0f, 126.0f, FALSE},
		{146.0f, 202.0f, 249.0f, FALSE},
		{255.0f, 255.0f, 255.0f, FALSE}
	},
	{
		{37.0f, 37.0f, 37.0f, TRUE},
		{88.0f, 83.0f, 85.0f, TRUE},
		{117.0f, 120.0f, 118.0f, TRUE},
		{150.0f, 154.0f, 144.0f, TRUE},
		{171.0f, 170.0f, 155.0f, TRUE},
		{211.0f, 202.0f, 177.0f, TRUE},
		{225.0f, 219.0f, 203.0f, TRUE},
		{255.0f, 255.0f, 255.0f, TRUE}
	},
	{
		{79.0f, 97.0f, 123.0f, TRUE},
		{99.0f, 118.0f, 147.0f, TRUE},
		{125.0f, 138.0f, 171.0f, TRUE},
		{139.0f, 162.0f, 198.0f, TRUE},
		{172.0f, 182.0f, 207.0f, TRUE},
		{186.0f, 201.0f, 223.0f, TRUE},
		{214.0f, 224.0f, 235.0f, TRUE},
		{240.0f, 244.0f, 252.0f, TRUE}
	}
};

int map[20][20] = {
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 5, 5, 6, 2, 2, 2, 2, 2, 2},
};

Palette palettes[PALETTE_COUNT];
int currentPalette;

Tile **tiles;

Char *character;

float speed = 0.0001f;

//Stack *keyStack;

void setColor(TileColor *color, GLfloat r, GLfloat g, GLfloat b) {
	color->r = r / 255.0f;
	color->g = g / 255.0f;
	color->b = b / 255.0f;
}

void setPoint(Point *point, GLdouble x, GLdouble y) {
	point->x = x;
	point->y = y;
}

void printTile(Tile t) {
	TileColor c = palettes[currentPalette].colors[t.color];
	printf("p: (%f, %f), (%f, %f), (%f, %f), (%f, %f), c: %d, (%f, %f, %f)\n",
		t.points[0].x, t.points[0].y,
		t.points[1].x, t.points[1].y,
		t.points[2].x, t.points[2].y,
		t.points[3].x, t.points[3].y,
		t.color, c.r, c.g, c.b
	);
}

unsigned int getTime() {
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000000 + t.tv_usec;
}

void init() {
	int i, j;

  glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, screenWidth, screenHeight, 0.0f, -1.0f, 1.0f);

	for (i = 0; i < PALETTE_COUNT; i++) {
		for (j = 0; j < COLORS_PER_PALETTE; j++) {
			setColor(&(palettes[i].colors[j]), paletteVals[i][j][0],
				paletteVals[i][j][1], paletteVals[i][j][2]);
			palettes[i].colors[j].walkable = paletteVals[i][j][3];
		}
	}

	currentPalette = 0;

	tiles = malloc(sizeof(Tile *) * screenHeight / TILE_HEIGHT);

	for (i = 0; i < screenHeight / TILE_HEIGHT; i++) {
		tiles[i] = malloc(sizeof(Tile) * screenWidth / TILE_WIDTH);

		for (j = 0; j < screenWidth / TILE_WIDTH; j++) {
			setPoint(&(tiles[i][j].points[0]), j * TILE_WIDTH, i * TILE_HEIGHT);
			setPoint(&(tiles[i][j].points[1]), (j + 1) * TILE_WIDTH, i * TILE_HEIGHT);
			setPoint(&(tiles[i][j].points[2]), (j + 1) * TILE_WIDTH,
				(i + 1) * TILE_HEIGHT);
			setPoint(&(tiles[i][j].points[3]), j * TILE_WIDTH, (i + 1) * TILE_HEIGHT);
			//tiles[i][j].color = rand() % COLORS_PER_PALETTE;
			tiles[i][j].color = map[i][j];
		}
	}

	character = createChar();
	//keyStack = stackCreate(4, sizeof(int));
}

void cleanup() {
	int i;

	for (i = 0; i < screenHeight / TILE_HEIGHT; i++) {
		free(tiles[i]);
	}

	free(tiles);

	freeChar(character);
}

void render() {
	int i, j;
	TileColor c;
	Tile t;

  glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);
	for (i = 0; i < screenHeight / TILE_HEIGHT; i++) {
		for (j = 0; j < screenWidth / TILE_WIDTH; j++) {
			t = tiles[i][j];
			c = palettes[currentPalette].colors[t.color];
			glColor3f(c.r, c.g, c.b);
			glVertex2f(t.points[0].x, t.points[0].y);
			glVertex2f(t.points[1].x, t.points[1].y);
			glVertex2f(t.points[2].x, t.points[2].y);
			glVertex2f(t.points[3].x, t.points[3].y);
		}
	}
	glEnd();

	renderChar(character, palettes);

	glFinish();

	glfwSwapBuffers(window);
}

/*
int keyStackFind(int val) {
	int *data = (int *)stackData(keyStack);
	int i, index = -1;
	for (i = 0; i < stackSize(keyStack) && index != -1; i++) {
		if (data[i] == val) {
			index = i;
		}
	}
	return index;
}

int keyStackContains(int val) {
	return keyStackFind(val) != -1;
}

int keyStackRemove(int val) {
	int *data = (int *)stackData(keyStack);
	int i, index = keyStackFind(val);
	if (index != -1) {
		for (i = index; i < stackSize(keyStack) - 1; i++) {
			data[i] = data[i + 1];
		}
		stackPop(keyStack);

		return val;
	} else {
		return -1;
	}
}
*/

void key(GLFWwindow *window, int key, int scancode, int action, int mode) {
	int dir;
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		currentPalette = (currentPalette + 1) % PALETTE_COUNT;
	} else if (key == GLFW_KEY_O && action == GLFW_PRESS) {
		character->palette = (character->palette + 1) % PALETTE_COUNT;
	} else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		character->dir = LEFT;
	} else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		character->dir = RIGHT;
	} else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		character->dir = UP;
	} else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		character->dir = DOWN;
	} else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		exit(0);
	}
}

void charPosition(Char *c, Point *p) {
	p->x = floor(c->position.x / TILE_WIDTH);
	p->y = floor(c->position.y / TILE_HEIGHT);
}

int walkable(int x, int y) {
	if (x < 0 || y < 0 || x >= screenWidth / TILE_WIDTH
			|| y >= screenHeight / TILE_HEIGHT) {
		return FALSE;
	} else {
		return COLOR(palettes[currentPalette], tiles, x, y).walkable;
	}
}

void update(unsigned int delta) {
	float dX = 0, dY = 0;
	Point p;

	charPosition(character, &p);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		if (walkable(p.x - 1, p.y)) {
			dX -= speed * delta;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		if (walkable(p.x + 1, p.y)) {
			dX += speed * delta;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (walkable(p.x, p.y - 1)) {
			dY -= speed * delta;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (walkable(p.x, p.y + 1)) {
			dY += speed * delta;
		}
	}

	if (dX != 0 || dY != 0) {
		moveChar(character, dX, dY);
	}
}

int main(int argc, char** argv) {
	if (!glfwInit()) {
		exit(1);
	}

	window = glfwCreateWindow(screenWidth, screenHeight, "steve", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key);

  init();

	unsigned int lastTime = getTime(), time;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		time = getTime();
		update(time - lastTime);
		lastTime = time;

		render();
	}

	cleanup();

	glfwDestroyWindow(window);

	glfwTerminate();

  return 0;
}
