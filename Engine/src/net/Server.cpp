#include "Server.h"
#include "ServerMessage.h"
#include "core/logging/Logger.h"

#include "Ws2tcpip.h"

namespace Ghurund::Net {
    Status Server::getMessageSize(void* data, size_t size, size_t& messageSize) {
        ClientMessage* clientMessage = ((ClientMessage*)data);
        ClientMessageType messageType = (ClientMessageType)clientMessage->messageType;
        if (messageType == ClientMessageType::CONNECT) {
            messageSize = sizeof(ClientConnectMessage);
            return Status::OK;
        } else if (messageType == ClientMessageType::DISCONNECT) {
            messageSize = sizeof(ClientDisconnectMessage);
            return Status::OK;
        }
        return Status::INV_PACKET;
    }

    Status Server::onReliableMessage(Connection& connection, Message& message) {
        ClientMessageType messageType = (ClientMessageType)((ClientMessage&)message).messageType;
        if (messageType == ClientMessageType::CONNECT) {
            if (onNewClientConnection(connection)) {
                connection.Connected = true;
                send(connection, ghnew ServerAcceptMessage(connection.Id));
            } else {
                connection.Connected = false;
                send(connection, ghnew ServerRejectMessage());
            }
            onConnected(connection);
            return Status::OK;
        } else if (messageType == ClientMessageType::DISCONNECT) {
            connections.remove(&connection);
            spareIds.add(connection.Id);
            onDisconnected(ClientDisconnection{ connection, DisconnectionReason::CLIENT });
            delete& connection;
            return Status::DISCONNECTED;
        }
        return Status::INV_PACKET;
    }

    Connection* Server::onNewConnection(const tchar* address, uint16_t port) {
        uint16_t id = (uint16_t)connections.Size;
        if (!spareIds.Empty) {
            id = spareIds[spareIds.Size - 1];
            spareIds.removeAt(spareIds.Size - 1);
        }
        Connection* connection = ghnew Connection();
        connection->Id = id;
        connection->Socket.init(address, port);
        return connection;
    }

    Server::~Server() {
        if (hosting)
            shutdown();
    }

    Status Server::host(uint16_t port) {
        socket.init((const tchar*)INADDR_ANY, port);

        if (socket.bind() != Status::OK)
            return Logger::log(LogType::ERR0R, Status::SOCKET, _T("unable to bind to socket"));

        hosting = true;

        return Status::OK;
    }

    void Server::shutdown() {
        hosting = false;
        connections.deleteItems();
        socket.close();
    }
}