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

    addItem(queue, createFibonacci(3));
    addItem(queue, createPower(1, 2));

    return queue;
}

void createLockQueueTest() {
    LockQueue *queue = createLockQueue();

    assert(queue != NULL);
    destroyQueue(queue);
}

void addItemTest() {
    LockQueue *queue = createTestLockQueue();
    addItem(queue, createFibonacci(5));

    assert(queue->count == 3);
    destroyQueue(queue);
}

void getItemTest() {
    LockQueue *queue = createTestLockQueue();

    assert(getItem(queue).data != NULL);
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