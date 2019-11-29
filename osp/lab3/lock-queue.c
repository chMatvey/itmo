//
// Created by matvey on 29.11.2019.
//

#include "lock-queue.h"
#include <malloc.h>

LockQueue createLockQueue() {
    LockQueue queue;
    queue.count = 0;
    queue.first = NULL;
    pthread_mutex_init(&queue.mutex, NULL);

    return queue;
}

void addItem(LockQueue *queue, TMessage message) {
    struct LockItem *item = (struct LockItem *) malloc(sizeof(struct LockItem));
    item->message = message;
    item->next = queue->first;

    pthread_mutex_lock(&queue->mutex);

    queue->first = item;
    queue->count++;

    pthread_mutex_unlock(&queue->mutex);
}

TMessage getItem(LockQueue *queue) {
    pthread_mutex_lock(&queue->mutex);

    struct LockItem result = *queue->first;
    if (queue->first != NULL) {
        queue->first = queue->first->next;
        queue->count--;
    }

    pthread_mutex_unlock(&queue->mutex);

    return result.message;
}

uint64_t getCount(LockQueue *queue) {
    return queue->count;
}

void destroyQueue(LockQueue *queue) {
    struct LockItem *item;
    struct LockItem *next = queue->first;

    while (next != NULL) {
        item = next;
        next = item->next;
        free(item);
    }

    pthread_mutex_destroy(&queue->mutex);
    free(queue);
}