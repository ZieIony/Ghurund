#include "Socket.h"

namespace Ghurund {
    Status Ghurund::Socket::init(::SOCKET id, SocketProtocol protocol, const tchar* address, unsigned short port) {
        this->id = id;
        this->protocol = protocol;
        if (id == INVALID_SOCKET)
            return Logger::log(LogType::ERR0R, Status::INV_PARAM, _T("socket is invalid"));

        this->port = port;
        safeCopyStr(&this->address, address);

        memset(&addressStruct, 0, sizeof addressStruct);

#ifdef UNICODE
        struct addrinfoW* result = nullptr;
        struct addrinfoW* ptr = nullptr;
        struct addrinfoW hints;
#else
        struct addrinfo* result = nullptr;
        struct addrinfo* ptr = nullptr;
        struct addrinfo hints;
#endif

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = (int)protocol;
        hints.ai_protocol = protocol == SocketProtocol::UDP ? IPPROTO_UDP : IPPROTO_TCP;

        tchar portStr[10];
        _stprintf_s(portStr, 10, _T("%i"), port);
        int dwRetval = GetAddrInfo(address, portStr, &hints, &result);
        if (dwRetval != 0)
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Failed to get address info"));

        for (ptr = result; ptr != nullptr; ptr = ptr->ai_next) {
            switch (ptr->ai_family) {
            case AF_INET:
                addressStruct = ghnew sockaddr_in();
                memcpy(addressStruct, ptr->ai_addr, sizeof(sockaddr_in));
                break;
            case AF_INET6:
                addressStruct6 = ghnew sockaddr_in6();
                memcpy(addressStruct6, ptr->ai_addr, sizeof(sockaddr_in6));
                break;
            }
        }

        FreeAddrInfo(result);

        dataBuffer.buf = ghnew char[BUFFER_SIZE];
        dataBuffer.len = BUFFER_SIZE;

        return Status::OK;
    }

    sockaddr* Socket::getAddressStruct() const {
        if (addressStruct6 != nullptr)
            return (sockaddr*)addressStruct6;
        return (sockaddr*)addressStruct;
    }

    Status Socket::send(void* data, size_t size, unsigned int flags) const {
        if (addressStruct6 != nullptr)
            return ::sendto(id, (char*)data, size, flags, (sockaddr*)addressStruct6, sizeof(sockaddr_in6)) == SOCKET_ERROR ? Status::SOCKET : Status::OK;
        return ::sendto(id, (char*)data, size, flags, (sockaddr*)addressStruct, sizeof(sockaddr_in)) == SOCKET_ERROR ? Status::SOCKET : Status::OK;
    }

    Status Socket::receive(void** data, size_t * size) {
        int bytes;
        sockaddr socketAddr;
        memset(&socketAddr, 0, sizeof(socketAddr));
        int length = sizeof(socketAddr);
        if ((bytes = recvfrom(id, dataBuffer.buf, dataBuffer.len, 0, &socketAddr, &length)) == SOCKET_ERROR) {
            int error = WSAGetLastError();
            *data = nullptr;
            *size = 0;
            return Logger::log(LogType::ERR0R, Status::SOCKET, _T("there was an error while receiving data"));
        }

        if (data != nullptr) {
            *data = ghnew char[bytes];
            memcpy(*data, dataBuffer.buf, bytes);
        }
        if (size != nullptr)
            * size = bytes;

        return Status::OK;
    }

    Status Socket::bind() {
        int result;
        if (addressStruct6 != nullptr) {
            result = ::bind(id, (sockaddr*)addressStruct6, sizeof(sockaddr_in6));
        } else {
            result = ::bind(id, (sockaddr*)addressStruct, sizeof(sockaddr_in));
        }
        if (result == SOCKET_ERROR)
            return Status::SOCKET;

        return select();
    }

    Status Socket::select() {
        eventHandle = WSACreateEvent();
        if (SOCKET_ERROR == WSAEventSelect(id, eventHandle, FD_ALL_EVENTS)) {
            int error = WSAGetLastError();
            return Logger::log(LogType::ERR0R, Status::SOCKET, _T("unable to register socket for async notification, error: %i"), error);
        }
        return Status::OK;
    }

    Socket* Socket::accept() const {
        Socket* acceptedSocket = new Socket();
        int size = addressStruct6 != nullptr ? sizeof(sockaddr_in6) : sizeof(sockaddr_in);
        ::SOCKET id = ::accept(this->id, getAddressStruct(), &size);
        int flag = 1;
        if (acceptedSocket->init(id, protocol, address, port) != Status::OK)
            goto error;

        if (acceptedSocket->select() != Status::OK)
            goto error;

        return acceptedSocket;

    error:
        delete acceptedSocket;
        return nullptr;
    }
}