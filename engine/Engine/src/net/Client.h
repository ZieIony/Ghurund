#pragma once

#include "Connection.h"
#include "ServerMessage.h"
#include "ReliableUDP.h"
#include "core/Event.h"
#include "core/collection/List.h"
#include "core/state/StateMachine.h"

#include <thread>

namespace Ghurund::Net {
    class Client:public ReliableUDP {
    protected:
        uint16_t id = 0;

        bool connected = false;
        Event<Client> onConnected = *this;
        Event<Client, DisconnectionReason> onDisconnected = *this;

        virtual Status getMessageSize(void* data, size_t size, size_t& messageSize) override;

        virtual Status onUpdateMessage(Connection& connection, Message& message) override {
            return Status::INV_PACKET;
        }

        virtual Status onReliableMessage(Connection& connection, Message& message) override;

        virtual void onConnectionLost(Connection& connection) override {
            connected = false;
            onDisconnected(DisconnectionReason::TIMEOUT);
        }

    public:
        ~Client();

        Status connect(const tchar* address, uint16_t port);

        void disconnect();

        inline bool isConnected() const {
            return connected;
        }

        __declspec(property(get = isConnected)) bool Connected;

        inline const Ghurund::Net::Socket& getSocket()const {
            return socket;
        }

        __declspec(property(get = getSocket)) Ghurund::Net::Socket& Socket;

        inline Event<Client>& getOnConnected() {
            return onConnected;
        }

        __declspec(property(get = getOnConnected)) Event<Client>& OnConnected;

        inline Event<Client, DisconnectionReason>& getOnDisconnected() {
            return onDisconnected;
        }

        __declspec(property(get = getOnDisconnected)) Event<Client, DisconnectionReason>& OnDisconnected;

        template<typename MessageType>
        Status send(MessageType* message) {
            return __super::send(*connections[0], message);
        }
    };
}