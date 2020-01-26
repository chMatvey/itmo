//
// Created by matvey on 25.11.2019.
//

#include "handler.h"
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "message-manager.h"
#include "timer.h"
#include "client-handler.h"
#include "mongoose/mongoose.h"
#include "flags.h"
#include <pthread.h>
#include <asm/errno.h>

int thread_strategy() {
    int wasStopMsg = 0;

    while (!wasStopMsg) {
        struct mg_mgr mgr;
        struct mg_connection *nc;
        mg_mgr_init(&mgr, NULL);
        nc = mg_connect(&mgr, "tcp://127.0.0.1:27015", client_handler);

        if (nc != NULL) {
            printf("Getting message...\n");
            struct timespec *start = getTime();
            for (;;) {
                mg_mgr_poll(&mgr, 1000);
                if (getFlag() == 0) {
                    continue;
                } else {
                    TMessage *msg = getMsg();
                    struct timespec *finish = getTime();
                    addTime(readTimes, *start, *finish);
                    free(start);
                    free(finish);

                    if (msg == NULL) {
                        msg = (TMessage *) malloc(sizeof(TMessage));
                        *msg = createStop();
                    }

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

                    break;
                }
            }
        } else {
            return 1;
        }

        setFlag();
        //mg_mgr_free(&mgr);
    }

    return 0;
}

int task_strategy() {
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

    int wasStopMsg = 0;

    while (!wasStopMsg) {
        struct mg_mgr mgr;
        struct mg_connection *nc;
        mg_mgr_init(&mgr, NULL);
        nc = mg_connect(&mgr, "tcp://127.0.0.1:27015", client_handler);

        if (nc != NULL) {
            printf("Getting message...\n");
            struct timespec *start = getTime();
            for (;;) {
                mg_mgr_poll(&mgr, 1000);
                if (getFlag() == 0) {
                    continue;
                } else {
                    TMessage *msg = getMsg();
                    struct timespec *finish = getTime();
                    addTime(readTimes, *start, *finish);
                    free(start);
                    free(finish);

                    if (msg == NULL) {
                        msg = (TMessage *) malloc(sizeof(TMessage));
                        *msg = createStop();
                    }

                    if (msg->type == STOP) {
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
                    } else if (msg->type == FIBONACCI) {
                        addItemWidthTimer(fibonacciLockQueue, msg);
                    } else if (msg->type == POW) {
                        addItemWidthTimer(powLockQueue, msg);
                    } else if (msg->type == BUBBLE_SORT_UINT64) {
                        addItemWidthTimer(sortLockQueue, msg);
                    }

                    break;
                }
            }
        } else {
            return 1;
        }

        //mg_mgr_free(&mgr);
        setFlag();
    }

    pthread_join(tidFibonacci, NULL);
    pthread_join(tidPow, NULL);
    pthread_join(tidSort, NULL);

    destroyQueue(fibonacciLockQueue);
    destroyQueue(powLockQueue);
    destroyQueue(sortLockQueue);

    return 0;
}

int pool_strategy(long countThreads) {
    ThreadPool *pool = createThreadPool(countThreads);

    int wasStopMsg = 0;

    while (!wasStopMsg) {
        struct mg_mgr mgr;
        struct mg_connection *nc;
        mg_mgr_init(&mgr, NULL);
        nc = mg_connect(&mgr, "tcp://127.0.0.1:27015", client_handler);

        if (nc != NULL) {
            printf("Getting message...\n");
            struct timespec *start = getTime();
            for (;;) {
                mg_mgr_poll(&mgr, 1000);
                if (getFlag() == 0) {
                    continue;
                } else {
                    TMessage *msg = getMsg();
                    struct timespec *finish = getTime();
                    addTime(readTimes, *start, *finish);
                    free(start);
                    free(finish);

                    if (msg == NULL) {
                        msg = (TMessage *) malloc(sizeof(TMessage));
                        *msg = createStop();
                    }

                    if (msg->type == STOP) {
                        wasStopMsg = 1;
                        destroyThreadPool(pool);
                        addItem(lockQueue, msg);
                    } else {
                        addItemWidthTimer(pool->taskQueue, msg);
                    }

                    break;
                }
            }
        } else {
            return 1;
        }

        //mg_mgr_free(&mgr);
        setFlag();
    }

    return 0;
}

void *reader_thread(void *param) {
    ThreadParam *threadParam = (ThreadParam *) param;
    int result = -1;

    if (threadParam->strategyType == PER_THREAD) {
        result = thread_strategy();
    } else if (threadParam->strategyType == PER_TASK) {
        result = task_strategy();
    } else if (threadParam->strategyType == THREAD_POOL) {
        result = pool_strategy(threadParam->data);
    }

    if (result < 0) {
        TMessage *msg = (TMessage *) malloc(sizeof(TMessage));
        *msg = createStop();
        addItem(lockQueue, msg);
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
    struct timespec *finish;
    switch (message->type) {
        case FIBONACCI: {
            fibonacci(message->data[0]);
            finish = getTime();
            addTime(executionTimesF, *start, *finish);
            break;
        }
        case POW: {
            power(message->data[0], message->data[1]);
            finish = getTime();
            addTime(executionTimesP, *start, *finish);
            break;
        }
        case BUBBLE_SORT_UINT64: {
            bubbleSort(message->data, message->size);
            finish = getTime();
            addTime(executionTimesS, *start, *finish);
            break;
        }
        default: {
            break;
        }
    }

    addItem(lockQueue, message);

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
            addTime(executionTimesF, *start, *finish);
            addItem(lockQueue, message);
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
            addTime(executionTimesF, *start, *finish);
            addItem(lockQueue, message);
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
            addTime(executionTimesS, *start, *finish);
            addItem(lockQueue, message);
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
        } else if (message->type == FIBONACCI) {
            struct timespec *start = getTime();
            fibonacci(message->data[0]);
            struct timespec *finish = getTime();
            addTime(executionTimesF, *start, *finish);
            free(start);
            free(finish);
        } else if (message->type == POW) {
            struct timespec *start = getTime();
            pow(message->data[0], message->data[1]);
            struct timespec *finish = getTime();
            addTime(executionTimesP, *start, *finish);
            free(start);
            free(finish);
        } else if (message->type == BUBBLE_SORT_UINT64) {
            struct timespec *start = getTime();
            bubbleSort(message->data, message->size);
            struct timespec *finish = getTime();
            addTime(executionTimesS, *start, *finish);
            free(start);
            free(finish);
        }

        addItem(lockQueue, message);

        if (getCount(pool->taskQueue) == 0) {
            pthread_cond_signal(&pool->nonTasks);
        }
    }

    pthread_exit(0);
}