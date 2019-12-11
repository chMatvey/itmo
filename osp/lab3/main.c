#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <pthread.h>
#include "handler.h"
#include "lock-queueTest.h"
#include <execinfo.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include "timer.h"

#include "test/messageTest.h"
#include "test/lock-queueTest.h"
#include "test/handlerTest.h"
#include "test/timerTest.h"

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
    signal(SIGSEGV, handler);

    lockQueue = createLockQueue();
    readTimes = createTimeQueue();
    inQueueTimes = createTimeQueue();
    executionTimes = createTimeQueue();
    writeTimes = createTimeQueue();

//    messageTest();
//    lockQueueTest();
//    handlerTest();
//    timerTest();

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

    int readTimesFile = open("../read", O_WRONLY | O_CREAT, 00700);
    int inQueueFile = open("../queue", O_WRONLY | O_CREAT, 00700);
    int executionTimesFile = open("../execution", O_WRONLY | O_CREAT, 00700);
    int writeTimesFIle = open("../writte", O_WRONLY | O_CREAT, 00700);

    printTimesToFile(*readTimes, readTimesFile);
    printTimesToFile(*inQueueTimes, inQueueFile);
    printTimesToFile(*executionTimes, executionTimesFile);
    printTimesToFile(*writeTimes, writeTimesFIle);

    close(readTimesFile);
    close(inQueueFile);
    close(executionTimesFile);
    close(writeTimesFIle);

    destroyQueue(lockQueue);
    destroyTimeQueue(readTimes);
    destroyTimeQueue(inQueueTimes);
    destroyTimeQueue(executionTimes);
    destroyTimeQueue(writeTimes);
}