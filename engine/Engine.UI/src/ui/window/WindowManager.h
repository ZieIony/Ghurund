#pragma once

#include "core/window/WindowAttributes.h"
#include "core/window/SystemWindow.h"
#include "core/collection/Map.h"
#include <format>

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class WindowManager {
    public:
        virtual Window* makeWindow(WindowAttributes attr) = 0;
    };

    class VirtualWindowManager:public WindowManager {
    private:
        Window* hostWindow;

    public:
        VirtualWindowManager(Timer& timer) {
            //hostWindow = ghnew SystemWindow();
        }

        virtual Window* makeWindow(WindowAttributes attr) override {}
    };

    class SystemWindowManager:public WindowManager {
    private:
        Timer& timer;
        Map<WindowAttributes, WNDCLASSEX> classes;

    public:
        SystemWindowManager(Timer& timer):timer(timer) {}

        ~SystemWindowManager() {
            for (WNDCLASSEX& windowClass : classes) {
                UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
                delete[] windowClass.lpszClassName;
            }
        }

        virtual Window* makeWindow(WindowAttributes attr) override {
            DWORD exStyle = attr & WindowAttributes::SHOW_ON_TASKBAR ? WS_EX_APPWINDOW : WS_EX_NOACTIVATE;
            DWORD dwStyle =
                (attr & WindowAttributes::MINIMIZE_BUTTON ? WS_MINIMIZEBOX : 0) |
                (attr & WindowAttributes::MAXIMIZE_BUTTON ? WS_MAXIMIZEBOX : 0) |
                (attr & WindowAttributes::TITLE ? WS_CAPTION : 0) |
                (attr & WindowAttributes::RESIZE_BORDER ? WS_THICKFRAME : 0) |
                (attr & WindowAttributes::THIN_BORDER ? WS_BORDER : 0);

            String className = std::format(_T("Ghurund{}"), (size_t)attr).c_str();

            UINT style = attr & WindowAttributes::THIN_BORDER ? CS_DROPSHADOW : 0;

            HINSTANCE hInst = GetModuleHandle(0);

            if (!classes.containsKey(attr)) {
                WNDCLASSEX windowClass = {
                    .cbSize = sizeof(WNDCLASSEX),
                    .style = style,
                    .lpfnWndProc = &windowProc,
                    .cbClsExtra = 0L,
                    .cbWndExtra = 0L,
                    .hInstance = hInst,
                    .hIcon = 0,
                    .hCursor = nullptr,
                    .hbrBackground = 0,
                    .lpszMenuName = 0,
                    .lpszClassName = copyStr(className.Data),
                    .hIconSm = 0
                };

                RegisterClassEx(&windowClass);
                classes.set(attr, windowClass);
            }

            HWND handle = CreateWindowEx(exStyle, className.Data, nullptr, dwStyle, 0, 0, 0, 0, nullptr, nullptr, hInst, nullptr);
            return ghnew SystemWindow(handle, timer);
        }
    };
}