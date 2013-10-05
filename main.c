#include "util.h"
#include "char.h"

#include <GLFW/glfw3.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

GLFWwindow *window;

int screenWidth = 400; //default screen window width
int screenHeight = 400; //default screen window height

GLfloat paletteVals[PALETTE_COUNT][COLORS_PER_PALETTE][3] = {
	{
		{0.0f, 0.0f, 0.0f},
		{129.0f, 212.0f, 106.0f},
		{177.0f, 152.0f, 124.0f},
		{152.0f, 100.0f, 33.0f},
		{89.0f, 173.0f, 42.0f},
		{30.0f, 82.0f, 126.0f},
		{146.0f, 202.0f, 249.0f},
		{255.0f, 255.0f, 255.0f}
	},
	{
		{37.0f, 37.0f, 37.0f},
		{88.0f, 83.0f, 85.0f},
		{117.0f, 120.0f, 118.0f},
		{150.0f, 154.0f, 144.0f},
		{171.0f, 170.0f, 155.0f},
		{211.0f, 202.0f, 177.0f},
		{225.0f, 219.0f, 203.0f},
		{255.0f, 255.0f, 255.0f}
	},
	{
		{79.0f, 97.0f, 123.0f},
		{99.0f, 118.0f, 147.0f},
		{125.0f, 138.0f, 171.0f},
		{139.0f, 162.0f, 198.0f},
		{172.0f, 182.0f, 207.0f},
		{186.0f, 201.0f, 223.0f},
		{214.0f, 224.0f, 235.0f},
		{240.0f, 244.0f, 252.0f}
	}
};

Palette palettes[PALETTE_COUNT];
int currentPalette;

Tile **tiles;

Char *character;

char keys[UCHAR_MAX];

float speed = 0.1f;
unsigned int lastTime;

void setColor(Color *color, GLfloat r, GLfloat g, GLfloat b) {
	color->r = r / 255.0f;
	color->g = g / 255.0f;
	color->b = b / 255.0f;
}

void setPoint(Point *point, GLdouble x, GLdouble y) {
	point->x = x;
	point->y = y;
}

void printTile(Tile t) {
	Color c = palettes[currentPalette].colors[t.color];
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
	return t.tv_sec * 1000 + t.tv_usec;
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
		}
	}

	currentPalette = 1;

	tiles = malloc(sizeof(Tile *) * screenHeight / TILE_HEIGHT);

	for (i = 0; i < screenHeight / TILE_HEIGHT; i++) {
		tiles[i] = malloc(sizeof(Tile) * screenWidth / TILE_WIDTH);

		for (j = 0; j < screenWidth / TILE_WIDTH; j++) {
			setPoint(&(tiles[i][j].points[0]), j * TILE_WIDTH, i * TILE_HEIGHT);
			setPoint(&(tiles[i][j].points[1]), (j + 1) * TILE_WIDTH, i * TILE_HEIGHT);
			setPoint(&(tiles[i][j].points[2]), (j + 1) * TILE_WIDTH,
				(i + 1) * TILE_HEIGHT);
			setPoint(&(tiles[i][j].points[3]), j * TILE_WIDTH, (i + 1) * TILE_HEIGHT);
			tiles[i][j].color = rand() % COLORS_PER_PALETTE;
		}
	}

	character = createChar();

	memset(keys, 0, UCHAR_MAX);

	lastTime = getTime();
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
	Color c;
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

void key(GLFWwindow *window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		currentPalette = (currentPalette + 1) % PALETTE_COUNT;
	} else if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		exit(0);
	}
}

void update(unsigned int delta) {
	float dX = 0, dY = 0;

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		dX = -speed * (float)delta;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		dX = speed * (float)delta;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		dY = -speed * (float)delta;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		dY = speed * (float)delta;
	}

	if (dX != 0.0f || dY != 0.0f) {
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

  init();

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key);

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
