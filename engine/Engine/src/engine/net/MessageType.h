#pragma once

#include "core/Enum.h"

namespace Ghurund::Net {
    using namespace Ghurund::Core;

    enum class MessageTypeEnum:uint8_t {
        RELIABLE, CONFIRM, UPDATE, REFRESH
    };

    class MessageType:public Enum<MessageTypeEnum, MessageType> {
    public:
        static const MessageType RELIABLE, CONFIRM, UPDATE, REFRESH;

        MessageType(MessageTypeEnum value, const char* name):Enum<MessageTypeEnum, MessageType>(value, name) {}
    };
}