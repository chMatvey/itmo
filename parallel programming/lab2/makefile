all: chgroup

chgroup: main.o
	g++ main.o -o chgroup

main.o: main.c
	g++ -c main.c

clean:
	rm -rf *.o chgroup

flags:
	gcc -Wall -Wextra -std=gnu99 -pedantic -Werror main.c