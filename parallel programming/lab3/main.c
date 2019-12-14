#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "handler.h"
#include "lock-queue.h"
#include <execinfo.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <values.h>
#include "errno.h"
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

int main(int argc, char *argv[]) {
    signal(SIGSEGV, handler);

    if (argc < 2) {
        printf("Arguments must be: <strategy-type | test>\n");
        return EINVAL;
    }

    lockQueue = createLockQueue();
    readTimes = createTimeQueue();
    inQueueTimes = createTimeQueue();
    executionTimes = createTimeQueue();
    writeTimes = createTimeQueue();

    if (strcmp(argv[1], "test") == 0) {
        messageTest();
        lockQueueTest();
        handlerTest();
        timerTest();
    } else {
        ThreadParam *param = (ThreadParam *) malloc(sizeof(ThreadParam));
        param->data = 0;
        int isCorrectParam = 1;

        if (strcmp(argv[1], "per_thread") == 0) {
            param->strategyType = PER_THREAD;
        } else if (strcmp(argv[1], "per_task") == 0) {
            param->strategyType = PER_TASK;
        } else if (strcmp(argv[1], "thread_pool") == 0) {
            param->strategyType = THREAD_POOL;
            if (argc < 3) {
                printf("Thread_pool strategy must contain count-threads parameter\n");
                isCorrectParam = 0;
            } else {
                param->data = strtol(argv[2], NULL, 10);
                if (param->data <= 0 || param->data == LONG_MAX || param->data == LONG_MIN) {
                    printf("Count-threads parameter must be more than zero\n");
                    isCorrectParam = 0;
                }
            }
        } else {
            printf("Strategy-type must be: per_thread | per_task | thread_pool\n");
            isCorrectParam = 0;
        }

        if (isCorrectParam) {
            pthread_t reader_tid; /* идентификатор потока */
            pthread_attr_t reader_attr; /* отрибуты потока */

            pthread_t writer_tid; /* идентификатор потока */
            pthread_attr_t writer_attr; /* отрибуты потока */

            /* получаем дефолтные значения атрибутов */
            pthread_attr_init(&reader_attr);
            pthread_attr_init(&writer_attr);

            /* создаем новый поток */
            pthread_create(&reader_tid, &reader_attr, reader_thread, (void *) param);
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
        }

        free(param);
    }

    destroyQueue(lockQueue);
    destroyTimeQueue(readTimes);
    destroyTimeQueue(inQueueTimes);
    destroyTimeQueue(executionTimes);
    destroyTimeQueue(writeTimes);
}