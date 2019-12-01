//
// Created by matvey on 25.11.2019.
//

#include "message.h"
#include "cJSON/cJSON.h"
#include "cJSON/cJSON.c"
#include <stdint.h>
#include <malloc.h>

uint64_t power(uint8_t basis, uint8_t exponent) {
    uint64_t result = 1;
    while (exponent != 0) {
        result *= basis;
        exponent--;
    }

    return result;
}

uint64_t fibonacci(uint8_t n) {
    if (n < 1) {
        return -1;
    }

    uint64_t first = 0;
    uint64_t second = 1;
    uint64_t next = 0;

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

TMessage createFibonacci(uint8_t n) {
    TMessage message;
    message.type = FIBONACCI;
    message.size = 1;
    message.data = calloc(message.size, sizeof(uint8_t));
    message.data[0] = n;

    return message;
}

TMessage createPower(uint8_t basis, uint8_t exponent) {
    TMessage message;
    message.type = POW;
    message.size = 2;
    message.data = calloc(message.size, sizeof(uint8_t));
    message.data[0] = basis;
    message.data[1] = exponent;

    return message;
}

TMessage createBubbleSort(uint8_t *array, uint64_t length) {
    TMessage message;
    message.type = BUBBLE_SORT_UINT64;
    message.size = length;
    message.data = array;

    return message;
}

TMessage createStop() {
    TMessage message;
    message.type = STOP;

    return message;
}

TMessage createMessage(char *string) {
    cJSON *json = cJSON_Parse(string);
    cJSON *data = json->child->next->next->child;
    TMessage message;

    if (strcmp(json->child->valuestring, "FIBONACCI") == 0) {
        message = createFibonacci((uint8_t) data->valueint);
    } else if (strcmp(json->child->valuestring, "POW") == 0) {
        uint8_t basic = data->valueint;
        uint8_t exponent = data->next->valueint;
        message = createPower(basic, exponent);
    } else if (strcmp(json->child->valuestring, "BUBBLE_SORT") == 0) {
        uint64_t size = 0;
        uint8_t *array = NULL;

        while (data != NULL) {
            size++;
            array = (uint8_t *) realloc(array, sizeof(uint8_t) * size);
            array[size - 1] = (uint8_t) data->valueint;
            data = data->next;
        }

        message = createBubbleSort(array, size);
    } else {
        message = createStop();
    }

    free(json);

    return message;
}

char *getMessageTypeStr(EType type) {
    if (type == FIBONACCI) {
        return "FIBONACCI";
    } else if (type == POW) {
        return "POW";
    } else if (type == BUBBLE_SORT_UINT64) {
        return "BUBBLE_SORT_UINT64";
    } else {
        return "STOP";
    }

}

char *getJsonStr(TMessage message) {
    cJSON *monitor = cJSON_CreateObject();
    cJSON *type = cJSON_CreateString(getMessageTypeStr(message.type));
    cJSON *size = cJSON_CreateNumber(message.size);
    uint64_t count = message.size;
    if (message.type == FIBONACCI) {
        count = 1;
    } else if (message.type == POW) {
        count = 2;
    }
    cJSON *data = cJSON_CreateIntArray((const int *) message.data, count);
    cJSON_AddItemToObject(monitor, "type", type);
    cJSON_AddItemToObject(monitor, "size", size);
    cJSON_AddItemToObject(monitor, "data", data);

    char *result = cJSON_Print(monitor);

    free(data);
    free(size);
    free(type);
    free(monitor);

    return result;
}

