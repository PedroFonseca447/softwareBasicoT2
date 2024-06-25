all: tool

tool: main.o mymemory.o mymemory.a
		gcc -o tool main.o mymemory.o 	-L.


mymemory.a: main.o
	ar rcs mymemory.a mymemory.o


main.o: main.c mymemory.h
	gcc -c mymemory.c

mymemory.o: mymemory.c mymemory.o
	gcc -c mymemory.c


clean:
	rm -f	*.o	tool	*.a