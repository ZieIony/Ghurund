#pragma once

#include "core/string/String.h"

#include <ws2tcpip.h>

namespace Ghurund::Net {
    using namespace Ghurund::Core;

    class Socket {
    private:
        ::SOCKET id = INVALID_SOCKET;
        unsigned short port = 0;
        String address;
        sockaddr_in* addressStruct = nullptr;
        sockaddr_in6* addressStruct6 = nullptr;

    public:
        ~Socket() {
            close();
        }

        void init(::SOCKET id, const String& address, uint16_t port);

        inline void init(const String& address, uint16_t port = 0) {
            init(::socket(AF_INET, SOCK_DGRAM, 0), address.Data, port);
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

        void send(Socket& socket, const void* data, size_t size, unsigned int flags = 0)const;

        void receive(void* data, size_t capacity, size_t& size, sockaddr& socketAddr);

        void bind();

        void close();
    };
}