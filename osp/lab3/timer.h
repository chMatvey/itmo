//
// Created by matvey on 07.12.2019.
//

#ifndef LAB3_TIMER_H
#define LAB3_TIMER_H

#endif //LAB3_TIMER_H

#pragma once

#include <pthread.h>
#include <time.h>
#include <stdint.h>

struct Item {
    long value;
    struct Item *next;
};

typedef struct {
    uint64_t count;
    struct Item *first;
    pthread_mutex_t mutex;
//    long *array;
} TimeQueue;

TimeQueue *readTimes;
TimeQueue *inQueueTimes;
TimeQueue *executionTimes;
TimeQueue *writeTimes;

TimeQueue *createTimeQueue();

void addTime(TimeQueue *queue, struct timespec first, struct timespec second);

struct timespec *getTime();

void printTimesToFile(TimeQueue queue, int fileDescriptor);

void destroyTimeQueue(TimeQueue *queue);

long *toArray(TimeQueue queue);