#include "ghpch.h"

#include "Client.h"

#include "ClientMessage.h"

namespace Ghurund::Net {
    Status Client::getMessageSize(void* data, size_t size, size_t& messageSize) {
        ServerMessage* serverMessage = ((ServerMessage*)data);
        ServerMessageType messageType = (ServerMessageType)serverMessage->messageType;
        if (messageType == ServerMessageType::ACCEPT) {
            messageSize = sizeof(ServerAcceptMessage);
            return Status::OK;
        } else if (messageType == ServerMessageType::REJECT) {
            messageSize = sizeof(ServerRejectMessage);
            return Status::OK;
        } else if (messageType == ServerMessageType::DISCONNECT) {
            messageSize = sizeof(ServerDisconnectMessage);
            return Status::OK;
        }
        return Status::INV_PACKET;
    }

    Status Client::onReliableMessage(Connection& connection, Message& message) {
        if (!Connected) {
            ServerMessageType messageType = (ServerMessageType)((ServerMessage&)message).messageType;
            if (messageType == ServerMessageType::ACCEPT) {
                id = ((ServerAcceptMessage&)message).clientId;
                connected = true;
                onConnected();
                return Status::OK;
            } else if (messageType == ServerMessageType::REJECT) {
                connected = false;
                connections.clear();
                return Status::OK;
            }
            return Status::INV_PACKET;
        } else {
            ServerMessageType messageType = (ServerMessageType)((ServerMessage&)message).messageType;
            if (messageType == ServerMessageType::DISCONNECT) {
                Logger::log(LogType::INFO, _T("disconnect\n"));
                socket.close();
                connected = false;
                onDisconnected(DisconnectionReason::SERVER);
                return Status::DISCONNECTED;
            }
            return Status::INV_PACKET;
        }
    }

    Client::~Client() {
        if (Connected)
            disconnect();
    };

    Status Client::connect(const tchar* address, uint16_t port) {
        socket.init(_T("localhost"));
        Connection* connection = ghnew Connection();
        connection->Socket.init(address, port);

        if (socket.bind() != Status::OK) {
            int error = WSAGetLastError();
            delete connection;
            auto text = std::format(_T("unable to bind to socket, error: {:d}\n"), error);
            return Logger::log(LogType::ERR0R, Status::SOCKET, text.c_str());
        }

        connections.add(connection);
        send(ghnew ClientConnectMessage());

        return Status::OK;
    }

    void Client::disconnect() {
        send(ghnew ClientDisconnectMessage());
    }
}