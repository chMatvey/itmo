//
// Created by matvey on 25.11.2019.
//

#include "handler.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <pthread.h>
#include "message.h"

const int buffer_size = 1024;

void *per_thread(void *param) {
    TMessage *message = (TMessage *) param;

    switch (message->type) {
        case FIBONACCI: {
            if (message->size < 1) {
                return NULL;
            } else {
                message->data[0] = fibonacci(message->data[0]);;
            }
            break;
        }
        case POW: {
            if (message->size < 2) {
                return NULL;
            } else {
                message->data[0] = power(message->data[0], message->data[1]);
            }
            break;
        }
        case BUBBLE_SORT_UINT64: {
            if (message->size < 1) {
                return NULL;
            } else {
                bubbleSort(message->data, message->size);
            }
            break;
        }
        default: {
            break;
        }
    }

    pthread_exit(0);
}

void *reader_thread(void *param) {
    StrategyType sType = (StrategyType) param;
    char *string = NULL;
    TMessage *msg = (TMessage *) calloc(1, sizeof(msg));
    int wasStopMsg = 0;

    while (!wasStopMsg) {
        fgets(string, buffer_size, stdin);
        msg = createMessage(string);

        if (msg->type == STOP) {
            wasStopMsg = 1;
        } else {
            pthread_t tid; /* идентификатор потока */
            pthread_attr_t attr; /* отрибуты потока */
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
    free(msg);
}
