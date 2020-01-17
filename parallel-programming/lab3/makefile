all: a

a: main.o handler.o lock-queue.o message-manager.o timer.o file-manager.o client-handler.o message.o flags.o handlerTest.o lock-queueTest.o messageTest.o timerTest.o
	g++ -o main.o handler.o lock-queue.o message-manager.o timer.o file-manager.o client-handler.o message.o flags.o handlerTest.o lock-queueTest.o messageTest.o timerTest.o -Wall -Wextra -std=gnu99 -pedantic -Werror -pthread -lprotobuf -coverage -fprofile-arcs -ftest-coverage -lgcov

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

client-handler.o: client-handler.cpp
	g++ -c client-handler.cpp -lprotobuf 
 
message.o: proto/message.pb.cc
	g++ -c proto/message.pb.cc -o message.o -lprotobuf 

flags.o: flags.cpp
	g++ -c flags.cpp

handlerTest.o: test/handlerTest.c
	gcc -c test/handlerTest.c

lock-queueTest.o: test/lock-queueTest.c
	gcc -c test/lock-queueTest.c

messageTest.o: test/messageTest.c
	gcc -c test/messageTest.c

timerTest.o: test/timerTest.c
	gcc -c test/timerTest.c

clean:
	rm -rf *.o a *.gcno *.gcda coverage report *.info

coverage-test:
	gcc -pthread --coverage main.c handler.c lock-queue.c message.c timer.c file-manager.c test/handlerTest.c test/lock-queueTest.c test/messageTest.c test/timerTest.c -o coverage

