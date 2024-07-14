#pragma once

#include "Connection.h"
#include "ClientMessage.h"
#include "ServerMessage.h"
#include "ReliableUDP.h"
#include "core/Buffer.h"
#include "core/Event.h"
#include "core/collection/List.h"
#include "core/Exceptions.h"

namespace Ghurund::Net {
    struct ClientDisconnection {
        Connection& connection;
        DisconnectionReason reason;
    };

    class Server:public ReliableUDP {
    private:
        List<uint16_t> spareIds;

        bool hosting = false;

        virtual size_t getMessageSize(void* data, size_t size) override;

        virtual void onUpdateMessage(SharedPointer<Connection>& connection, Message& message) override {
            throw NotImplementedException();
        }

        virtual void onReliableMessage(SharedPointer<Connection>& connection, Message& message) override;

        virtual SharedPointer<Connection> onNewConnection(const String& address, uint16_t port);

        virtual void onConnectionLost(Connection& connection) override {
            onDisconnected(ClientDisconnection{ connection, DisconnectionReason::TIMEOUT });
        }

    public:
        Event<Server, Connection> onConnected = *this;
        Event<Server, ClientDisconnection> onDisconnected = *this;
        Event<Server, Connection> onNewClientConnection = *this;

        ~Server();

        void host(uint16_t port = 0);

        void shutdown();

        inline bool isHosting() {
            return hosting;
        }

        __declspec(property(get = isHosting)) bool Hosting;

        inline List<SharedPointer<Connection>>& getConnections() {
            return connections;
        }

        __declspec(property(get = getConnections)) List<SharedPointer<Connection>>& Connections;
    };
}