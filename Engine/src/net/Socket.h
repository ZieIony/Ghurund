#pragma once

#include "Common.h"
#include "Status.h"

#include <ws2tcpip.h>

namespace Ghurund::Net {
    class Socket {
    private:
        static const int BUFFER_SIZE = 4096;

        ::SOCKET id = INVALID_SOCKET;
        unsigned short port = 0;
        tchar* address = nullptr;
        sockaddr_in* addressStruct = nullptr;
        sockaddr_in6* addressStruct6 = nullptr;
        WSAEVENT eventHandle = 0;
        WSABUF dataBuffer;

    public:
        Socket() {
            memset(&dataBuffer, 0, sizeof(WSABUF));
        }

        ~Socket() {
            close();
        }

        Status init(::SOCKET id, const tchar* address, uint16_t port);

        Status init(const tchar* address, uint16_t port) {
            return init(::socket(AF_INET, SOCK_DGRAM, 0), address, port);
        }

        ::SOCKET getId() const {
            return id;
        }

        __declspec(property(get = getId)) ::SOCKET Id;

        WSAEVENT getEventHandle() const {
            return eventHandle;
        }

        __declspec(property(get = getEventHandle)) WSAEVENT EventHandle;

        sockaddr* getAddressStruct()const;

        Status send(const void* data, size_t size, unsigned int flags = 0)const;

        Status receive(void** data = nullptr, size_t* size = nullptr);

        void* getData()const {
            return dataBuffer.buf;
        }

        size_t getDataSize()const {
            return dataBuffer.len;
        }

        Status bind();

        Status select();

        void close() {
            delete[] dataBuffer.buf;
            WSACloseEvent(eventHandle);
            closesocket(id);
            delete[] address;
            delete addressStruct;
            delete addressStruct6;
        }
    };
}