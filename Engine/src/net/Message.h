#pragma once

#include "Common.h"
#include "core/string/TextUtils.h"

#include "winsock2.h"

#define WM_GHFILEWATCHER WM_USER+100

namespace Ghurund::Net {
    enum class ClientMessageType:uint8_t {
        CONNECT, DISCONNECT, UPDATE, 
    };

    struct Message {
        uint8_t type;
        uint16_t sender;
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