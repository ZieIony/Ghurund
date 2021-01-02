#pragma once

#include "winsock2.h"
#include "Socket.h"
#include "NetworkListener.h"
#include <thread>
#include "core/StateMachine.h"
#include "ConnectionState.h"

namespace Ghurund::Net {
    class Client;

    class ClientThread {
    private:
        struct ThreadParams {
            Socket& socket;
            NetworkListener* listener;
            StateMachine<ConnectionState>& connectionState;
            Client& client;
        };

        ThreadParams params;
        std::thread* thread;
        static void eventLoop(void* arg);
        static Status handleReadEvent(WSANETWORKEVENTS& networkEvents, Socket& socket);
        static Status handleWriteEvent(WSANETWORKEVENTS& networkEvents, Socket& socket);
        static Status handleEvent(WSANETWORKEVENTS& networkEvents, Socket& socket);

    public:
        ClientThread(Socket& socket, NetworkListener* listener, StateMachine<ConnectionState>& connectionState, Client& client):params{ socket, listener,connectionState,client } {
            thread = ghnew std::thread(ClientThread::eventLoop, &params);
        }

        ~ClientThread() {
            thread->join();
            delete thread;
        }
    };
}