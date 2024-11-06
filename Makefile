all: tool

tool: main.o mymemory.o
	gcc -o tool main.o mymemory.o -L.

mymemory.a: mymemory.o
	ar rcs mymemory.a mymemory.o

main.o: main.c mymemory.h
	gcc -c main.c

mymemory.o: mymemory.c mymemory.h
	gcc -c mymemory.c

clean:
	rm -f *.o tool *.a
