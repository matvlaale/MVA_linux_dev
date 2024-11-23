.POSIX:
CFLAGS = -std=c99 -Wall -Wextra -O3 -g3
LIBNAME = libbuf.a

all: $(LIBNAME) tests

$(LIBNAME): buf.o
	ar rcs $@ buf.o

buf.o: tests.c buf.h
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ -c tests.c $(LDLIBS)

tests: tests.c
	$(CC) $(LDFLAGS) $(CFLAGS) $^ -o $@ $(LDLIBS)

test: check
check: tests
	./tests

bench: tests
	./tests 558d2750ae0e0887

clean:
	rm -f tests $(LIBNAME) buf.o
