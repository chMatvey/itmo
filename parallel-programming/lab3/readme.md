#lab3

install CJson:

    git clone https://github.com/DaveGamble/cJSON
    
install protobuf: https://github.com/protocolbuffers/protobuf

build jar-file from https://github.com/chMatvey/itmo/tree/master/osp/random-number-generator

### build:

    make

### run with pipe:
   
    java -jar generator-jar-with-dependencies.jar -uniform 1 255 | ./a per_thread
    java -jar generator-jar-with-dependencies.jar -exponential 1 255 | ./a thread_pool 10
    
### test:

    java -jar generator-jar-with-dependencies.jar -uniform 1 255 | ./a test
    
### valgrind:

    java -jar generator-jar-with-dependencies.jar -uniform 1 25 | valgrind ./a per_thread
    java -jar generator-jar-with-dependencies.jar -uniform 1 25 | valgrind --leak-check=full --show-leak-kinds=all -v ./a per_thread

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