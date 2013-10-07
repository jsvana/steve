#include "util.h"

#include <stdio.h>

int main() {
	int val, passed = TRUE;
	Stack *s = stackCreate(5, sizeof(int));

	val = stackSize(s);
	if (val != 0) {
		printf("[sizeStack] expected 0, got %d\n", val);
		passed = FALSE;
	} else {
		printf("[sizeStack] size correct\n");
	}

	val = 7;
	val = stackPush(s, &val);
	if (val != 1) {
		printf("[pushStack] expected 1, got %d\n", val);
		passed = FALSE;
	} else {
		printf("[pushStack] val correct\n");
	}

	val = *(int *)stackPeek(s);
	if (val != 7) {
		printf("[peekStack] expected 7, got %d\n", val);
		passed = FALSE;
	} else {
		printf("[peekStack] val correct\n");
	}

	val = stackSize(s);
	if (val != 1) {
		printf("[sizeStack] expected 1, got %d\n", val);
		passed = FALSE;
	} else {
		printf("[sizeStack] size correct\n");
	}

	val = *(int *)stackPop(s);
	if (val != 7) {
		printf("[popStack] expected 7, got %d\n", val);
		passed = FALSE;
	} else {
		printf("[popStack] val correct\n");
	}

	val = stackSize(s);
	if (val != 0) {
		printf("[sizeStack] expected 0, got %d\n", val);
		passed = FALSE;
	} else {
		printf("[sizeStack] size correct\n");
	}

	val = 8;
	stackPush(s, &val);
	val = 9;
	stackPush(s, &val);

	int *data = (int *)stackData(s);
	int contains = FALSE;
	for (int i = 0; i < stackSize(s) && !contains; i++) {
		if (data[i] == 9) {
			contains = TRUE;
		}
	}
	printf("contains: %s\n", contains ? "yes" : "no");

	val = *(int *)stackPeek(s);
	if (val != 9) {
		printf("[peekStack] expected 9, got %d\n", val);
		passed = FALSE;
	} else {
		printf("[peekStack] val correct\n");
	}

	val = *(int *)stackPop(s);
	if (val != 9) {
		printf("[popStack] expected 9, got %d\n", val);
		passed = FALSE;
	} else {
		printf("[popStack] val correct\n");
	}

	val = stackSize(s);
	if (val != 1) {
		printf("[sizeStack] expected 1, got %d\n", val);
		passed = FALSE;
	} else {
		printf("[sizeStack] size correct\n");
	}

	val = *(int *)stackPeek(s);
	if (val != 8) {
		printf("[peekStack] expected 8, got %d\n", val);
		passed = FALSE;
	} else {
		printf("[peekStack] val correct\n");
	}

	if (passed) {
		printf("A-OK\n");
	} else {
		printf("Some tests failed\n");
	}

	stackDestroy(s);

	return 0;
}
