CC=clang
PROG=steve
OBJS=main.o char.o conway.o util.o
CFLAGS=-ggdb $(shell pkg-config --cflags glfw3)
LDLIBS=$(shell pkg-config --static --libs glfw3)

TEST_PROG=test
TEST_OBJS=test.o util.o

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(LDLIBS) $(CFLAGS) $(OBJS)

$(TEST_PROG): $(TEST_OBJS)
	$(CC) -o $(TEST_PROG) $(LDLIBS) $(CFLAGS) $(TEST_OBJS)

clean:
	rm -f $(PROG) $(TEST_PROG) $(OBJS) $(TEST_OBJS)
