#pragma once

#include "Common.h"
#include "Status.h"
#include "core/Buffer.h"

#include <ws2tcpip.h>

namespace Ghurund::Net {
    class Socket {
    private:
        ::SOCKET id = INVALID_SOCKET;
        unsigned short port = 0;
        tchar* address = nullptr;
        sockaddr_in* addressStruct = nullptr;
        sockaddr_in6* addressStruct6 = nullptr;

    public:
        ~Socket() {
            close();
        }

        Status init(::SOCKET id, const tchar* address, uint16_t port);

        inline Status init(const tchar* address, uint16_t port = 0) {
            return init(::socket(AF_INET, SOCK_DGRAM, 0), address, port);
        }

        inline ::SOCKET getId() const {
            return id;
        }

        __declspec(property(get = getId)) ::SOCKET Id;

        inline bool isValid() const {
            return id != INVALID_SOCKET;
        }

        __declspec(property(get = isValid)) bool Valid;

        inline sockaddr* getAddressStruct() const {
            if (addressStruct6)
                return (sockaddr*)addressStruct6;
            return (sockaddr*)addressStruct;
        }

        __declspec(property(get = getAddressStruct)) sockaddr* AddressStruct;

        Status send(Socket& socket, const void* data, size_t size, unsigned int flags = 0)const;

        Status receive(void* data, size_t capacity, size_t& size, sockaddr& socketAddr);

        Status bind();

        void close();
    };
}