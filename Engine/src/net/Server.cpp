#include "net/Server.h"
#include "core/logging/Logger.h"
#include "Ws2tcpip.h"

namespace Ghurund::Net {
    Status Server::handlePacket(uint8_t* data, uint32_t size, sockaddr_in& socketAddr) {
        Message* message = (Message*)data;
        ClientMessageType messageType = (ClientMessageType)message->type;
        if (messageType == ClientMessageType::CONNECT) {
            Socket* clientSocket = ghnew Socket();
            tchar address[16];
            InetNtop(AF_INET, &socketAddr.sin_addr.s_addr, (tchar*)address, 16);
            clientSocket->init(socket.Id, address, ntohs(socketAddr.sin_port));
            uint16_t id = clients.Size;
            if (!spareIds.Empty) {
                id = spareIds[spareIds.Size - 1];
                spareIds.removeAt(spareIds.Size - 1);
            }
            clients.set(id, ClientConnection(clientSocket));
        } else if (clients.contains(message->sender)) {
            if (messageType == ClientMessageType::DISCONNECT) {
                clients.remove(message->sender);
                spareIds.add(message->sender);
            } else if (messageType == ClientMessageType::UPDATE) {

            }
        }
        return Status::SOCKET_INV_PACKET;
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

    Status Server::receive() {
        int bytes;
        sockaddr_in socketAddr;
        memset(&socketAddr, 0, sizeof(socketAddr));
        int length = sizeof(socketAddr);
        while (true) {
            bytes = recvfrom(socket.getId(), (char*)buffer.Data, BUFFER_SIZE, 0, (sockaddr*)&socketAddr, &length);
            if (bytes == 0)
                break;
            if (bytes == SOCKET_ERROR) {
                int error = WSAGetLastError();
                if (error == WSAEWOULDBLOCK)
                    return Status::OK;
                return Logger::log(LogType::ERR0R, Status::SOCKET, _T("there was an error while receiving data"));
            }

            handlePacket(buffer.Data, bytes, socketAddr);
        }

        return Status::OK;
    }

    void Server::shutdown() {
        /*char buffer[256];
        for (size_t i = sockets.Size - 1; i >= 0; i--) {
            ::shutdown(sockets[i]->Id, SD_SEND);
            recv(sockets[i]->Id, buffer, 256, 0);
            closesocket(sockets[i]->Id);
            delete sockets[i];
            sockets.removeAt(i);
        }
        ::shutdown(socket.Id, 1);
        recv(socket.Id, buffer, 256, 0);
        closesocket(socket.Id);
        hosting = false;
        //if(hostThread)
            //delete hostThread;*/
    }

    Status Server::send(void* data, int size, unsigned int flags) {
        Status result = Status::OK;
        /*for (unsigned int i = 0; i < sockets.Size; i++) {
            result = socket.send(data, size, flags);
            if (result != Status::OK)
                return result;
        }*/
        return result;
    }

    Status Server::sendExcept(const Socket* socket, void* data, int size, unsigned int flags) {
        Status result = Status::OK;
        /*for (unsigned int i = 0; i < sockets.Size; i++) {
            if (socket->Id != sockets[i]->Id) {
                result = sockets[i]->send(data, size, flags);
                if (result != Status::OK)
                    return result;
            }
        }*/
        return result;
    }
}