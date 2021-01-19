#pragma once

#include "Connection.h"
#include "ClientMessage.h"
#include "ServerMessage.h"
#include "ReliableUDP.h"
#include "core/Buffer.h"
#include "core/Event.h"
#include "core/collection/List.h"
#include "core/collection/Map.h"

namespace Ghurund::Net {
    struct ClientDisconnection {
        Connection& connection;
        DisconnectionReason reason;
    };

    class Server:public ReliableUDP {
    private:
        List<uint16_t> spareIds;

        bool hosting = false;

        Event<Server, Connection> onConnected = *this;
        Event<Server, ClientDisconnection> onDisconnected = *this;
        Event<Server, Connection> onNewClientConnection = *this;

        virtual Status getMessageSize(void* data, size_t size, size_t& messageSize) override;

        virtual Status onUpdateMessage(Connection& connection, Message& message) override {
            return Status::INV_PACKET;
        }

        virtual Status onReliableMessage(Connection& connection, Message& message) override;

        virtual Connection* onNewConnection(const tchar* address, uint16_t port);

        virtual void onConnectionLost(Connection& connection) override {
            onDisconnected(ClientDisconnection{ connection, DisconnectionReason::TIMEOUT });
        }

    public:
        ~Server();

        Status host(uint16_t port = 0);

        void shutdown();

        inline bool isHosting() {
            return hosting;
        }

        __declspec(property(get = isHosting)) bool Hosting;

        inline Event<Server, Connection>& getOnConnected() {
            return onConnected;
        }

        __declspec(property(get = getOnConnected)) Event<Server, Connection>& OnConnected;

        inline Event<Server, ClientDisconnection>& getOnDisconnected() {
            return onDisconnected;
        }

        __declspec(property(get = getOnDisconnected)) Event<Server, ClientDisconnection>& OnDisconnected;

        inline Event<Server, Connection>& getOnNewClientConnection() {
            return onNewClientConnection;
        }

        __declspec(property(get = getOnNewClientConnection)) Event<Server, Connection>& OnNewClientConnection;

        inline List<Connection*>& getConnections() {
            return connections;
        }

        __declspec(property(get = getConnections)) List<Connection*>& Connections;
    };
}