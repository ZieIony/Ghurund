#pragma once

#include "Common.h"
#include "Connection.h"
#include "Message.h"
#include "Socket.h"
#include "core/Buffer.h"
#include "core/Exceptions.h"
#include "core/Noncopyable.h"
#include "core/SharedPointer.h"
#include "core/collection/List.h"

namespace Ghurund::Net {
    class ReliableUDP:public Noncopyable {
    private:
        uint8_t reliableId = 0, updateId = 0;
        static constexpr uint32_t BUFFER_SIZE = 65535;
        Buffer buffer = Buffer(BUFFER_SIZE);

        void confirmMessage(SharedPointer<Connection>& connection, Message& message);
        void answerRefresh(Connection& connection);
        bool isReceivedDuplicate(SharedPointer<Connection>& connection, uint8_t* messageData);

        void processUpdateMessage(SharedPointer<Connection>& connection, uint8_t* messageData);
        void processReliableMessage(SharedPointer<Connection>& connection, uint8_t* messageData, size_t messageSize);
        void processConfirmMessage(SharedPointer<Connection>& connection, uint8_t* messageData, uint64_t time);
        void processRefreshMessage(Connection& connection, uint64_t time);
        void processMessages(SharedPointer<Connection>& connection, size_t size, uint64_t time);
        void processMessage(SharedPointer<Connection>& connection, uint8_t* messageData, size_t messageSize, uint64_t time);

        void send(Connection& connection, Message* message, size_t messageSize);

        void retryMessages(SharedPointer<Connection>& connection, uint64_t time);

    protected:
        Socket socket;
        List<SharedPointer<Connection>> connections;

        virtual size_t getMessageSize(void* data, size_t size) {
            throw NotImplementedException();
        }

        virtual void onUpdateMessage(SharedPointer<Connection>& connection, Message& message) {
            throw NotImplementedException();
        }

        virtual void onReliableMessage(SharedPointer<Connection>& connection, Message& message) {
            throw NotImplementedException();
        }

        virtual SharedPointer<Connection> onNewConnection(const tchar* address, uint16_t port) {
            return makeShared<Connection>();
        }

        virtual void onConnectionLost(Connection& connection) {}

    public:
        void update(uint64_t time);

        template<typename MessageType>
        void send(Connection& connection, MessageType* message) {
            send(connection, message, sizeof(MessageType));
        }
    };
}