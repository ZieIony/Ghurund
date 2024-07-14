#include "ghpch.h"
#include "Socket.h"

#include "core/Exceptions.h"
#include "core/Finally.h"
#include "core/logging/Logger.h"

namespace Ghurund::Net {
    void Socket::init(::SOCKET id, const String& address, uint16_t port) {
        this->id = id;
        if (id == INVALID_SOCKET) {
            Logger::log(LogType::ERR0R, _T("socket is invalid"));
            throw InvalidParamException();
        }

        u_long enabled = 1;
        ioctlsocket(id, FIONBIO, &enabled);
        // Any calls to recvfrom made when there are no packets to consume, will return SOCKET_ERROR, and WSAGetLastError will return WSAEWOULDBLOCK

        this->port = port;
        this->address = address;

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
        Finally f = [&] {
            FreeAddrInfo(result);
        };

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_DGRAM;
        hints.ai_protocol = IPPROTO_UDP;

        tchar portStr[10];
        _stprintf_s(portStr, 10, _T("%i"), port);
        int dwRetval = GetAddrInfo(address.Data, portStr, &hints, &result);
        if (dwRetval != 0) {
            Logger::log(LogType::ERR0R, _T("Failed to get address info"));
            throw CallFailedException();
        }

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
    }

    void Socket::send(Socket& socket, const void* data, size_t size, unsigned int flags) const {
        int result = 0;
        if (addressStruct6 != nullptr) {
            result = ::sendto(id, (const char*)data, (int)size, flags, socket.AddressStruct, sizeof(sockaddr_in6));
        } else {
            result = ::sendto(id, (const char*)data, (int)size, flags, socket.AddressStruct, sizeof(sockaddr_in));
        }
        if(result == SOCKET_ERROR)
            throw CallFailedException();
    }

    void Socket::receive(void* data, size_t capacity, size_t& size, sockaddr& socketAddr) {
        int bytes;
        memset(&socketAddr, 0, sizeof(socketAddr));
        int length = sizeof(socketAddr);
        if ((bytes = recvfrom(id, (char*)data, capacity, 0, &socketAddr, &length)) == SOCKET_ERROR) {
            size = 0;
            int error = WSAGetLastError();
            if (error == WSAEWOULDBLOCK)
                return;
            Logger::log(LogType::ERR0R, _T("there was an error while receiving data\n"));
            throw CallFailedException();
        }
        size = bytes;
    }

    void Socket::bind() {
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
        if (result == SOCKET_ERROR) {
            int error = WSAGetLastError();
            auto text = std::format(_T("unable to bind to socket, error: {:d}\n"), error);
            Logger::log(LogType::ERR0R, text.c_str());
            throw CallFailedException();
        }
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
        address = _T("");
        delete addressStruct;
        addressStruct = nullptr;
        delete addressStruct6;
        addressStruct6 = nullptr;
    }
}