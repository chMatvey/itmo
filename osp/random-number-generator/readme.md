#Random number generator

Build jar:
    
    mvn assembly
    
Build C:

    gcc main.c -o a
    
Windows:
    
    java -jar target/generator-jar-with-dependencies.jar | a.exe
    
Linux:

    java -jar target/generator-jar-with-dependencies.jar | ./a