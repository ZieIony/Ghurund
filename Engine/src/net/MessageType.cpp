#include "MessageType.h"

#include <tchar.h>

namespace Ghurund::Net {
    const MessageType MessageType::RELIABLE = MessageType(MessageTypeEnum::RELIABLE, _T("reliable"));
    const MessageType MessageType::CONFIRM = MessageType(MessageTypeEnum::CONFIRM, _T("confirm"));
    const MessageType MessageType::UPDATE = MessageType(MessageTypeEnum::UPDATE, _T("update"));
    const MessageType MessageType::REFRESH = MessageType(MessageTypeEnum::REFRESH, _T("refresh"));

    const EnumValues<MessageTypeEnum, MessageType> MessageType::VALUES = {
        &MessageType::RELIABLE,
        &MessageType::CONFIRM,
        &MessageType::UPDATE,
        &MessageType::REFRESH
    };
}