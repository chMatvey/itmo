//
// Created by matvey on 29.11.2019.
//

#include "lock-queueTest.h"
#include "../lock-queueTest.h"
#include <assert.h>
#include <malloc.h>
#include "../message.h"

LockQueue *createTestLockQueue() {
    LockQueue *queue = createLockQueue();

    TMessage *message1 = (TMessage *) malloc(sizeof(TMessage));
    TMessage *message2 = (TMessage *) malloc(sizeof(TMessage));
    *message1 = createFibonacci(3);
    addItem(queue, message1);
    *message2 = createPower(1, 2);
    addItem(queue, message2);

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

    TMessage * msg = getItem(queue);
    assert(msg->data != NULL);

    free(msg->data);
    free(msg);
    destroyQueue(queue);
}

void getCountTest() {
    LockQueue *queue = createTestLockQueue();

    assert(getCount(queue) == 2);
    destroyQueue(queue);
}

void destroyQueueTest() {
    LockQueue *queue = createTestLockQueue();
    destroyQueue(queue);
}

void lockQueueTest() {
    createLockQueueTest();
    addItemTest();
    getItemTest();
    getCountTest();
    destroyQueueTest();
}