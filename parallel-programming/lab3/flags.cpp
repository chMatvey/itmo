//
// Created by matvey on 17.01.2020.
//

#include "message-manager.h"

int exitFlag = 0;

TMessage *msgPtr = nullptr;

void dropFlag() {
    exitFlag = -1;
}

extern "C" void setFlag() {
    exitFlag = 0;
}

extern "C" int getFlag() {
    return exitFlag;
}

void setMsg(TMessage *ptr) {
    msgPtr = ptr;
}

extern "C" TMessage *getMsg() {
    return msgPtr;
}