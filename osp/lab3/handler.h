//
// Created by matvey on 25.11.2019.
//

#ifndef LAB3_HANDLER_H
#define LAB3_HANDLER_H

#endif //LAB3_HANDLER_H

typedef enum {
    PER_THREAD = 1,
    PER_TASK = 2,
    THREAD_POOL = 3
} StrategyType;

void *per_thread(void *param);

void *reader_thread(void *param);
