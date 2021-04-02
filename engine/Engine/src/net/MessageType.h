#pragma once

#include "core/Enum.h"

namespace Ghurund::Net {

    enum class MessageTypeEnum:uint8_t {
        RELIABLE, CONFIRM, UPDATE, REFRESH
    };

    class MessageType:public Enum<MessageTypeEnum, MessageType> {
    public:
        static const MessageType RELIABLE, CONFIRM, UPDATE, REFRESH;

        static const EnumValues<MessageTypeEnum, MessageType> VALUES;

        MessageType(MessageTypeEnum value, const char* name):Enum<MessageTypeEnum, MessageType>(value, name) {}
    };
}