#include "net/Server.h"
#include "core/Logger.h"
#include "Ws2tcpip.h"

namespace Ghurund {
    Server::Server() {
        hosting = false;
        //hostThread=0;
    }

    Server::~Server() {
        if(hosting)
            shutdown();//TODO poprawi? wszystkie p?tle sprz?taj?ce
        WSACleanup();
    }

    Status Server::init() {
        WSADATA w;    // used to store information about WinSock version
        int error = WSAStartup(0x0202, &w);   // Fill in w

        if(error) { // there was an error
            Logger::log(_T("there was an error with WinSock initialization"));
            return Status::CALL_FAIL;
        }
        if(w.wVersion != 0x0202) { // wrong WinSock version!
            WSACleanup(); // unload ws2_32.dll
            Logger::log(_T("wrong WinSock version"));
            return Status::CALL_FAIL;
        }

        return Status::OK;
    }
    
    Status Server::host(SocketProtocol protocol, unsigned short port) {
        socket.init(protocol, INADDR_ANY, port);

        if(socket.bind()!=Status::OK) { // error
            WSACleanup();  // unload WinSock
            Logger::log(_T("unable to bind to socket"));         // quit
            return Status::SOCKET;
        }

        hosting = true;

        return Status::OK;
    }

    /*
    Status Server::receive(Socket **senderSocket, void **buffer, int *size) {
        int bytes;
        sockaddr_in socketAddr;
        memset(&socketAddr, 0, sizeof(socketAddr));
        int length = sizeof(socketAddr);
        if((bytes = recvfrom(socket.getId(), this->buffer, BUFFER_SIZE, 0, (sockaddr*)&socketAddr, &length))==SOCKET_ERROR) {
            int error = WSAGetLastError();
            *senderSocket = nullptr;
            *buffer = nullptr;
            *size = 0;
            Logger::log(_T("there was an error while receiving data"));
            return Status::SOCKET;
        }

        *buffer = ghnew char[bytes];
        memcpy(*buffer, this->buffer, bytes);
        *size = bytes;

/*        for(unsigned int i = 0; i<sockets.getSize(); i++) {
            if(sockets.get(i)->addressStruct.sin_addr.s_addr==socketAddr.sin_addr.s_addr) {
                *senderSocket = sockets.get(i);
                return Status::OK;
            }
        }*/
    /*
        Socket *socket2 = new Socket();
        tchar address[16];
        InetNtop(AF_INET, &socketAddr.sin_addr.s_addr, (tchar*)address, 16);
        socket2->init(socket.getId(), address, ntohs(socketAddr.sin_port));
        sockets.add(socket2);
        *senderSocket = socket2;

        return Status::OK;
    }*/

    void Server::shutdown() {
        char buffer[256];
        for(size_t i = sockets.getSize()-1; i>=0; i--) {
            ::shutdown(sockets.get(i)->getId(), SD_SEND);
            recv(sockets.get(i)->getId(), buffer, 256, 0);
            closesocket(sockets.get(i)->getId());
            delete sockets.get(i);
            sockets.remove(i);
        }
        ::shutdown(socket.getId(), 1);
        recv(socket.getId(), buffer, 256, 0);
        closesocket(socket.getId());
        hosting = false;
        //if(hostThread)
            //delete hostThread;
    }

    inline Status Server::send(void * data, int size, unsigned int flags) {
        Status result = Status::OK;
        for(unsigned int i = 0; i<sockets.getSize(); i++) {
            result = socket.send(data, size, flags);
            if(result != Status::OK)
                return result;
        }
        return result;
    }

    inline Status Server::sendExcept(const Socket * socket, void * data, int size, unsigned int flags) {
        Status result = Status::OK;
        for(unsigned int i = 0; i<sockets.getSize(); i++) {
            if(socket->getId()!=sockets.get(i)->getId()) {
                result = sockets.get(i)->send(data, size, flags);
                if(result != Status::OK)
                    return result;
            }
        }
        return result;
    }

    Status Server::accept() {
        Socket *clientSocket = socket.accept();
        if(clientSocket==nullptr) {
            Logger::log(_T("Failed to accept a connection\n"));
            return Status::SOCKET;
        }

        sockets.add(clientSocket);
        return Status::OK;
    }

}