#pragma once

#include "Common.h"
#include "MessageType.h"
#include "core/logging/Logger.h"
#include "core/string/TextUtils.h"

#include <WinSock2.h>
#include <CRC.h>

namespace Ghurund::Net {
#pragma pack(push, 1)
    struct Message {
        uint32_t crc;
        MessageTypeEnum type;
        uint8_t id = 0;
        uint8_t messageType = 0;

        bool isCrcValid(size_t messageSize) {
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

        void calculateCrc(size_t messageSize) {
            crc = CRC::Calculate((uint8_t*)this + sizeof(crc), messageSize - sizeof(crc), CRC::CRC_32());
        }

        bool operator==(const Message& other) const {
            return crc == other.crc && type == other.type && id == other.id && messageType == other.messageType;
        }

        String toString() const {
            return fmt::format(_T("{{ crc:{}, type:{}, id:{}, msg:{} }}"), crc, type, id, messageType).c_str();
        }
    };

    struct ConfirmationMessage:public Message {
        uint32_t confirmedCrc;

        ConfirmationMessage(uint8_t confirmedId, uint32_t confirmedCrc) {
            type = MessageTypeEnum::CONFIRM;
            this->id = confirmedId;
            this->confirmedCrc = confirmedCrc;
        }
    };

    struct RefreshMessage:public Message {
        RefreshMessage() {
            type = MessageTypeEnum::REFRESH;
        }
    };
#pragma pack(pop)

    enum class ClientMessageType:uint8_t {
        CONNECT, DISCONNECT, UPDATE, USER
    };

    enum class ServerMessageType:uint8_t {
        ACCEPT, REJECT, DISCONNECT, UPDATE, USER
    };

    static inline constexpr uint64_t RETRY_DELAY_MS = 2000;
    static inline constexpr uint64_t RETRY_COUNT = 5;
    static inline constexpr uint64_t REFRESH_PERIOD_MS = 2000;

    struct MessageItem {
        uint64_t time = 0;
        uint8_t retryCount = 0;
        size_t messageSize;
        uint8_t* messageData;

        MessageItem(uint8_t* messageData, size_t messageSize) {
            this->messageData = ghnew uint8_t[messageSize];
            memcpy(this->messageData, messageData, messageSize);
            this->messageSize = messageSize;
        }

        ~MessageItem() {
            delete[] messageData;
        }

        Message& getMessage() {
            return *(Ghurund::Net::Message*)messageData;
        }

        __declspec(property(get = getMessage)) Message& Message;

        String toString() const {
            return fmt::format(_T("{{ time:{}, retry:{}, size:{}, msg:{} }}"), time, retryCount, messageSize, ((Ghurund::Net::Message*)messageData)->toString()).c_str();
        }
    };
}