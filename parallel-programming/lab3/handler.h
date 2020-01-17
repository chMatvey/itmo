//
// Created by matvey on 25.11.2019.
//

#include <pthread.h>
#include "lock-queue.h"
#include "message-manager.h"


#ifndef LAB3_HANDLER_H
#define LAB3_HANDLER_H

#endif //LAB3_HANDLER_H

#pragma once

typedef enum {
    PER_THREAD = 1,
    PER_TASK = 2,
    THREAD_POOL = 3
} StrategyType;

typedef struct {
    StrategyType strategyType;
    long data;
} ThreadParam;

int thread_strategy();

int task_strategy();

int pool_strategy(long countThreads);

void *reader_thread(void *param);

void *writer_thread(void *param);

void *per_thread(void *param);

void *per_task_fibonacci(void *param);

void *per_task_pow(void *param);

void *per_task_sort(void *param);

struct ThreadItem {
    pthread_t tid;
    struct ThreadItem *next;
};

typedef struct {
    uint8_t threadCount;
    struct ThreadItem *firstThread;
    LockQueue *taskQueue;
    pthread_cond_t nonTasks;
} ThreadPool;

ThreadPool *createThreadPool(uint8_t threadCount);

void destroyThreadPool(ThreadPool *pool);

void *per_pool(void *param);
