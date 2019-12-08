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
}

void createTimeQueueTest() {
    TimeQueue *queue = NULL;
    queue = createTimeQueue();

    assert(queue != NULL);

    destroyTimeQueue(queue);
}

void addTimeTest() {
    TimeQueue *queue = NULL;
    queue = createTimeQueue();

    struct timespec *first = getTime();
    struct timespec *second = getTime();

    addTime(queue, *first, *second);

    assert(queue->count == 1);

    free(first);
    free(second);
    destroyTimeQueue(queue);
}