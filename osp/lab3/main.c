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

typedef enum {
    PER_THREAD,
    PER_TASK,
    THREAD_POOL
} StrategyType;

const int buffer_size = 100000;

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
    uint8_t result = 1;
    while (exponent != 0) {
        result *= basis;
        exponent--;
    }

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

char *readFromFile(char *filename) {
    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, 1, fsize, f);
    fclose(f);
    free(f);

    string[fsize] = 0;

    return string;
}

TMessage *createMessage(char *string) {
    cJSON *json = cJSON_Parse(string);
    TMessage *msg = (TMessage *) malloc(sizeof(TMessage));

    if (strcmp(json->child->valuestring, "FIBONACCI") == 0) {
        msg->type = FIBONACCI;
    } else if (strcmp(json->child->valuestring, "POW") == 0) {
        msg->type = POW;
    } else if (strcmp(json->child->valuestring, "BUBBLE_SORT") == 0) {
        msg->type = BUBBLE_SORT_UINT64;
    } else {
        msg->type = STOP;
    }

    if (msg->type != STOP) {
        msg->type = (EType) json->child->valuestring;
        msg->size = (uint64_t) json->child->next->valueint;
        cJSON *data = json->child->next->next->child;
        uint64_t dataSize = 1;
        msg->data = (uint8_t *) malloc(sizeof(uint8_t));
        msg->data[0] = (uint8_t) data->valueint;

        while (data->next != NULL) {
            dataSize++;
            data = data->next;
            msg->data = (uint8_t *) realloc(msg->data, sizeof(uint8_t) * dataSize);
            msg->data[dataSize - 1] = (uint8_t) data->valueint;
        }

        free(data);
    }

    free(json);

    return msg;
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
        default: {
            break;
        }
    }

    return param;
}

void *reader_thread(void *param) {
    StrategyType sType = (StrategyType) param;
    char *string = NULL;
    TMessage* msg = (TMessage *) malloc(sizeof(msg));
    int wasStopMsg = 0;

    while(!wasStopMsg) {
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

int main() {
    char *string = readFromFile("../data.json");
    TMessage *msg = createMessage(string);

    free(string);
    free(msg);
}