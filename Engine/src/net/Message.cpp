#include "Message.h"

#include "core/logging/Formatter.h"
#include "core/logging/Logger.h"

namespace Ghurund::Net {
    bool Message::isCrcValid(size_t messageSize) {
        uint32_t crc = CRC::Calculate((uint8_t*)this + sizeof(crc), messageSize - sizeof(crc), CRC::CRC_32());
        bool valid = this->crc == crc;
#ifdef _DEBUG
        if (!valid) {
            tchar* name = toTchar(MessageType::VALUES[type].Name);
            Logger::log(LogType::INFO, _T("invalid crc {} vs id:{}, type:{}, crc:{}, msg:{}\n"), crc, id, name, crc, messageType);
            delete[] name;
        }
#endif
        return valid;
    }
    
    String Message::toString() const {
        return fmt::format(_T("{{ crc:{}, type:{}, id:{}, msg:{} }}"), crc, type, id, messageType).c_str();
    }
    
    String MessageItem::toString() const {
        return fmt::format(_T("{{ time:{}, retry:{}, size:{}, msg:{} }}"), time, retryCount, messageSize, ((Ghurund::Net::Message*)messageData)->toString()).c_str();
    }
}