CC=clang
PROG=steve
OBJS=main.o char.o
CFLAGS=-g -ggdb $(shell pkg-config --cflags glfw3)
LDLIBS=$(shell pkg-config --static --libs glfw3)

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(LDLIBS) $(CFLAGS) $(OBJS)

clean:
	rm -f $(PROG) $(OBJS)
