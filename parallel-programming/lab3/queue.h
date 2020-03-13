//
// Created by matvey on 17.01.2020.
//

#include "message-manager.h"

#ifndef LAB3_QUEUE_H
#define LAB3_QUEUE_H

#endif //LAB3_QUEUE_H

#pragma once

struct Item {
    TMessage *message;
    struct Item *next;
};

typedef struct {
    uint64_t count;
    struct Item *first;
} Queue;