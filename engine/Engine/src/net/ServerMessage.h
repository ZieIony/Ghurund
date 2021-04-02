#pragma once

#include "Message.h"

namespace Ghurund::Net {
#pragma pack(push, 1)
    struct ServerMessage:public Message {
        //ServerMessageType messageType;
    };

    struct ServerAcceptMessage:public ServerMessage {
        uint16_t clientId;

        ServerAcceptMessage(uint16_t clientId) {
            type = MessageType::RELIABLE.Value;
            id = 0;
            this->clientId = clientId;
            messageType = (uint8_t)ServerMessageType::ACCEPT;
        }
    };

    struct ServerRejectMessage:public ServerMessage {

        ServerRejectMessage() {
            type = MessageType::RELIABLE.Value;
            id = 0;
            messageType = (uint8_t)ServerMessageType::REJECT;
        }
    };

    struct ServerDisconnectMessage:public ServerMessage {

        ServerDisconnectMessage() {
            type = MessageType::RELIABLE.Value;
            messageType = (uint8_t)ServerMessageType::DISCONNECT;
        }
    };

    struct ServerUpdateMessage:public Message {
        ServerMessageType messageType = ServerMessageType::UPDATE;

        ServerUpdateMessage() {
            type = MessageType::UPDATE.Value;
        }
    };
#pragma pack(pop)
}