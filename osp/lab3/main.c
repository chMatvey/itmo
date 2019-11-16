#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "cJSON/cJSON.h"
#include "cJSON/cJSON.c"

typedef enum {
    FIBONACCI,
    POW,
    BUBBLE_SORT_UINT64,
    STOP
} EType;

typedef struct {
    EType type;
    uint64_t size;
    uint8_t *data;
} TMessage;

void advancedPrint(char *str) {
    size_t length = strlen(str);
    size_t size = 0;

    while (size != length) {
        size_t s = write(STDOUT_FILENO, str + size, length - size);
        if (s == -1) {
            return;
        }
        size += s;
    }
}

uint8_t power(uint8_t basis, uint8_t exponent) {
    uint8_t result = (uint8_t) basis;
    return result;
}

uint8_t fibonacci(uint8_t n) {
    if (n < 1) {
        return -1;
    }

    uint8_t first = 0;
    uint8_t second = 1;
    uint8_t next = 0;

    for (uint64_t i = 0; i < n; i++) {
        if (i < 2) {
            next = i;
        } else {
            next = first + second;
            first = second;
            second = next;
        }
    }

    return next;
}

void bubbleSort(uint8_t *array, uint64_t length) {
    for (uint64_t i = 0; i < length; i++) {
        for (uint64_t j = 1 + i; j < length; j++) {
            if (array[i] > array[j]) {
                array[i] = array[i] + array[j];
                array[j] = array[i] - array[j];
                array[i] = array[i] - array[j];
            }
        }
    }
}

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
        case STOP: {
            break;
        }
        default: {
            break;
        }
    }

    return param;
}

void read_csv(char *filename, uint8_t *data) {
    FILE *file = fopen(filename, "r");
    char buf[1024];
    int i = 0;

    while (fgets(buf, 1024, file)) {
        char *tmp = strdup(buf);
        const char *tok;

        for (tok = strtok(buf, ";"); tok && *tok; tok = strtok(NULL, ";\n")) {
            data[i] = (uint8_t) atoi(tok);
            i++;
        }
    }

    fclose(file);
}

TMessage parseJson(char *filename) {
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);

    string[fsize] = 0;

    cJSON *json = cJSON_Parse(string);

    return NULL;
}

void getTasks(uint8_t *data, uint64_t dataCount) {
    uint64_t taskFibonacciCount = data[0];
    uint64_t taskPowerCount = data[1];
    uint64_t taskBubbleSortCount = data[2];
    uint64_t taskCount = taskFibonacciCount + taskPowerCount + taskBubbleSortCount;

    TMessage *result[taskCount];
    for (uint64_t i = 0; i < taskCount; i++) {
        result[i] = (TMessage *) malloc(sizeof(TMessage));
    }
}

void readThread() {

}

void writeThread() {

}

int main() {



//    pthread_t tid; /* идентификатор потока */
//    pthread_attr_t attr; /* отрибуты потока */
//
//    TMessage *message = (TMessage *) malloc(sizeof(TMessage));
//    message->type = BUBBLE_SORT_UINT64;
//    message->size = 4;
//    message->data = (uint8_t *) malloc(message->size * sizeof(uint8_t));
//    message->data[0] = 12;
//    message->data[1] = 2;
//    message->data[2] = 13;
//    message->data[3] = 1;
//
//    pthread_attr_init(&attr);
//    pthread_create(&tid, &attr, per_thread, message);
//
//    pthread_join(tid, NULL);
//
//    free(data);
//    free(message->data);
//    free(message);
}