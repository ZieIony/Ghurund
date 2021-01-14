#pragma once

#include "core/Buffer.h"
#include "core/Noncopyable.h"
#include "core/collection/List.h"
#include "core/collection/Map.h"
#include "Message.h"
#include "Socket.h"

namespace Ghurund::Net {
    class ClientConnection {
        Socket* socket;

    public:
        ClientConnection(Socket* socket):socket(socket) {}

        ~ClientConnection() {
            delete socket;
        }
    };

    class Server:public Noncopyable {
    private:
        Socket socket;
        
        Map<uint16_t, ClientConnection> clients;
        List<uint16_t> spareIds;

        bool hosting = false;
        static constexpr uint32_t BUFFER_SIZE = 1024;
        Buffer buffer = Buffer(BUFFER_SIZE);

        Status handlePacket(uint8_t* data, uint32_t size, sockaddr_in& socketAddr);

    public:
        ~Server();

        Status host(uint16_t port = 0);
        Status receive();
        void shutdown();

        inline bool isHosting() {
            return hosting;
        }

        __declspec(property(get = isHosting)) bool Hosting;
        
        inline Status send(void *data, int size, unsigned int flags = 0);

        inline Status sendExcept(const Socket *socket, void *data, int size, unsigned int flags = 0);

        inline Map<uint16_t, ClientConnection>& getConnections() {
            return clients;
        }

        __declspec(property(get = getConnections)) Map<uint16_t, ClientConnection> Connections;
    };
}