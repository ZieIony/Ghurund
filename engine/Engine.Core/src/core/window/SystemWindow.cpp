#include "ghcpch.h"
#include "SystemWindow.h"

#include "WindowClass.h"
#include "core/Timer.h"
#include "core/input/Input.h"
#include "core/reflection/TypeBuilder.h"

#include <time.h>
#include <shellapi.h>
#include <windowsx.h>

namespace Ghurund {
    LRESULT CALLBACK windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
        WindowData* windowData = (WindowData*)GetWindowLongPtr(handle, GWLP_USERDATA);
        if (!windowData)
            return DefWindowProc(handle, msg, wParam, lParam);

        SystemWindow& window = *windowData->window;
        Timer& timer = window.Timer;
        Input& input = window.Input;

        if (msg >= WM_KEYFIRST && msg <= WM_KEYLAST) {
            input.addEvent({ msg, wParam, timer.TimeMs });
            return 0;
        } else if (msg == WM_MOUSEMOVE) {
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(window.Handle, &p);
            input.addEvent({ msg, wParam, timer.TimeMs, p });

            if (!windowData->mouseTracked) {
                windowData->mouseTracked = true;

                TRACKMOUSEEVENT mouseEvt;
                ZeroMemory(&mouseEvt, sizeof(TRACKMOUSEEVENT));
                mouseEvt.cbSize = sizeof(TRACKMOUSEEVENT);
                mouseEvt.dwFlags = TME_LEAVE;
                mouseEvt.hwndTrack = window.Handle;
                TrackMouseEvent(&mouseEvt);
            }
        } else if (msg == WM_MOUSELEAVE) {
            windowData->mouseTracked = false;
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(window.Handle, &p);
            input.addEvent({ msg, wParam, timer.TimeMs, p });
        } else if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(window.Handle, &p);
            input.addEvent({ msg, wParam, timer.TimeMs, p });
            return 0;
            //} else if (msg == WM_PAINT) {
              //  window.OnPaint();   // TODO: do it in the message loop
        } else if (msg == WM_MOVE) {
            unsigned int x = LOWORD(lParam);
            unsigned int y = HIWORD(lParam);

            RECT rc = { 0,0,(LONG)window.Size.width, (LONG)window.Size.height };
            AdjustWindowRect(&rc, window.Class.Style, false);

            if (window.Position.x != x + rc.left && window.Position.y != y + rc.top) {
                window.setPosition(x + rc.left, y + rc.top);
                window.dispatchPositionChangedEvent();
            }
            return 0;
        } else if (msg == WM_SIZE) {
            unsigned int width = LOWORD(lParam);
            unsigned int height = HIWORD(lParam);
            if (window.Size.width != width || window.Size.height != height) {
                window.setSize(width, height);
                window.dispatchSizeChangedEvent();
            }
            return 0;
        } else if (msg == WM_NCACTIVATE) {
            if (window.Class == WindowClass::POPUP && wParam == FALSE) {
                PostMessage(window.Handle, WM_CLOSE, 0, 0);
                return 0;
            }
        } else if (msg == WM_SETFOCUS || msg == WM_KILLFOCUS) {
            window.dispatchFocusedChangedEvent();
        } else if (msg == WM_CLOSE) {
            window.dispatchClosedEvent();
            return 0;
        }

        return DefWindowProc(handle, msg, wParam, lParam);
    }

    const Ghurund::Type& SystemWindow::GET_TYPE() {
        static const Ghurund::Type TYPE = Ghurund::TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(SystemWindow))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    SystemWindow::SystemWindow(const WindowClass& type, Ghurund::Timer& timer):Window(nullptr), windowClass(type), timer(timer) {
        this->handle = type.create();

        WindowData* windowData = ghnew WindowData(this);
        SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)windowData);
    }

    SystemWindow::~SystemWindow() {
        setVisible(false);
        DragDropEnabled = false;

        WindowData* windowData = (WindowData*)GetWindowLongPtr(handle, GWLP_USERDATA);
        delete windowData;
        SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)nullptr);

        if (handle)
            DestroyWindow(handle);
    }

    void SystemWindow::setPosition(int x, int y) {
        if (Position.x != x || Position.y != y) {
            __super::setPosition(x, y);

            SetWindowPos(handle, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }

    void SystemWindow::setSize(unsigned int w, unsigned int h) {
        if (Size.width != w || Size.height != h) {
            __super::setSize(w, h);

            RECT rc, rcClient;
            GetWindowRect(handle, &rc);
            GetClientRect(handle, &rcClient);
            int xExtra = rc.right - rc.left - rcClient.right;
            int yExtra = rc.bottom - rc.top - rcClient.bottom;

            SetWindowPos(handle, 0, 0, 0, w + xExtra, h + yExtra, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }

    void SystemWindow::setDragDropEnabled(bool enabled) {
        if (isDragDropEnabled() == enabled)
            return;
        if (enabled) {
            dragDropManager = ghnew DragDropManager(*this);
            DragAcceptFiles(handle, TRUE);
            RegisterDragDrop(handle, dragDropManager);
        } else {
            RevokeDragDrop(handle);
            DragAcceptFiles(handle, FALSE);
            if (dragDropManager) {
                dragDropManager->Release();
                dragDropManager = nullptr;
            }
        }
    }

    void SystemWindow::update(const uint64_t time) {
        input.dispatchEvents(time, *this);
    }
}