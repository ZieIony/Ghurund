#pragma once

#include "Common.h"
#include "TextUtils.h"
#include "MathUtils.h"

#include <stdio.h>
#include <psapi.h>

namespace Ghurund {
    enum class Status {
        OK, INV_PARAM, INV_STATE, CALL_FAIL, SOCKET, IO, NOT_IMPLEMENTED, ALREADY_LOADED, UNKNOWN,

        WRONG_RESOURCE_VERSION,
        WRONG_RESOURCE_TYPE,
        FILE_DOESNT_EXIST,
        FILE_EXISTS,
        UNKNOWN_FORMAT,
        INV_FORMAT,
        UNEXPECTED_EOF,

        ENTRY_POINT_NOT_FOUND,
        COMPILATION_ERROR,
        SCRIPT_EXCEPTION,

        DIRECTX12_NOT_SUPPORTED
    };


    inline void dumpMemoryLeaks() {
        _CrtDumpMemoryLeaks();
    }

    inline void _____________________checkMemory() {
        _ASSERTE(_CrtCheckMemory());
    }

    template<class Type> inline Type align(Type value, Type alignment) {
        return (value + alignment - 1) & ~(alignment - 1);
    }

    template<class Type> void safeDelete(Type * &p) {
        delete p;
        p = nullptr;
    }

    template<class Type> void safeDeleteArray(Type * &p) {
        delete[] p;
        p = nullptr;
    }

}