CFLAGS = -Wall -Wextra -g

all: move protect.so

move: move.c
	$(CC) $(CFLAGS) -o $@ $^

protect.so: protect.c
	$(CC) $(CFLAGS) -fPIC -shared -ldl -o $@ $^

files:
	echo "Oh no, the original file\nmust be deleted!\n" > input.txt
	echo "Yes, the original file  \nmust be safe!\n" > PROTECTED.txt

test: move protect.so files
	bash ./test.sh

clean:
	rm -f move protect.so PROTECTED.txt input.txt output.txt
