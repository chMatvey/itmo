//
// Created by matvey on 29.11.2019.
//

#include <stdint-gcc.h>

#ifndef LAB3_LOCK_QUEUE_H
#define LAB3_LOCK_QUEUE_H

#endif //LAB3_LOCK_QUEUE_H

#pragma once

#include <pthread.h>
#include "message-manager.h"

struct LockItem {
    TMessage *message;
    struct LockItem *next;
};

typedef struct {
    uint64_t count;
    struct LockItem *first;
    pthread_mutex_t mutex;
    pthread_cond_t count_nonzero;
} LockQueue;

LockQueue *lockQueue;

LockQueue *fibonacciLockQueue;

LockQueue *powLockQueue;

LockQueue *sortLockQueue;

LockQueue *createLockQueue();

void addItem(LockQueue *queue, TMessage *message);

void addItemWidthTimer(LockQueue *queue, TMessage *message);

TMessage *getItem(LockQueue *queue);

uint64_t getCount(LockQueue *queue);

void destroyQueue(LockQueue *queue);

