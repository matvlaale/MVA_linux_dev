GENERATES = prog prog-a prog-so README
TRASH = *.o *~ o.* *.txt
LIBRARIES = *.a *.so

%.o:    %.c
	cc -fPIC $< -c -o $@

all:    README prog libs proges test

prog:   const.o fun.o prog.o
	cc $^ -o $@

README: prog
	./$< 2> $@
test:
	./prog > prog0.txt 2>&1
	./prog-a > proga0.txt 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > progso0.txt 2>&1
	./prog "first" > prog1.txt 2>&1
	./prog-a "first" > proga1.txt 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so "first" > progso1.txt 2>&1
	./prog "first" 2 "three" > prog3.txt 2>&1
	./prog-a "first" 2 "three" > proga3.txt 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so "first" 2 "three" > progso3.txt 2>&1
	@echo "\nThese should be identical:"
	-cmp prog1.txt proga1.txt
	-cmp prog1.txt progso1.txt
	
	-cmp prog3.txt proga3.txt
	-cmp prog3.txt progso3.txt
	
	-cmp prog0.txt proga0.txt
	-cmp prog0.txt progso0.txt

libs:
	ar -rcs liboutput_static.a fun.o const.o
	cc -shared fun.o const.o -o liboutput.so

proges: prog-a prog-so

prog-a:  prog.o
	cc -L. $^ -loutput_static -o $@

prog-so:  prog.o
	cc -L. $^ -loutput -o $@

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES) $(LIBRARIES)
