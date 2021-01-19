#pragma once

#include "net/ClientMessage.h"

namespace Messenger {
    struct TextMessage:public Ghurund::Net::ClientMessage {
        TextMessage() {
            type = Ghurund::Net::MessageType::RELIABLE.Value;
            messageType = (uint8_t)Ghurund::Net::ClientMessageType::USER;
        }
    };
}