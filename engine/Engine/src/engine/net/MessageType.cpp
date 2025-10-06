#include "ghepch.h"

#include "MessageType.h"

namespace Ghurund::Net {
    const MessageType MessageType::RELIABLE = MessageType(MessageTypeEnum::RELIABLE, "RELIABLE");
    const MessageType MessageType::CONFIRM = MessageType(MessageTypeEnum::CONFIRM, "CONFIRM");
    const MessageType MessageType::UPDATE = MessageType(MessageTypeEnum::UPDATE, "UPDATE");
    const MessageType MessageType::REFRESH = MessageType(MessageTypeEnum::REFRESH, "REFRESH");
}