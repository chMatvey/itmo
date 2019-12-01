#lab3

    java -jar generator-jar-with-dependencies.jar -uniform 1 255 | ./a -pthread
    
    
valgrind:

    java -jar generator-jar-with-dependencies.jar -uniform 1 25 | valgrind ./a -pthread
    java -jar generator-jar-with-dependencies.jar -uniform 1 25 | valgrind --leak-check=full -v ./a -pthread 