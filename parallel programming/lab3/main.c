#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <pthread.h>
#include "handler.h"
#include "lock-queue.h"
#include <execinfo.h>
#include <unistd.h>
#include <signal.h>

//#include "test/messageTest.h"
//#include "test/lock-queueTest.h"
//#include "test/handlerTest.h"

char *readFromFile(char *filename) {
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);
    free(f);

    string[fsize] = 0;

    return string;
}

void handler(int sig) {
    void *array[10];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 10);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    _exit(1);
}

int main() {
//    messageTest();
//    lockQueueTest();
//    handlerTest();
    signal(SIGSEGV, handler);

    lockQueue = createLockQueue();

    pthread_t reader_tid; /* идентификатор потока */
    pthread_attr_t reader_attr; /* отрибуты потока */

    pthread_t writer_tid; /* идентификатор потока */
    pthread_attr_t writer_attr; /* отрибуты потока */

    /* получаем дефолтные значения атрибутов */
    pthread_attr_init(&reader_attr);
    pthread_attr_init(&writer_attr);

    /* создаем новый поток */
    pthread_create(&reader_tid, &reader_attr, reader_thread, (void *) PER_THREAD);
    pthread_create(&writer_tid, &writer_attr, writer_thread, NULL);

    /* ждем завершения исполнения потока */
    pthread_join(reader_tid, NULL);
    pthread_join(writer_tid, NULL);

    destroyQueue(lockQueue);
}