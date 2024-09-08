#pragma once

#include "core/window/WindowClass.h"
#include "core/window/WindowStyle.h"
#include "core/collection/Map.h"

namespace Ghurund::Core {
    class WindowManager {
    public:
        virtual HWND makeWindow(WindowStyle style) = 0;
    };

    class SystemWindowManager:public WindowManager {
    private:
        Map<WindowStyle, WindowClass*> classes;

    public:
        ~SystemWindowManager() {
            for (auto& [windowStyle, windowClass] : classes)
                delete windowClass;
        }

        virtual HWND makeWindow(WindowStyle style) override {
            WindowClass* windowClass;
            if (classes.contains(style)) {
                windowClass = classes.get(style);
            } else {
                windowClass = ghnew WindowClass(style);
                classes.put(style, windowClass);
            }
            return windowClass->create();
        }
    };
}