#pragma once

#include "Message.h"

namespace Ghurund::Net {
#pragma pack(push, 1)
    struct ClientMessage:public Message {
        //ClientMessageType messageType;
    };

    struct ClientConnectMessage:public ClientMessage {

        ClientConnectMessage() {
            type = MessageType::RELIABLE.Value;
            id = 0;
            messageType = (uint8_t)ClientMessageType::CONNECT;
        }
    };

    struct ClientDisconnectMessage:public ClientMessage {

        ClientDisconnectMessage() {
            type = MessageType::RELIABLE.Value;
            messageType = (uint8_t)ClientMessageType::DISCONNECT;
        }
    };

    struct ClientUpdateMessage:public ClientMessage {

        ClientUpdateMessage() {
            type = MessageType::UPDATE.Value;
            messageType = (uint8_t)ClientMessageType::UPDATE;
        }
    };
#pragma pack(pop)
}