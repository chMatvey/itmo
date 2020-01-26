//
// Created by matvey on 11.01.2020.
//

#include "message-manager.h"
#include "proto/message.pb.h"
#include "mongoose.h"
#include "handler.h"
#include "flags.h"

using namespace std;

TMessage createMessageByProto(EType type, uint64_t size, uint8_t *data) {
    TMessage result;
    result.type = type;
    result.size = size;
    result.data = data;

    return result;
}

extern "C" void client_handler(struct mg_connection *conn, int ev, void *p) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (ev == MG_EV_RECV) {
        lab3::TMessage receivedMsg = lab3::TMessage();
        receivedMsg.ParseFromString((&conn->recv_mbuf)->buf);
        auto *msg = (TMessage *) conn->user_data;

        if (msg == nullptr) {
            EType eType;
            if (receivedMsg.type() == lab3::FIBONACCI) {
                eType = FIBONACCI;
            } else if (receivedMsg.type() == lab3::POW) {
                eType = POW;
            } else if (receivedMsg.type() == lab3::BUBBLE_SORT_UINT64) {
                eType = BUBBLE_SORT_UINT64;
            } else if (receivedMsg.type() == lab3::STOP) {
                eType = STOP;
            } else {
                eType = BUBBLE_SORT_UINT64;
            }
            uint64_t size = receivedMsg.size();
            auto *data = (uint8_t *) calloc(size, sizeof(uint8_t));
            msg = (TMessage *) malloc(sizeof(TMessage));
            *msg = createMessageByProto(eType, 0, data);
            conn->user_data = msg;
        }

        for (uint64_t i = msg->size; i < msg->size + receivedMsg.data_size(); i++) {
            msg->data[i] = receivedMsg.data(i - msg->size);
        }
        msg->size += receivedMsg.data_size();

        //receivedMsg.Clear();
    } else if (ev == MG_EV_CLOSE) {
        setMsg((TMessage *) conn->user_data);
        dropFlag();
    }
}