#pragma once

#include "core/threading/CriticalSection.h"
#include "core/reflection/Type.h"

#include <functional>
#include <process.h>
#include <queue>

namespace Ghurund {
    class Thread {
    private:
        HANDLE handle = INVALID_HANDLE_VALUE;
        DWORD threadId = 0;
        bool finishing = false;
        CriticalSection section;
        HANDLE event;

        static DWORD WINAPI threadMain(void* arg) {
            Thread* thread = (Thread*)arg;
            thread->run();
            return 0;
        }

    protected:
        virtual void wakeUp() {}

        virtual void run() = 0;

    public:

        Thread() {
            event = CreateEvent(nullptr, false, false, nullptr);
        }

        ~Thread() {
            if (handle != INVALID_HANDLE_VALUE)
                finish();
        }

        void start() {
            handle = CreateThread(NULL, 0, threadMain, this, 0, &threadId);
        }

        void wait(DWORD ms = INFINITE) {
            WaitForSingleObjectEx(event, ms, true);
        }

        void notify() {
            SetEvent(event);
        }

        bool isFinishing() {
            section.enter();
            bool result = finishing;
            section.leave();
            return result;
        }

        void finish() {
            section.enter();
            finishing = true;
            wakeUp();
            section.leave();
            WaitForSingleObject(handle, INFINITE);
            CloseHandle(handle);
            handle = INVALID_HANDLE_VALUE;
        }

        DWORD getId() {
            return threadId;
        }

        __declspec(property(get = getId)) DWORD Id;

        HANDLE getHandle() {
            return handle;
        }

        __declspec(property(get = getHandler)) HANDLE Handle;
    };

    class APCThread:public Thread {
    private:
        static void CALLBACK wake(__in  ULONG_PTR arg) {}

    protected:
        virtual void wakeUp() {
            post(&wake, 0);
        }

    public:

        void post(PAPCFUNC apc, ULONG_PTR data) {
            QueueUserAPC(apc, getHandle(), data);
        }

        void run() {
            while (!isFinishing())
                ::SleepEx(INFINITE, true);
        }
    };
}