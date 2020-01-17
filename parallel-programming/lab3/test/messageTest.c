//
// Created by matvey on 29.11.2019.
//

#include "messageTest.h"
#include <stdint.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include "../message-manager.h"

void powerTest() {
    assert(power(4, 2) == 16);
    assert(power(4, 3) == 64);
}

void fibonacciTest() {
    assert(fibonacci(1) == 0);
    assert(fibonacci(2) == 1);
    assert(fibonacci(3) == 1);
    assert(fibonacci(4) == 2);
    assert(fibonacci(11) == 55);
}

void bubbleSortTest() {
    uint8_t *array = (uint8_t *) calloc(4, sizeof(uint8_t));
    array[0] = 4;
    array[1] = 3;
    array[2] = 2;
    array[3] = 1;

    bubbleSort(array, 4);

    assert(array[0] == 1);
    assert(array[1] == 2);
    assert(array[2] == 3);
    assert(array[3] == 4);

    free(array);
}

void createFibonacciTest() {
    TMessage message = createFibonacci(3);

    assert(message.type == FIBONACCI);
    assert(message.data[0] == 3);
    assert(message.size == 1);

    free(message.data);
}

void createPowerTest() {
    TMessage message = createPower(3, 4);

    assert(message.type == POW);
    assert(message.data[0] == 3);
    assert(message.data[1] == 4);
    assert(message.size == 2);

    free(message.data);
}

void createBubbleSortTest() {
    int size = 4;
    uint8_t *array = (uint8_t *) calloc(size, sizeof(uint8_t));
    array[0] = 4;
    array[1] = 3;
    array[2] = 2;
    array[3] = 1;

    TMessage message = createBubbleSort(array, size);

    assert(message.type == BUBBLE_SORT_UINT64);
    assert(message.size == size);

    free(message.data);
}

void createStopTest() {
    TMessage message = createStop();

    assert(message.type == STOP);
}

void createMessageTest() {
    char *fibonacciStr = "{\"type\":\"FIBONACCI\",\"size\":1,\"data\":[210]}";
    char *powerStr = "{\"type\":\"POW\",\"size\":2,\"data\":[52,136]}";
    char *sortStr = "{\"type\":\"BUBBLE_SORT\",\"size\":21,\"data\":[246,85,109,34,164,184,17,244,10,83,3,192,237,7,184,11,128,81,192,215,167]}";
    char *stopStr = "{\"type\":\"STOP\",\"size\":0,\"data\":[]}";

    TMessage msqFibonacci = createMessage(fibonacciStr);
    TMessage msgPower = createMessage(powerStr);
    TMessage msgSort = createMessage(sortStr);
    TMessage msgStop = createMessage(stopStr);

    assert(msqFibonacci.type == FIBONACCI);
    assert(msgPower.type == POW);
    assert(msgSort.type == BUBBLE_SORT_UINT64);
    assert(msgStop.type == STOP);

    free(msqFibonacci.data);
    free(msgPower.data);
    free(msgSort.data);
}

void getJsonStrTest() {
    int size = 2;
    uint8_t *array = (uint8_t *) calloc(size, sizeof(uint8_t));
    array[0] = 4;
    array[1] = 3;

    TMessage messageFibonacci = createFibonacci(3);
    TMessage messagePow = createPower(3, 4);
    TMessage messageSort = createBubbleSort(array, size);

    char *strFibonacci = getJsonStr(messageFibonacci);
    char *strPow = getJsonStr(messagePow);
    char *strSort = getJsonStr(messageSort);

    assert(strcmp("{\n"
                  "\t\"type\":\t\"FIBONACCI\",\n"
                  "\t\"size\":\t1,\n"
                  "\t\"data\":\t[3]\n"
                  "}", strFibonacci) == 0);
    assert(strcmp("{\n"
                  "\t\"type\":\t\"POW\",\n"
                  "\t\"size\":\t2,\n"
                  "\t\"data\":\t[3, 4]\n"
                  "}", strPow) == 0);
    assert(strcmp("{\n"
                  "\t\"type\":\t\"BUBBLE_SORT_UINT64\",\n"
                  "\t\"size\":\t2,\n"
                  "\t\"data\":\t[4, 3]\n"
                  "}", strSort) == 0);

    free(strFibonacci);
    free(strPow);
    free(strSort);
    free(messageSort.data);
    free(messagePow.data);
    free(messageFibonacci.data);
}

void messageTest() {
    powerTest();
    fibonacciTest();
    bubbleSortTest();
    createFibonacciTest();
    createPowerTest();
    createBubbleSortTest();
    createStopTest();
    createMessageTest();
    getJsonStrTest();
}

