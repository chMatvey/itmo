all: a

a: main.o handler.o lock-queue.o message-manager.o timer.o file-manager.o handlerTest.o lock-queueTest.o messageTest.o timerTest.o read.o message.o
	g++ -pthread -lprotobuf -g -rdynamic -ggdb -O0 -Wall main.o handler.o lock-queue.o message-manager.o timer.o file-manager.o handlerTest.o lock-queueTest.o messageTest.o timerTest.o read.o message.o -o a

main.o: main.c
	gcc -c main.c

handler.o: handler.c
	gcc -c handler.c

lock-queue.o: lock-queue.c
	gcc -c lock-queue.c

message-manager.o: message-manager.c
	gcc -c message-manager.c

timer.o: timer.c
	gcc -c timer.c

file-manager.o: file-manager.c
	gcc -c file-manager.c

handlerTest.o: test/handlerTest.c
	gcc -c test/handlerTest.c

lock-queueTest.o: test/lock-queueTest.c
	gcc -c test/lock-queueTest.c

messageTest.o: test/messageTest.c
	gcc -c test/messageTest.c

timerTest.o: test/timerTest.c
	gcc -c test/timerTest.c

read.o: read.cpp
	g++ -c read.cpp -o read.o -lprotobuf

message.o: proto/message.pb.cc
	g++ -c proto/message.pb.cc -o message.o -lprotobuf

clean:
	rm -rf *.o a *.gcno *.gcda coverage report *.info

coverage-test:
	gcc -pthread --coverage main.c handler.c lock-queue.c message.c timer.c file-manager.c test/handlerTest.c test/lock-queueTest.c test/messageTest.c test/timerTest.c -o coverage

