#pragma once

#include "core/window/WindowManager.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class VirtualWindowManager:public WindowManager {
    private:
        HWND hostWindow;

    public:
        VirtualWindowManager(HWND hostWindow) {
            this->hostWindow = hostWindow;
        }

        virtual HWND makeWindow(WindowStyle attr) override {
            return hostWindow;
        }
    };
}