//
// Created by matvey on 25.11.2019.
//

#include "handler.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <asm/errno.h>
#include <fcntl.h>
#include "message.h"
#include "timer.h"
#include <pthread.h>

const int buffer_size = 1024 * 1024;

void thread_strategy() {
    char *string = calloc(buffer_size, sizeof(char));
    int wasStopMsg = 0;

    while (!wasStopMsg) {
        struct timespec *start = getTime();
        fgets(string, buffer_size, stdin);
        printf("%s\n", string);
        TMessage *msg = (TMessage *) malloc(sizeof(TMessage));
        *msg = createMessage(string);
        struct timespec *finish = getTime();

        addTime(readTimes, *start, *finish);

        free(start);
        free(finish);

        if (msg->type == STOP) {
            wasStopMsg = 1;
            addItem(lockQueue, msg);
        } else {
            pthread_t tid;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_create(&tid, &attr, per_thread, msg);
            pthread_join(tid, NULL);
        }
    }

    free(string);
}

void task_strategy() {
    fibonacciLockQueue = createLockQueue();
    powLockQueue = createLockQueue();
    sortLockQueue = createLockQueue();

    pthread_t tidFibonacci;
    pthread_t tidPow;
    pthread_t tidSort;

    pthread_attr_t attrFibonacci;
    pthread_attr_t attrPow;
    pthread_attr_t attrSort;

    pthread_attr_init(&attrFibonacci);
    pthread_attr_init(&attrPow);
    pthread_attr_init(&attrSort);

    pthread_create(&tidFibonacci, &attrFibonacci, per_task_fibonacci, NULL);
    pthread_create(&tidPow, &attrPow, per_task_pow, NULL);
    pthread_create(&tidSort, &attrSort, per_task_sort, NULL);

    char *string = calloc(buffer_size, sizeof(char));
    int wasStopMsg = 0;

    while (!wasStopMsg) {
        struct timespec *start = getTime();
        fgets(string, buffer_size, stdin);
        printf("%s\n", string);
        TMessage *msg = (TMessage *) malloc(sizeof(TMessage));
        *msg = createMessage(string);
        struct timespec *finish = getTime();

        addTime(readTimes, *start, *finish);

        if (msg->type == FIBONACCI) {
            addItem(fibonacciLockQueue, msg);
        } else if (msg->type == POW) {
            addItem(powLockQueue, msg);
        } else if (msg->type == BUBBLE_SORT_UINT64) {
            addItem(sortLockQueue, msg);
        } else {
            wasStopMsg = 1;
            TMessage *stopFibonacci = (TMessage *) malloc(sizeof(TMessage));
            TMessage *stopPow = (TMessage *) malloc(sizeof(TMessage));
            TMessage *stopSort = (TMessage *) malloc(sizeof(TMessage));

            *stopFibonacci = createStop();
            *stopPow = createStop();
            *stopSort = createStop();

            addItem(fibonacciLockQueue, stopFibonacci);
            addItem(powLockQueue, stopPow);
            addItem(sortLockQueue, stopSort);
            addItem(lockQueue, msg);
        }

        free(start);
        free(finish);
    }

    pthread_join(tidFibonacci, NULL);
    pthread_join(tidPow, NULL);
    pthread_join(tidSort, NULL);

    destroyQueue(fibonacciLockQueue);
    destroyQueue(powLockQueue);
    destroyQueue(sortLockQueue);
    free(string);
}

void pool_strategy(long countThreads) {
    ThreadPool *pool = createThreadPool(countThreads);

    char *string = calloc(buffer_size, sizeof(char));
    int wasStopMsg = 0;

    while (!wasStopMsg) {
        struct timespec *start = getTime();
        fgets(string, buffer_size, stdin);
        printf("%s\n", string);
        TMessage *msg = (TMessage *) malloc(sizeof(TMessage));
        *msg = createMessage(string);
        struct timespec *finish = getTime();

        addTime(readTimes, *start, *finish);

        free(start);
        free(finish);

        if (msg->type == STOP) {
            wasStopMsg = 1;
            destroyThreadPool(pool);
            addItem(lockQueue, msg);
        } else {
            addItem(pool->taskQueue, msg);
            //addItem(taskQueue, msg);
        }
    }

    free(string);
}

void *reader_thread(void *param) {
    ThreadParam *threadParam = (ThreadParam *) param;

    printf("%u", threadParam->strategyType);
    printf("%ld", threadParam->data);

    if (threadParam->strategyType == PER_THREAD) {
        thread_strategy();
    } else if (threadParam->strategyType == PER_TASK) {
        task_strategy();
    } else if (threadParam->strategyType == THREAD_POOL) {
        pool_strategy(threadParam->data);
    } else {
        TMessage msg = createStop();
        addItem(lockQueue, &msg);
    }

    pthread_exit(0);
}

void *writer_thread(void *param) {
    int wasStopMsg = 0;

    int destFile = open("../result", O_WRONLY | O_CREAT, 00700);
    if (destFile == -1) {
        _exit(EBADF);
    }

    while (!wasStopMsg) {
        TMessage *message = getItem(lockQueue);

        if (message->type == STOP) {
            wasStopMsg = 1;
        } else {
            struct timespec *start = getTime();
            writeMessageToFile(*message, destFile);
            struct timespec *finish = getTime();

            addTime(writeTimes, *start, *finish);

            free(start);
            free(finish);
            free(message->data);
        }
        free(message);
    }

    close(destFile);

    pthread_exit(0);
}

void *per_thread(void *param) {
    TMessage *message = (TMessage *) param;

    struct timespec *start = getTime();
    switch (message->type) {
        case FIBONACCI: {
            fibonacci(message->data[0]);
            break;
        }
        case POW: {
            power(message->data[0], message->data[1]);
            break;
        }
        case BUBBLE_SORT_UINT64: {
            bubbleSort(message->data, message->size);
            break;
        }
        default: {
            break;
        }
    }
    struct timespec *finish = getTime();

    addItem(lockQueue, message);
    addTime(executionTimes, *start, *finish);

    free(start);
    free(finish);

    pthread_exit(0);
}

void *per_task_fibonacci(void *param) {
    int wasStopMsg = 0;

    while (!wasStopMsg) {
        TMessage *message = getItem(fibonacciLockQueue);

        if (message->type == STOP) {
            wasStopMsg = 1;
            free(message);
        } else {
            struct timespec *start = getTime();
            fibonacci(message->data[0]);
            struct timespec *finish = getTime();

            addItem(lockQueue, message);
            addTime(executionTimes, *start, *finish);

            free(start);
            free(finish);
        }
    }

    pthread_exit(0);
}

void *per_task_pow(void *param) {
    int wasStopMsg = 0;

    while (!wasStopMsg) {
        TMessage *message = getItem(powLockQueue);

        if (message->type == STOP) {
            wasStopMsg = 1;
            free(message);
        } else {
            struct timespec *start = getTime();
            power(message->data[0], message->data[1]);
            struct timespec *finish = getTime();

            addItem(lockQueue, message);
            addTime(executionTimes, *start, *finish);

            free(start);
            free(finish);
        }
    }

    pthread_exit(0);
}

void *per_task_sort(void *param) {
    int wasStopMsg = 0;

    while (!wasStopMsg) {
        TMessage *message = getItem(sortLockQueue);

        if (message->type == STOP) {
            wasStopMsg = 1;
            free(message);
        } else {
            struct timespec *start = getTime();
            bubbleSort(message->data, message->size);
            struct timespec *finish = getTime();

            addItem(lockQueue, message);
            addTime(executionTimes, *start, *finish);

            free(start);
            free(finish);
        }
    }

    pthread_exit(0);
}

ThreadPool *createThreadPool(uint8_t threadCount) {
    ThreadPool *pool = (ThreadPool *) malloc(sizeof(ThreadPool));
    pool->threadCount = threadCount;
    pool->taskQueue = createLockQueue();
    pool->firstThread = NULL;
    pthread_cond_init(&pool->nonTasks, NULL);

    for (uint8_t i = 0; i < threadCount; i++) {
        pthread_t tid;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, per_pool, pool);

        struct ThreadItem *item = (struct ThreadItem *) malloc(sizeof(struct ThreadItem));
        item->tid = tid;
        item->next = pool->firstThread;
        pool->firstThread = item;
    }

    return pool;
}

void destroyThreadPool(ThreadPool *pool) {
    struct ThreadItem *item;

    while (pool->taskQueue->count != 0) {
        pthread_cond_wait(&pool->nonTasks, &pool->taskQueue->mutex);
    }

    while (pool->firstThread != NULL) {
        item = pool->firstThread;
        pool->firstThread = pool->firstThread->next;
        pthread_cancel(item->tid);

        free(item);
    }

    destroyQueue(pool->taskQueue);
    free(pool);
}

void *per_pool(void *param) {
    ThreadPool *pool = (ThreadPool *) param;
    int wasStopMsg = 0;

    while (!wasStopMsg) {
        TMessage *message = getItem(pool->taskQueue);

        if (message->type == STOP) {
            wasStopMsg = 1;
        } else {
            struct timespec *start = getTime();
            fibonacci(message->data[0]);
            struct timespec *finish = getTime();

            addItem(lockQueue, message);
            addTime(executionTimes, *start, *finish);

            free(start);
            free(finish);
        }

        if (getCount(pool->taskQueue) == 0) {
            pthread_cond_signal(&pool->nonTasks);
        }
    }

    pthread_exit(0);
}