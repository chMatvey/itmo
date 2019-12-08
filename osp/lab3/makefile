all: a

a: main.o handler.o lock-queue.o message.o timer.o handlerTest.o lock-queueTest.o messageTest.o timerTest.o
	gcc -pthread -g -rdynamic -ggdb -O0 -Wall main.o handler.o lock-queue.o message.o timer.o handlerTest.o lock-queueTest.o messageTest.o timerTest.o -o a

main.o: main.c
	gcc -c main.c

handler.o: handler.c
	gcc -c handler.c

lock-queue.o: lock-queue.c
	gcc -c lock-queue.c

message.o: message.c
	gcc -c message.c

timer.o: timer.c
	gcc -c timer.c

handlerTest.o: test/handlerTest.c
	gcc -c test/handlerTest.c

lock-queueTest.o: test/lock-queueTest.c
	gcc -c test/lock-queueTest.c

messageTest.o: test/messageTest.c
	gcc -c test/messageTest.c

timerTest.o: test/timerTest.c
	gcc -c test/timerTest.c

clean:
	rm -rf *.o a
