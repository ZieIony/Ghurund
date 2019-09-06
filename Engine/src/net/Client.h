#pragma once

#include "ClientThread.h"
#include "ConnectionState.h"
#include "Message.h"
#include "NetworkListener.h"
#include "Socket.h"
#include "core/Noncopyable.h"
#include "core/collection/List.h"
#include "core/threading/FunctionQueue.h"
#include "core/StateMachine.h"

#include <thread>
#include <time.h>
#include <winsock2.h>

namespace Ghurund {
    class Client:public Noncopyable {
    protected:
        Socket *serverSocket = nullptr, mySocket;
        StateMachine<ConnectionState> connectionState;
        List<UDPMessage*> messages;
        NetworkListener *listener = nullptr;
        ClientThread *thread = nullptr;
        FunctionQueue &functionQueue;

    public:
        Client(FunctionQueue &functionQueue);
        ~Client();

        Status init();
        Status connect(SocketProtocol protocol, unsigned short port, const tchar *address);
        void disconnect();

        inline bool isConnected() const {
            return connectionState.getState()==ConnectionState::CONNECTED;
        }

        inline Status send(void *data, size_t size)const {
            return serverSocket->send(data, size, 0);
        }

        inline Status receive(void ** buffer, size_t * size) {
            return mySocket.receive(buffer, size);
        }

        inline const Socket *getSocket()const {
            return &mySocket;
        }

        void update() {
            time_t time = ::time(nullptr);
        }

        void setNetworkListener(NetworkListener *listener) {
            this->listener = listener;
        }

        NetworkListener *getNetworkListener() {
            return listener;
        }

    };
}