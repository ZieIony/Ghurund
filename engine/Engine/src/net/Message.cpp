#include "ghpch.h"

#include "Message.h"

#include "core/logging/Logger.h"
#include <CRC.h>

namespace Ghurund::Net {
    bool Message::isCrcValid(size_t messageSize) {
        uint32_t crc = CRC::Calculate((uint8_t*)this + sizeof(crc), messageSize - sizeof(crc), CRC::CRC_32());
        bool valid = this->crc == crc;
#ifdef _DEBUG
        if (!valid) {
            auto text = std::format(_T("invalid crc {} vs id:{}, type:{}, crc:{}, msg:{}\n"), crc, id, MessageType::VALUES[type].Name, crc, messageType);
            Logger::log(LogType::INFO, text.c_str());
        }
#endif
        return valid;
    }

    void Message::calculateCrc(size_t messageSize) {
        crc = CRC::Calculate((uint8_t*)this + sizeof(crc), messageSize - sizeof(crc), CRC::CRC_32());
    }
    
    String Message::toString() const {
        String name = convertText<char, tchar>(MessageType::VALUES[type].Name);
        return std::format(_T("{{ crc:{}, type:{}, id:{}, msg:{} }}"), crc, name, id, messageType).c_str();
    }
    
    String MessageItem::toString() const {
        return std::format(_T("{{ time:{}, retry:{}, size:{}, msg:{} }}"), time, retryCount, messageSize, ((Ghurund::Net::Message*)messageData)->toString()).c_str();
    }
}