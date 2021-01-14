#pragma once

#include "Server.h"
#include "Client.h"
#include "core/Object.h"

namespace Ghurund::Net {
    class Networking:public Object, public Noncopyable {
    public:
        ~Networking() {
            uninit();
        }

        Status init();

        void uninit() {
            WSACleanup();
        };

        Server* host(uint16_t port = 0) {
            Server* server = ghnew Server();
            if (server->host(port) != Status::OK) {
                delete server;
                return nullptr;
            }
            return server;
        }

        Client* connect(const tchar* address, uint16_t port) {
            Client* client = ghnew Client();
            if (client->connect(address, port) != Status::OK) {
                delete client;
                return nullptr;
            }
            return client;
        }
    };
}