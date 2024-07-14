#pragma once

#include "Server.h"
#include "Client.h"
#include "core/application/Feature.h"

namespace Ghurund::Net {
    using namespace Ghurund::Core;

    class Networking:public Feature, public Noncopyable {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Networking::GET_TYPE();
#pragma endregion

    public:
        void init();

        void uninit() {
            WSACleanup();
        };

        SharedPointer<Server> host(uint16_t port = 0) {
            auto server = makeShared<Server>();
            server->host(port);
            return server;
        }

        SharedPointer<Client> connect(const tchar* address, uint16_t port) {
            auto client = makeShared<Client>();
            client->connect(address, port);
            return client;
        }
    };
}