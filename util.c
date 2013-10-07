#include "util.h"

#include <stdlib.h>
#include <string.h>

Stack *stackCreate(int size, size_t elemSize) {
	Stack *s = malloc(sizeof(Stack));
	if (s == NULL) {
		return NULL;
	}

	s->maxSize = size;
	s->top = -1;
	s->elemSize = elemSize;
	s->data = malloc(elemSize * size);
	if (s->data == NULL) {
		free(s);
		return NULL;
	}

	return s;
}

int stackSize(Stack *s) {
	if (s == NULL) {
		return -1;
	}

	return s->top + 1;
}

void *stackData(Stack *s) {
	if (s == NULL) {
		return NULL;
	}

	return s->data;
}

int stackPush(Stack *s, void *val) {
	if (s == NULL || stackSize(s) == s->maxSize) {
		return -1;
	}

	++s->top;
	memcpy(s->data + s->top * s->elemSize, val, s->elemSize);
	//*(uint8_t *)(s->data + s->top * s->elemSize) = *(uint8_t *)val;

	return stackSize(s);
}

void *stackPeek(Stack *s) {
	if (s == NULL || stackSize(s) == 0) {
		return NULL;
	}
	return s->data + s->top * s->elemSize;
}

void *stackPop(Stack *s) {
	if (s == NULL || stackSize(s) == 0) {
		return NULL;
	}

	void *val = stackPeek(s);

	--s->top;

	return val;
}

void stackDestroy(Stack *s) {
	if (s != NULL) {
		free(s->data);
		free(s);
	}
}
