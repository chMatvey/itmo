//
// Created by matvey on 25.11.2019.
//

#include "message.h"

#ifndef LAB3_HANDLER_H
#define LAB3_HANDLER_H

#endif //LAB3_HANDLER_H

#pragma once

typedef enum {
    PER_THREAD = 1,
    PER_TASK = 2,
    THREAD_POOL = 3
} StrategyType;

void *reader_thread(void *param);

void writeToFile(TMessage message, int fileDescriptor);

void *writer_thread(void *param);

void *per_thread(void *param);
