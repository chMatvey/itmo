//
// Created by matvey on 11.01.2020.
//

#include "message-manager.h"
#include "mongoose.h"

#ifndef LAB3_READ_H
#define LAB3_READ_H

#endif //LAB3_READ_H

#pragma once

TMessage *readProtoMessage();

void client_handler(struct mg_connection *conn, int ev, void *p);