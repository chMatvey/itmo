#lab3

install CJson:

    git clone https://github.com/DaveGamble/cJSON
    
install protobuf: https://github.com/protocolbuffers/protobuf

build jar-file from https://github.com/chMatvey/itmo/tree/master/osp/random-number-generator

### build:

    make
    
### run

    cmake-build-debug/lab3
    cmake-build-debug/lab3 per_thread
    cmake-build-debug/lab3 per_task
    cmake-build-debug/lab3 thread_pool 10
    
### test:

    cmake-build-debug/lab3 test
    
### valgrind:

    valgrind cmake-build-debug/lab3
    valgrind --leak-check=full --show-leak-kinds=all -v cmake-build-debug/lab3
    valgrind --leak-check=full --show-leak-kinds=all -v cmake-build-debug/lab3 per_thread
    valgrind --leak-check=full --show-leak-kinds=all -v cmake-build-debug/lab3 per_task
    valgrind --leak-check=full --show-leak-kinds=all -v cmake-build-debug/lab3 thread_pool 10

### test-coverage, install package:
    
    sudo apt install lcov
    
### test-coverage:

    make coverage-test
    ./coverage test
    lcov -t "coverage" -o coverage.info -c -d .
    genhtml -o report coverage.info
    
result - report/index.html

### protobuf

    protoc -I=. --java_out=../random-number-generator/src/main/java proto/message.proto
    protoc -I=. --cpp_out=proto proto/message.proto