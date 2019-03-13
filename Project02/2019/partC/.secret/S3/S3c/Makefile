all: main

main: main.o hey.o hay.o

main.o: main.c  hay.h hey.h
	gcc -ansi -pedantic -Wall -c main.c

hay.o: hay.c hay.h
	gcc -ansi -pedantic -Wall -c hay.c 

hey.o: hey.c hey.h
	gcc -ansi -pedantic -Wall -c hey.c 

clean:
	rm -f main

