#include "Client.h"
#include "../core/Logger.h"

namespace Ghurund {
    Client::Client(FunctionQueue &functionQueue):connectionState(ConnectionState::NOT_CONNECTED, &functionQueue), functionQueue(functionQueue) {
        this->functionQueue = functionQueue;
        connectionState.addEdge(ConnectionState::NOT_CONNECTED, ConnectionState::CONNECTING);
        connectionState.addEdge(ConnectionState::CONNECTING, ConnectionState::CONNECTED, [&]() {
            if(listener!=nullptr)
                listener->onConnected();
        });
        connectionState.addEdge(ConnectionState::CONNECTED, ConnectionState::DISCONNECTING);
        connectionState.addEdge(ConnectionState::DISCONNECTING, ConnectionState::NOT_CONNECTED, [&]() {
            safeDelete(&serverSocket);
            delete thread;  // called from that thread's thread
            thread = nullptr;
            if(listener!=nullptr)
                listener->onDisconnected();
        });
    };

    Client::~Client() {
        WSACleanup();
        if(listener!=nullptr)
            delete listener;
    };

    Status Client::init() {
        WSADATA w;    // used to store information about WinSock version

        if(WSAStartup(0x0202, &w)) { // there was an error
            Logger::log(_T("there was an error with WinSock initialization\n"));
            return Status::CALL_FAIL;
        }
        if(w.wVersion != 0x0202) { // wrong WinSock version!
            WSACleanup(); // unload ws2_32.dll
            Logger::log(_T("wrong WinSock version\n"));
            return Status::CALL_FAIL;
        }

        return Status::OK;
    }

    Status Client::connect(SocketProtocol protocol, unsigned short port, const tchar *address) {
        connectionState.setState(ConnectionState::CONNECTING);

        serverSocket = ghnew Socket();
        serverSocket->init(protocol, address, port);
        mySocket.init(serverSocket->Id, protocol, nullptr, 0);

        if(mySocket.bind()!=Status::OK) { // error
            int error = WSAGetLastError();
            Logger::log(_T("unable to bind to socket, error: %i\n"), error);
            WSACleanup();  // unload WinSock
            connectionState.setState(ConnectionState::NOT_CONNECTED);
            return Status::SOCKET;
        }

        // https://stackoverflow.com/questions/34242622/windows-udp-sockets-recvfrom-fails-with-error-10054
#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR, 12)
        BOOL bNewBehavior = FALSE;
        DWORD dwBytesReturned = 0;
        WSAIoctl(mySocket.Id, SIO_UDP_CONNRESET, &bNewBehavior, sizeof bNewBehavior, NULL, 0, &dwBytesReturned, NULL, NULL);

        connectionState.setState(ConnectionState::CONNECTED);

        thread = ghnew ClientThread(mySocket, listener, connectionState, *this);

        return Status::OK;
    }

    void Client::disconnect() {
        Logger::log(_T("disconnect\n"));
        /*char buffer[256];
        ::shutdown(socket.getId(),SD_SEND);
        recv(socket.getId(),buffer,256,0);*/
        connectionState.setState(ConnectionState::DISCONNECTING);
    }

}