#pragma once

#include "core/logging/Logger.h"

#include <winsock2.h>

namespace Ghurund::Net {

    Status init() {
        WSADATA w;

        if (WSAStartup(0x0202, &w)) // there was an error
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("there was an error with WinSock initialization\n"));
        if (w.wVersion != 0x0202) { // wrong WinSock version!
            WSACleanup(); // unload ws2_32.dll
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("wrong WinSock version\n"));
        }

        return Status::OK;
    }

    void uninit() {
        WSACleanup();
    };
}