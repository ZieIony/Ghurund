#pragma once

#include "core/threading/CriticalSection.h"
#include "core/reflection/Type.h"

#include <process.h>
#include <queue>

namespace Ghurund {
    class Thread:public NamedObject
    {
    private:
        HANDLE handle = INVALID_HANDLE_VALUE;
        DWORD threadId = 0;

        static DWORD WINAPI threadMain(void* arg) {
            Thread* thread = (Thread*)arg;
            thread->run();
            return 0;
        }

    protected:
        virtual void run() = 0;

    public:
        virtual ~Thread() {
            if (handle != INVALID_HANDLE_VALUE)
                finish();
        }

        inline void start() {
            handle = CreateThread(NULL, 0, threadMain, this, 0, &threadId);
        }

        virtual void finish() {
            WaitForSingleObject(handle, INFINITE);
            CloseHandle(handle);
            handle = INVALID_HANDLE_VALUE;
        }

        inline void join() {
            WaitForSingleObject(handle, INFINITE);
        }

        inline DWORD getId() {
            return threadId;
        }

        __declspec(property(get = getId)) DWORD Id;

        inline HANDLE getHandle() {
            return handle;
        }

        __declspec(property(get = getHandle)) HANDLE Handle;
    };
}