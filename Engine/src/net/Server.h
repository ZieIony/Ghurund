#pragma once

#include "core/Noncopyable.h"
#include "core/collection/List.h"
#include "Message.h"
#include "Socket.h"

namespace Ghurund::Net {
    class Server:public Noncopyable {
    private:
        Socket socket;
        List<Socket*> sockets;
        bool hosting;

    public:
        Server();
        ~Server();

        Status host(SocketProtocol protocol, unsigned short port);
        Status accept();
        //Status receive(Socket **sender, void **buffer, int *size);
        void shutdown();

        inline bool isHosting() {
            return hosting;
        }
        
        inline Status send(void *data, int size, unsigned int flags = 0);

        inline Status sendExcept(const Socket *socket, void *data, int size, unsigned int flags = 0);

        inline const Socket *getClientSocket(unsigned int index)const{
            return sockets.get(index);
        }

        inline size_t getConnections() {
            return sockets.getSize();
        }

    };
}