#lab3
    
build:

    make

run:

    java -jar generator-jar-with-dependencies.jar -uniform 1 255 | ./a -pthread
    
    
valgrind:

    java -jar generator-jar-with-dependencies.jar -uniform 1 25 | valgrind ./a -pthread
    java -jar generator-jar-with-dependencies.jar -uniform 1 25 | valgrind --leak-check=full -v ./a -pthread 

test-coverage, install package:
    
    sudo apt install lcov
    
test-coverage:

    make coverage-test
    ./coverage
    lcov -t "coverage" -o coverage.info -c -d .
    genhtml -o report coverage.info
    
result - report/index.html