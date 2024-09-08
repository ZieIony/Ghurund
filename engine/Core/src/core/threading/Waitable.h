#pragma once

#include <Windows.h>

namespace Ghurund::Core {
    class Waitable {
    private:
        HANDLE event;

    public:
        Waitable() {
            event = CreateEventW(nullptr, false, false, nullptr);
        }

        ~Waitable() {
            CloseHandle(event);
        }

        inline void wait(DWORD ms = INFINITE) {
            WaitForSingleObjectEx(event, ms, true);
        }

        inline void notify() {
            SetEvent(event);
        }
    };
}