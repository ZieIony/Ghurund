#pragma once

#include "Socket.h"
#include "Message.h"
#include "core/collection/List.h"

namespace Ghurund::Net {
    using namespace Ghurund::Core;

    class Connection {
    private:
        Socket socket;
        List<MessageItem*> messagesReceived;
        List<MessageItem*> messagesSent;
        uint8_t otherReliableId = 0, otherUpdateId = 0;
        uint64_t rtt = 0;
        uint64_t lastSeen = 0;
        uint16_t id = 0;
        bool connected = false;

    public:
        inline uint16_t getId() const {
            return id;
        }

        inline void setId(uint16_t id) {
            this->id = id;
        }

        __declspec(property(get = getId, put = setId)) uint16_t Id;

        inline bool isConnected() const {
            return connected;
        }

        inline void setConnected(bool connected) {
            this->connected = connected;
        }

        __declspec(property(get = isConnected, put = setConnected)) bool Connected;

        inline Socket& getSocket() {
            return socket;
        }

        __declspec(property(get = getSocket)) Socket& Socket;

        inline List<MessageItem*>& getMessagesSent() {
            return messagesSent;
        }

        __declspec(property(get = getMessagesSent)) List<MessageItem*>& MessagesSent;

        inline List<MessageItem*>& getMessagesReceived() {
            return messagesReceived;
        }

        __declspec(property(get = getMessagesReceived)) List<MessageItem*>& MessagesReceived;

        inline uint8_t getReliableId() const {
            return otherReliableId;
        }

        inline void setReliableId(uint8_t id) {
            otherReliableId = id;
        }

        __declspec(property(get = getReliableId, put = setReliableId)) uint8_t ReliableId;

        inline uint8_t getUpdateId() const {
            return otherUpdateId;
        }

        inline void setUpdateId(uint8_t id) {
            otherUpdateId = id;
        }

        __declspec(property(get = getUpdateId, put = setUpdateId)) uint8_t UpdateId;

        inline uint64_t getRtt() const {
            return rtt;
        }

        inline void setRtt(uint64_t rtt) {
            this->rtt = rtt;
        }

        __declspec(property(get = getRtt, put = setRtt)) uint64_t Rtt;

        inline uint64_t getLastSeen() const {
            return lastSeen;
        }

        inline void setLastSeen(uint64_t lastSeen) {
            this->lastSeen = lastSeen;
        }

        __declspec(property(get = getLastSeen, put = setLastSeen)) uint64_t LastSeen;
    };

    enum class DisconnectionReason {
        CLIENT, SERVER, TIMEOUT
    };
}