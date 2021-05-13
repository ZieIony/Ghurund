#pragma once

#include "Server.h"
#include "Client.h"
#include "application/Feature.h"

#include "reflection_84c7ff0b_6884_47b3_9cf6_5c7939b247ae.h"

namespace Ghurund::Net {
    class Networking:public Feature, public Noncopyable {
        reflection_84c7ff0b_6884_47b3_9cf6_5c7939b247ae

    public:
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