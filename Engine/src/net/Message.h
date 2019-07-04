#pragma once

#include "Common.h"
#include "TextUtils.h"

#include "winsock2.h"

#define WM_GHFILEWATCHER WM_USER+100

namespace Ghurund {
    namespace MsgType {
        enum Type {
            CONTROL = (1 >> 30), CHAT = (2 >> 30), SYNC = (3 >> 30)
        };
    }

    class Message {
    private:
        void* buffer, * data;
        int type;
        unsigned int size;

    public:
        SOCKET sender;

        Message() {
            buffer = 0;
            data = 0;
            type = 0;
            size = 0;
        }

        ~Message() {
            delete[] buffer;
        }

        void setData(unsigned int type, const char* data, unsigned int size) {
            if (!data)
                return;
            delete[] buffer;
            buffer = ghnew char[sizeof(unsigned int) + size];
            this->type = ((unsigned int*)buffer)[0] = type;
            memcpy((char*)buffer + sizeof(unsigned int), data, size);
            this->data = (unsigned int*)buffer + 1;
        }

        unsigned int getType() {
            return type;
        }

        const char* getData() {
            return (char*)data;
        }

        unsigned int getSize() {
            return size;
        }
    };

    enum class UDPMessageType {
        CONNECT, DISCONNECT, ALIVE, GAME, CHAT, CONFIRM
    };

    struct UDPMessage {
        UDPMessageType type;
    };

    struct UDPMessageChat:public UDPMessage {
        tchar* text = nullptr;

    public:

        UDPMessageChat(const tchar* text) {
            type = UDPMessageType::CHAT;
            this->text = copyStr(text);
        }

        UDPMessageChat(const void* data, unsigned int size) {
            type = UDPMessageType::CHAT;
            tchar* text = (tchar*)((char*)data + sizeof(type));
            this->text = copyStr(text);
        }

        void* getData() {
            size_t length = _tcslen(text) + 1;
            char* data = new char[sizeof(type) + length * sizeof(tchar)];
            memcpy(data, &type, sizeof(type));
            memcpy(data + sizeof(type), text, length * sizeof(tchar));
            return data;
        }

        size_t getSize() {
            return sizeof(type) + (_tcslen(text) + 1) * sizeof(tchar);
        }
    };

    struct UDPMessageConfirm:public UDPMessage {
        UDPMessageType what;	// what message are we confirming
        int when;	// when was the confirmed message sent

        UDPMessageConfirm(UDPMessageType what, int when) {
            type = UDPMessageType::CONFIRM;
            this->what = what;
            this->when = when;
        }
    };

    struct UDPMessageConnect:public UDPMessage {
        int time;
        UDPMessageConnect(int time) {
            this->type = UDPMessageType::CONNECT;
            this->time = time;
        }
    };
}