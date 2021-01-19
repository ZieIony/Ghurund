#include "Socket.h"

#include "core/logging/Logger.h"

namespace Ghurund::Net {
    Status Socket::init(::SOCKET id, const tchar* address, uint16_t port) {
        this->id = id;
        if (id == INVALID_SOCKET)
            return Logger::log(LogType::ERR0R, Status::INV_PARAM, _T("socket is invalid"));

        u_long enabled = 1;
        ioctlsocket(id, FIONBIO, &enabled);
        // Any calls to recvfrom made when there are no packets to consume, will return SOCKET_ERROR, and WSAGetLastError will return WSAEWOULDBLOCK

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
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;

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

        return Status::OK;
    }

    Status Socket::send(Socket& socket, const void* data, size_t size, unsigned int flags) const {
        int result = 0;
        if (addressStruct6 != nullptr) {
            result = ::sendto(id, (const char*)data, (int)size, flags, socket.AddressStruct, sizeof(sockaddr_in6));
        } else {
            result = ::sendto(id, (const char*)data, (int)size, flags, socket.AddressStruct, sizeof(sockaddr_in));
        }
        return result == SOCKET_ERROR ? Status::SOCKET : Status::OK;
    }

    Status Socket::receive(void* data, size_t capacity, size_t& size, sockaddr& socketAddr) {
        int bytes;
        memset(&socketAddr, 0, sizeof(socketAddr));
        int length = sizeof(socketAddr);
        if ((bytes = recvfrom(id, (char*)data, capacity, 0, &socketAddr, &length)) == SOCKET_ERROR) {
            size = 0;
            int error = WSAGetLastError();
            if (error == WSAEWOULDBLOCK)
                return Status::OK;
            return Logger::log(LogType::ERR0R, Status::SOCKET, _T("there was an error while receiving data\n"));
        }
        size = bytes;

        return Status::OK;
    }

    Status Socket::bind() {
        int result;
        if (addressStruct6 != nullptr) {
            result = ::bind(id, (sockaddr*)addressStruct6, sizeof(sockaddr_in6));
        } else {
            result = ::bind(id, (sockaddr*)addressStruct, sizeof(sockaddr_in));
        }
        if (port == 0) {
            sockaddr addr;
            int nameLen = 0;
            getsockname(id, &addr, &nameLen);
            port = addr.sa_family;
        }
        if (result == SOCKET_ERROR)
            return Status::SOCKET;

        return Status::OK;
    }
    
    void Socket::close() {
        if (id == INVALID_SOCKET)
            return;
        ::shutdown(id, SD_SEND);
        while (true) {
            char buffer[256];
            int bytes = recvfrom(id, buffer, 256, 0, nullptr, 0);
            if (bytes == SOCKET_ERROR || bytes == 0)
                break;
        }
        closesocket(id);
        id = INVALID_SOCKET;
        delete[] address;
        address = nullptr;
        delete addressStruct;
        addressStruct = nullptr;
        delete addressStruct6;
        addressStruct6 = nullptr;
    }
}