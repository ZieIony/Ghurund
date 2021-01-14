#include "Client.h"
#include "core/logging/Logger.h"

namespace Ghurund::Net {
    Client::Client():connectionState(ConnectionState::NOT_CONNECTED) {
        connectionState.addEdge(ConnectionState::NOT_CONNECTED, ConnectionState::CONNECTING);
        connectionState.addEdge(ConnectionState::CONNECTING, ConnectionState::CONNECTED, [&] {
            if (listener != nullptr)
                listener->onConnected();
        });
        connectionState.addEdge(ConnectionState::CONNECTED, ConnectionState::DISCONNECTING);
        connectionState.addEdge(ConnectionState::DISCONNECTING, ConnectionState::NOT_CONNECTED, [&] {
            delete serverSocket;
            serverSocket = nullptr;
            if (listener != nullptr)
                listener->onDisconnected();
        });
    };

    Client::~Client() {
        if (Connected)
            disconnect();
        if (listener != nullptr)
            delete listener;
    };

    Status Client::connect(const tchar* address, uint16_t port) {
        /*connectionState.setState(ConnectionState::CONNECTING);

        serverSocket = ghnew Ghurund::Net::Socket();
        serverSocket->init(type, address, port);
        mySocket.init(serverSocket->Id, type, nullptr, 0);

        if (mySocket.bind() != Status::OK) {
            int error = WSAGetLastError();
            connectionState.setState(ConnectionState::NOT_CONNECTED);
            return Logger::log(LogType::ERR0R, Status::SOCKET, _T("unable to bind to socket, error: {:d}\n"), error);
        }

        // https://stackoverflow.com/questions/34242622/windows-udp-sockets-recvfrom-fails-with-error-10054
#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)
        BOOL bNewBehavior = FALSE;
        DWORD dwBytesReturned = 0;
        WSAIoctl(mySocket.Id, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);

        connectionState.setState(ConnectionState::CONNECTED);*/

        return Status::OK;
    }

    void Client::disconnect() {
        Logger::log(LogType::INFO, _T("disconnect\n"));
        char buffer[256];
        ::shutdown(mySocket.Id, SD_SEND);
        recv(serverSocket->Id, buffer, 256, 0);
        connectionState.setState(ConnectionState::DISCONNECTING);
    }

}