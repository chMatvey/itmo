//
// Created by matvey on 25.11.2019.
//

#include "handler.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <asm/errno.h>
#include <fcntl.h>
#include "message.h"
#include "lock-queueTest.h"
#include "timer.h"

const int buffer_size = 1024 * 1024;

void *reader_thread(void *param) {
    StrategyType sType = (StrategyType) param;
    char *string = calloc(buffer_size, sizeof(char));
    int wasStopMsg = 0;

    while (!wasStopMsg) {
        fgets(string, buffer_size, stdin);
        printf("%s\n", string);
        TMessage *msg = (TMessage *) malloc(sizeof(TMessage));
        *msg = createMessage(string);

        if (msg->type == STOP) {
            wasStopMsg = 1;
            addItem(lockQueue, msg);
        } else {
            pthread_t tid;
            pthread_attr_t attr;
            pthread_attr_init(&attr);

            if (sType == PER_THREAD) {
                pthread_create(&tid, &attr, per_thread, msg);
            } else {
                return 0;
            }
            pthread_join(tid, NULL);
        }
    }

    free(string);

    pthread_exit(0);
}

void *writer_thread(void *param) {
    int wasStopMsg = 0;

    int destFile = open("../result", O_WRONLY | O_CREAT, 00700);
    if (destFile == -1) {
        _exit(EBADF);
    }

    while (!wasStopMsg) {
        TMessage *message = getItem(lockQueue);

        if (message->type == STOP) {
            wasStopMsg = 1;
        } else {
            writeMessageToFile(*message, destFile);
            free(message->data);
        }
        free(message);
    }

    close(destFile);

    pthread_exit(0);
}

void *per_thread(void *param) {
    TMessage *message = (TMessage *) param;
    struct timespec *start = getTime();

    switch (message->type) {
        case FIBONACCI: {
            fibonacci(message->data[0]);
            break;
        }
        case POW: {
            power(message->data[0], message->data[1]);
            break;
        }
        case BUBBLE_SORT_UINT64: {
            bubbleSort(message->data, message->size);
            break;
        }
        default: {
            break;
        }
    }

    struct timespec *finish = getTime();

    addItem(lockQueue, message);
    addTime(executionTimes, *start, *finish);

    free(start);
    free(finish);

    pthread_exit(0);
}