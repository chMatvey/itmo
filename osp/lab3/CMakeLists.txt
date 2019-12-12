cmake_minimum_required(VERSION 3.15)
project(lab3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_C_FLAGS -pthread)

add_executable(lab3 main.c message.h message.c handler.h handler.c test/messageTest.c test/messageTest.h lock-queue.c lock-queue.h test/lock-queueTest.h test/lock-queue.c test/handlerTest.h test/handlerTest.c timer.h timer.c test/timerTest.h test/timerTest.c file-manager.h file-manager.c)