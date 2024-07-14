#include "ghpch.h"

#include "Client.h"

#include "ClientMessage.h"

namespace Ghurund::Net {
    size_t Client::getMessageSize(void* data, size_t size) {
        ServerMessage* serverMessage = ((ServerMessage*)data);
        ServerMessageType messageType = (ServerMessageType)serverMessage->messageType;
        if (messageType == ServerMessageType::ACCEPT) {
            return sizeof(ServerAcceptMessage);
        } else if (messageType == ServerMessageType::REJECT) {
            return sizeof(ServerRejectMessage);
        } else if (messageType == ServerMessageType::DISCONNECT) {
            return sizeof(ServerDisconnectMessage);
        }
        throw InvalidDataException();
    }

    void Client::onReliableMessage(SharedPointer<Connection>& connection, Message& message) {
        if (!Connected) {
            ServerMessageType messageType = (ServerMessageType)((ServerMessage&)message).messageType;
            if (messageType == ServerMessageType::ACCEPT) {
                id = ((ServerAcceptMessage&)message).clientId;
                connected = true;
                onConnected();
                return;
            } else if (messageType == ServerMessageType::REJECT) {
                connected = false;
                connections.clear();
                return;
            }
        } else {
            ServerMessageType messageType = (ServerMessageType)((ServerMessage&)message).messageType;
            if (messageType == ServerMessageType::DISCONNECT) {
                Logger::log(LogType::INFO, _T("disconnect\n"));
                socket.close();
                connected = false;
                onDisconnected(DisconnectionReason::SERVER);
                return;
            }
        }
        throw InvalidDataException();
    }

    Client::~Client() {
        if (Connected)
            disconnect();
    };

    void Client::connect(const tchar* address, uint16_t port) {
        socket.init(String(_T("localhost")));
        SharedPointer<Connection> connection = makeShared<Connection>();
        connection->Socket.init(address, port);
        socket.bind();
        connections.add(connection);
        send(ghnew ClientConnectMessage());
    }

    void Client::disconnect() {
        send(ghnew ClientDisconnectMessage());
    }
}