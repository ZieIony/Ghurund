#pragma once

#include "Thread.h"

namespace Ghurund {
    class APCThread:public Thread {
    private:
        static void CALLBACK wake(__in  ULONG_PTR arg) {}

        bool running = false;

    public:
        virtual ~APCThread() {
            if (running)
                finish();
        }

        void post(PAPCFUNC apc, ULONG_PTR data) {
            QueueUserAPC(apc, Handle, data);
        }

        void run() {
            while (running)
                ::SleepEx(INFINITE, true);
        }

        virtual void finish() override {
            running = false;
            post(&wake, 0);
            __super::finish();
        }
    };
}