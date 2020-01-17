//
// Created by matvey on 29.11.2019.
//

#include "handlerTest.h"
#include "../handler.h"
#include <assert.h>

void handlerTest() {
    createThreadPoolTest();
}

void createThreadPoolTest() {
    ThreadPool *pool = createThreadPool(5);

    assert(pool->threadCount == 5);

    destroyThreadPool(pool);
}
