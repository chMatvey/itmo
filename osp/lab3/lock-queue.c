//
// Created by matvey on 29.11.2019.
//

#include "lock-queueTest.h"
#include <malloc.h>

LockQueue *createLockQueue() {
    LockQueue *queue = (LockQueue *) malloc(sizeof(LockQueue));
    queue->count = 0;
    queue->first = NULL;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->count_nonzero, NULL);

    return queue;
}

void addItem(LockQueue *queue, TMessage *message) {
    struct LockItem *item = (struct LockItem *) malloc(sizeof(struct LockItem));
    item->message = message;

    pthread_mutex_lock(&queue->mutex);

    if (queue->count == 0) {
        pthread_cond_signal(&queue->count_nonzero);
    }

    queue->count++;
    item->next = queue->first;
    queue->first = item;

    pthread_mutex_unlock(&queue->mutex);
}

TMessage *getItem(LockQueue *queue) {
    pthread_mutex_lock(&queue->mutex);

    while (getCount(queue) == 0) {
        pthread_cond_wait(&queue->count_nonzero, &queue->mutex);
    }

    struct LockItem *item = queue->first;
    if (queue->first != NULL) {
        queue->count--;
        queue->first = queue->first->next;
    }

    pthread_mutex_unlock(&queue->mutex);

    TMessage *message = item->message;
    free(item);

    return message;
}

uint64_t getCount(LockQueue *queue) {
    return queue->count;
}

void destroyQueue(LockQueue *queue) {
    struct LockItem *item;

    while (queue->first != NULL) {
        item = queue->first;
        queue->first = queue->first->next;

        free(item->message->data);
        free(item->message);
        free(item);
    }

    pthread_cond_destroy(&queue->count_nonzero);
    pthread_mutex_destroy(&queue->mutex);
    free(queue);
}