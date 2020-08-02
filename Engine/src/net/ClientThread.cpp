#include "ClientThread.h"
#include "Client.h"

namespace Ghurund {
    void ClientThread::eventLoop(void *arg) {
        ThreadParams *params = (ThreadParams*)arg;
        Socket &socket = params->socket;
        WSAEVENT eventHandle = socket.EventHandle;
        NetworkListener *listener = params->listener;
        Client &client = params->client;
        StateMachine<ConnectionState> &connectionState = params->connectionState;

        constexpr int EVENT_COUNT = 1;
        constexpr time_t TIMEOUT_MS = 2000;
        constexpr int DISCONNECT_COUNT = 3;
        int disconnect = 0;

        WSANETWORKEVENTS networkEvents;

        while(connectionState.getState()==ConnectionState::CONNECTED) {
            if(disconnect==DISCONNECT_COUNT) {
                client.disconnect();
                break;
            }

            int result = WSAWaitForMultipleEvents(EVENT_COUNT, &eventHandle, FALSE, TIMEOUT_MS, FALSE);
            if(result == WSA_WAIT_FAILED) {
                Logger::log(LogType::ERR0R, _T("WSAWaitForMultipleEvents() failed with error {:d}\n"), WSAGetLastError());
                return;
            } else if(result == WSA_WAIT_TIMEOUT) {
                if(listener!=nullptr)
                    listener->onTimeout(disconnect*TIMEOUT_MS);
                disconnect++;
                Logger::log(LogType::INFO, _T("refreshing connection %i\n"), disconnect);
                client.send("ping", strlen("ping")+1);
            } else {
                disconnect = 0;
                if(WSAEnumNetworkEvents(socket.Id, eventHandle, &networkEvents) == SOCKET_ERROR) {
                    Logger::log(LogType::ERR0R, _T("WSAEnumNetworkEvents() failed with error {}\n"), WSAGetLastError());
                    return;
                }

                if(handleEvent(networkEvents, socket)!=Status::OK)
                    break;
            }
        }

        connectionState.setState(ConnectionState::NOT_CONNECTED);
        Logger::log(LogType::INFO, _T("ClientThread finished\n"));
    }

    Status ClientThread::handleReadEvent(WSANETWORKEVENTS &networkEvents, Socket &socket) {
        if(networkEvents.lNetworkEvents & FD_READ && networkEvents.iErrorCode[FD_READ_BIT] != 0) {
            printf("FD_READ failed with error %d\n", networkEvents.iErrorCode[FD_READ_BIT]);
            return Status::SOCKET;
        }

        DWORD flags = 0;

        DWORD recvBytes = 0;
        if(socket.receive()!=Status::OK) {
            int error = WSAGetLastError();
            if(error != WSAEWOULDBLOCK) {
                printf("WSARecv() failed with error %d\n", WSAGetLastError());
                return Status::SOCKET;
            }
        } else {
            printf("WSARecv() is working!\n");
        }

        return Status::OK;
    }

    Status ClientThread::handleWriteEvent(WSANETWORKEVENTS &networkEvents, Socket &socket) {
        if(networkEvents.lNetworkEvents & FD_WRITE && networkEvents.iErrorCode[FD_WRITE_BIT] != 0) {
            printf("FD_WRITE failed with error %d\n", networkEvents.iErrorCode[FD_WRITE_BIT]);
            return Status::SOCKET;
        }

        DWORD flags = 0;

        // Write buffer data if it is available
        /*if(socket.BytesRECV > socket.BytesSEND) {
        socket.DataBuf.buf = socket.Buffer + socket.BytesSEND;
        socket.DataBuf.len = socket.BytesRECV - socket.BytesSEND;

        DWORD SendBytes;
        if(WSASend(socket.Id, &(socket.DataBuf), 1, &SendBytes, 0, nullptr, nullptr) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        if(error != WSAEWOULDBLOCK) {
        printf("WSASend() failed with error %d\n", error);
        //FreeSocketInformation(Event - WSA_WAIT_EVENT_0);
        return;
        }

        // A WSAEWOULDBLOCK error has occurred. An FD_WRITE event will be posted
        // when more buffer space becomes available
        } else {
        printf("WSASend() is fine! Thank you...\n");
        socket.BytesSEND += SendBytes;

        if(socket.BytesSEND == socket.BytesRECV) {
        socket.BytesSEND = 0;
        socket.BytesRECV = 0;
        }
        }
        }*/

        return Status::OK;
    }

    Status ClientThread::handleEvent(WSANETWORKEVENTS &networkEvents, Socket &socket) {
        if(networkEvents.lNetworkEvents & FD_ACCEPT) {
            Logger::log(LogType::INFO, _T("Accept"));
            /*SOCKET Accept;

            if(networkEvents.iErrorCode[FD_ACCEPT_BIT] != 0) {
            printf("FD_ACCEPT failed with error %d\n", networkEvents.iErrorCode[FD_ACCEPT_BIT]);
            break;
            }

            if((Accept = accept(socket.Id, NULL, NULL)) == INVALID_SOCKET) {
            printf("accept() failed with error %d\n", WSAGetLastError());
            break;
            }

            //CreateSocketInformation(Accept);

            if(WSAEventSelect(Accept, EventArray[EventTotal - 1], FD_READ|FD_WRITE|FD_CLOSE) == SOCKET_ERROR) {
            printf("WSAEventSelect() failed with error %d\n", WSAGetLastError());
            return;
            }

            printf("Socket %d got connected...\n", Accept);*/
        }

        if(networkEvents.lNetworkEvents & FD_READ)
            return handleReadEvent(networkEvents, socket);
        if(networkEvents.lNetworkEvents & FD_WRITE)
            return handleWriteEvent(networkEvents, socket);

        if(networkEvents.lNetworkEvents & FD_CLOSE) {
            if(networkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
                return Logger::log(LogType::ERR0R, Status::SOCKET, _T("FD_CLOSE failed with error %d\n"), networkEvents.iErrorCode[FD_CLOSE_BIT]);

            Logger::log(LogType::INFO, _T("Closing socket information %d\n"), socket.Id);
            //FreeSocketInformation(Event - WSA_WAIT_EVENT_0);
        }

        return Status::OK;
    }
}
