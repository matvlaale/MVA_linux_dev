CFLAGS=-O0 -Wall

SOURCES = maze1.c maze2.c maze3.c
EXECUTS = $(SOURCES:.c=)

all: maze patches $(EXECUTS)

maze: maze.c
	gcc $(CFLAGS) $^ -o $@

patches:
	patch -o maze1.c maze.c < m1.patch
	patch -o maze2.c maze.c < m2.patch
	patch -o maze3.c maze.c < m3.patch

maze1: maze1.c
	gcc $(CFLAGS) $^ -o $@
maze2: maze2.c
	gcc $(CFLAGS) $^ -o $@
maze3: maze3.c
	gcc $(CFLAGS) $^ -o $@

run:
	./maze
	./maze1 9
	./maze2 "*|" 9
	./maze3 1 ".\\" 9

clean:
	rm -f maze $(SOURCES) $(EXECUTS)
