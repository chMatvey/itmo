//
// Created by matvey on 25.11.2019.
//

#ifndef LAB3_MESSAGE_H
#define LAB3_MESSAGE_H

#endif //LAB3_MESSAGE_H

#pragma once

#include <stdint.h>

typedef enum {
    FIBONACCI,
    POW,
    BUBBLE_SORT_UINT64,
    STOP
} EType;

typedef struct {
    uint8_t type;
    uint64_t size;
    uint8_t *data;
} TMessage;

uint64_t power(uint8_t basis, uint8_t exponent);

uint64_t fibonacci(uint8_t n);

void bubbleSort(uint8_t *array, uint64_t length);

TMessage createFibonacci(uint8_t n);

TMessage createPower(uint8_t basis, uint8_t exponent);

TMessage createBubbleSort(uint8_t *array, uint64_t length);

TMessage createStop();

TMessage createMessage(char *string);

char *getJsonStr(TMessage message);

void writeMessageToFile(TMessage message, int fileDescriptor);