//
// Created by matvey on 07.12.2019.
//

#include "timer.h"
#include <malloc.h>
#include <unistd.h>
#include "errno.h"
#include <string.h>
#include <stdlib.h>
#include "file-manager.h"
#include <stdint.h>

TimeQueue *createTimeQueue() {
    TimeQueue *queue = (TimeQueue *) malloc(sizeof(TimeQueue));
    queue->first = NULL;
//    queue->array = NULL;
    queue->count = 0;
    pthread_mutex_init(&queue->mutex, NULL);

    return queue;
}

void addTime(TimeQueue *queue, struct timespec first, struct timespec second) {
    struct Item *item = (struct Item *) malloc(sizeof(struct Item));
    long time = (second.tv_sec - first.tv_sec) * 1000000000 + (second.tv_nsec - first.tv_nsec);
    item->value = time;

    pthread_mutex_lock(&queue->mutex);

//    if (queue->count == 0) {
//        queue->array = (long *) calloc(1, sizeof(long));
//    } else {
//        queue->array = (long *) realloc(queue->array, queue->count + 1);
//        queue->array[queue->count] = time;
//    }
    queue->count++;
    item->next = queue->first;
    queue->first = item;

    pthread_mutex_unlock(&queue->mutex);
}

struct timespec *getTime() {
    struct timespec *result = (struct timespec *) malloc(sizeof(struct timespec));

    if (clock_gettime(CLOCK_REALTIME, result) == -1) {
        free(result);
        return NULL;
    } else {
        return result;
    }
}

void printTimesToFile(TimeQueue queue, int fileDescriptor) {
    char *str = (char *) calloc(1024, sizeof(char));
    size_t size = 0;

    long *array = toArray(queue);

    for (long i = 0; i < queue.count; i++) {
        sprintf(str, "%ld", array[i]);
        size_t length = strlen(str);
        while (size != length) {
            size_t s = write(fileDescriptor, str + size, length - size);
            if (s == -1) {
                _exit(EIO);
            }
            size += s;
        }
    }

    free(str);
}

void destroyTimeQueue(TimeQueue *queue) {
//    if (queue->count > 0) {
//        free(queue->array);
//    }
    struct Item *item;

    while (queue->first != NULL) {
        item = queue->first;
        queue->first = queue->first->next;
        free(item);
    }

    pthread_mutex_destroy(&queue->mutex);
    free(queue);
}

long *toArray(TimeQueue queue) {
    if (queue.count == 0) {
        return NULL;
    }

    long *result = (long *) calloc(queue.count, sizeof(long));
    struct Item *item = queue.first;

    for (uint64_t i = 0; i < queue.count; i++) {
        
    }
}
