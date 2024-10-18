CFLAGS = -Wall
TEST_INPUT = input pop string of testing to test kols
TEST_REGEX = of test
TEST_SUBST = to no input

all: esub test

esub: esub.c
	cc $(CFLAGS) $^ -o $@

test: esub
	./esub "$(TEST_REGEX)" "$(TEST_SUBST)" "$(TEST_INPUT)" > output.txt
	echo "$(TEST_INPUT)" | sed -E 's/$(TEST_REGEX)/$(TEST_SUBST)/' > expected.txt
	cat *.txt
	diff output.txt expected.txt

clean:
	rm -f esub *.txt
