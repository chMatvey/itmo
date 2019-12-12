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

void thread_strategy();

void task_strategy();

void pool_strategy();

void *reader_thread(void *param);

void *writer_thread(void *param);

void *per_thread(void *param);

void *per_task_fibonacci(void *param);

void *per_task_pow(void *param);

void *per_task_sort(void *param);


