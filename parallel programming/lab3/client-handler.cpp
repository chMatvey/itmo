//
// Created by matvey on 11.01.2020.
//

#include "message-manager.h"
#include "proto/message.pb.h"
#include <iostream>
#include "mongoose.h"
#include <string.h>
#include "handler.h"

using namespace std;

using namespace std;

static bool connected = 0;

const int buffer_size = 1024 * 1024;

TMessage createMessageByProto(EType type, uint64_t size, uint8_t *data) {
    TMessage result;
    result.type = type;
    result.size = size;
    result.data = data;

    return result;
}

extern "C" void client_handler(struct mg_connection *conn, int ev, void *p) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    struct mbuf *io = &conn->send_mbuf;
    static int a = 1;

    if (ev == MG_EV_RECV) {
        lab3::TMessage receivedMsg = lab3::TMessage();
        receivedMsg.ParseFromString((&conn->recv_mbuf)->buf);

        EType eType;
        if (receivedMsg.type() == lab3::FIBONACCI) {
            eType = FIBONACCI;
        } else if (receivedMsg.type() == lab3::POW) {
            eType = POW;
        } else if (receivedMsg.type() == lab3::BUBBLE_SORT_UINT64) {
            eType = BUBBLE_SORT_UINT64;
        } else {
            eType = STOP;
        }
        uint64_t size = receivedMsg.size();
        auto *data = (uint8_t *) calloc(size, sizeof(uint8_t));
        for (uint64_t i = 0; i < size; i++) {
            data[i] = receivedMsg.data(i);
        }
        auto *result = (TMessage *) malloc(sizeof(TMessage));
        *result = createMessageByProto(eType, size, data);
        conn->user_data = result;
    }
}