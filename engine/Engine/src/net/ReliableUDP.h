#pragma once

#include "Common.h"
#include "Status.h"
#include "Message.h"
#include "Socket.h"
#include "Connection.h"
#include "core/Noncopyable.h"
#include "core/collection/List.h"

#include <CRC.h>

namespace Ghurund::Net {
    class ReliableUDP:public Noncopyable {
    private:
        uint8_t reliableId = 0, updateId = 0;
        static constexpr uint32_t BUFFER_SIZE = 65535;
        Buffer buffer = Buffer(BUFFER_SIZE);

        void confirmMessage(Connection& connection, Message& message);
        void answerRefresh(Connection& connection);
        bool isReceivedDuplicate(Connection& connection, uint8_t* messageData);

        void processUpdateMessage(Connection& connection, uint8_t* messageData);
        Status processReliableMessage(Connection& connection, uint8_t* messageData, size_t messageSize);
        void processConfirmMessage(Connection& connection, uint8_t* messageData, uint64_t time);
        void processRefreshMessage(Connection& connection, uint64_t time);
        Status processMessages(Connection& connection, size_t size, uint64_t time);
        Status processMessage(Connection& connection, uint8_t* messageData, size_t messageSize, uint64_t time);

        Status send(Connection& connection, Message* message, size_t messageSize);

        void retryMessages(Connection* connection, uint64_t time);

    protected:
        Socket socket;
        List<Connection*> connections;

        virtual Status getMessageSize(void* data, size_t size, size_t& messageSize) {
            return Status::INV_PACKET;
        }

        virtual Status onUpdateMessage(Connection& connection, Message& message) {
            return Status::INV_PACKET;
        }

        virtual Status onReliableMessage(Connection& connection, Message& message) {
            return Status::INV_PACKET;
        }

        virtual Connection* onNewConnection(const tchar* address, uint16_t port) {
            return nullptr;
        }

        virtual void onConnectionLost(Connection& connection) {}

    public:
        Status update(uint64_t time);

        template<typename MessageType>
        Status send(Connection& connection, MessageType* message) {
            return send(connection, message, sizeof(MessageType));
        }
    };
}