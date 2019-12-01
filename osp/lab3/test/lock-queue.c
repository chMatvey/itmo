//
// Created by matvey on 29.11.2019.
//

#include "lock-queueTest.h"
#include "../lock-queue.h"
#include <assert.h>
#include <malloc.h>
#include "../message.h"

LockQueue *createTestLockQueue() {
    LockQueue *queue = createLockQueue();

    TMessage *message = (TMessage *) malloc(sizeof(TMessage));
    *message = createFibonacci(3);
    addItem(queue, message);
    *message = createPower(1, 2);
    addItem(queue, message);

    return queue;
}

void createLockQueueTest() {
    LockQueue *queue = createLockQueue();

    assert(queue != NULL);
    destroyQueue(queue);
}

void addItemTest() {
    LockQueue *queue = createTestLockQueue();
    TMessage *message = (TMessage *) malloc(sizeof(TMessage));
    *message = createFibonacci(3);
    addItem(queue, message);

    assert(queue->count == 3);

    destroyQueue(queue);
}

void getItemTest() {
    LockQueue *queue = createTestLockQueue();

    assert(getItem(queue)->data != NULL);

    destroyQueue(queue);;
}

void getCountTest() {
    LockQueue *queue = createTestLockQueue();

    assert(getCount(queue) == 2);
    destroyQueue(queue);
}

void destroyQueueTest() {
    LockQueue *queue = createTestLockQueue();
    destroyQueue(queue);

    assert(queue->count == 0);
}

void lockQueueTest() {
    createLockQueueTest();
    addItemTest();
    getItemTest();
    getCountTest();
    destroyQueueTest();
}