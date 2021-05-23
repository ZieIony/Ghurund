#include "ghpch.h"
#include "MessageType.h"

namespace Ghurund::Net {
    const MessageType MessageType::RELIABLE = MessageType(MessageTypeEnum::RELIABLE, "reliable");
    const MessageType MessageType::CONFIRM = MessageType(MessageTypeEnum::CONFIRM, "confirm");
    const MessageType MessageType::UPDATE = MessageType(MessageTypeEnum::UPDATE, "update");
    const MessageType MessageType::REFRESH = MessageType(MessageTypeEnum::REFRESH, "refresh");

    const EnumValues<MessageTypeEnum, MessageType> MessageType::VALUES = {
        &MessageType::RELIABLE,
        &MessageType::CONFIRM,
        &MessageType::UPDATE,
        &MessageType::REFRESH
    };
}