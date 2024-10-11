CFLAGS = -O0 -g

all: range

range: range.c
	cc $(CFLAGS) $^ -o $@

test: range
	gdb --batch --quiet -x range1.gdb | grep "@@@" > test_output1.txt
	gdb --batch --quiet -x range2.gdb | grep "@@@" > test_output2.txt
	diff test_output1.txt test_expected1.txt
	diff test_output2.txt test_expected2.txt

clean:
	rm -f range test_output?.txt
