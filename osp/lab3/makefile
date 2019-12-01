all: a

a: main.o handler.o lock-queue.o message.o
	gcc -pthread -g -rdynamic -ggdb -O0 -Wall main.o handler.o lock-queue.o message.o -o a

main.o: main.c
	gcc -c main.c

handler.o: handler.c
	gcc -c handler.c

lock-queue.o: lock-queue.c
	gcc -c lock-queue.c

message.o: message.c
	gcc -c message.c

clean:
	rm -rf *.o a
