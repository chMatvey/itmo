cmake_minimum_required(VERSION 3.10.2)
project(lab2 C)

set(CMAKE_C_STANDARD 99)
#set(THREADS_PREFER_PTHREAD_FLAG ON)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(lab2 main.c parser.h)