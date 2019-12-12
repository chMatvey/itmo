#lab3

install CJson:

    git clone https://github.com/DaveGamble/cJSON
    
install protobuf: https://github.com/protocolbuffers/protobuf
    
build:

    make

run:

    java -jar generator-jar-with-dependencies.jar -uniform 1 255 | ./a [stratgy-type | test]
    
valgrind:

    java -jar generator-jar-with-dependencies.jar -uniform 1 25 | valgrind ./a [stratgy-type | test]
    java -jar generator-jar-with-dependencies.jar -uniform 1 25 | valgrind --leak-check=full -v ./a [stratgy-type | test]

test-coverage, install package:
    
    sudo apt install lcov
    
test-coverage:

    make coverage-test
    ./coverage
    lcov -t "coverage" -o coverage.info -c -d .
    genhtml -o report coverage.info
    
result - report/index.html