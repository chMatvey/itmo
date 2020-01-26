cmake_minimum_required(VERSION 3.15)
project(lab3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_C_FLAGS -pthread)
set(CMAKE_C_FLAGS --coverage)
set(CMAKE_CXX_FLAGS --coverage)

INCLUDE(FindProtobuf)
FIND_PACKAGE(Protobuf REQUIRED)
INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER proto/message.proto)
ADD_LIBRARY(proto3 ${PROTO_HEADER} ${PROTO_SRC})
TARGET_LINK_LIBRARIES(proto3)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(
        lab3 main.c
        message-manager.h
        message-manager.c
        handler.h
        handler.c
        test/messageTest.c
        test/messageTest.h
        lock-queue.c
        lock-queue.h
        test/lock-queueTest.h
        test/lock-queueTest.c
        test/handlerTest.h
        test/handlerTest.c
        timer.h
        timer.c
        test/timerTest.h
        test/timerTest.c
        file-manager.h
        file-manager.c
        client-handler.cpp
        client-handler.h
        mongoose.c
        mongoose.h queue.h flags.h flags.cpp)

target_link_libraries(lab3 proto3 ${PROTOBUF_LIBRARY})
target_link_libraries(lab3 ${PTHREAD_LIBRARY})