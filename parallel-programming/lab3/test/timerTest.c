//
// Created by matvey on 07.12.2019.
//

#include "timerTest.h"
#include "../timer.h"
#include <assert.h>
#include <malloc.h>

void timerTest() {
    createTimeQueueTest();
    addTimeTest();
    toArrayTest();
}

TimeQueue *createTestTimeQueue() {
    TimeQueue *queue = NULL;
    queue = createTimeQueue();

    struct timespec *first = getTime();
    struct timespec *second = getTime();
    addTime(queue, *first, *second);

    struct timespec *first1 = getTime();
    struct timespec *second1 = getTime();
    addTime(queue, *first1, *second1);

    free(first);
    free(first1);
    free(second);
    free(second1);

    return queue;
}

void createTimeQueueTest() {
    TimeQueue *queue = NULL;
    queue = createTimeQueue();

    assert(queue != NULL);

    destroyTimeQueue(queue);
}

void addTimeTest() {
    TimeQueue *queue = createTestTimeQueue();

    assert(queue->count == 2);

    destroyTimeQueue(queue);
}

void toArrayTest() {
    TimeQueue *queue = createTestTimeQueue();
    long *array = toArray(*queue);

    assert(array[0] <= array[1]);

    free(array);
    destroyTimeQueue(queue);
}