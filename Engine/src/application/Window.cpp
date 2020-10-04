#include "Window.h"
#include "WindowType.h"
#include <time.h>

namespace Ghurund {
    LRESULT windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
        WindowData* windowData = (WindowData*)GetWindowLongPtr(handle, GWLP_USERDATA);
        if (!windowData)
            return DefWindowProc(handle, msg, wParam, lParam);

        Window& window = *windowData->window;

        if (msg == WM_KEYDOWN) {
            window.OnKeyEvent(KeyEventArgs(KeyAction::DOWN, (int)wParam, time(nullptr)));
            return 0;
        } else if (msg == WM_KEYUP) {
            window.OnKeyEvent(KeyEventArgs(KeyAction::UP, (int)wParam, time(nullptr)));
            return 0;
        } else if (msg == WM_CHAR) {
            window.OnKeyEvent(KeyEventArgs(KeyAction::CHAR, (int)wParam, time(nullptr)));
            return 0;
        } else if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(window.Handle, &p);
            if (msg == WM_LBUTTONDOWN) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::DOWN, MouseButton::LEFT, time(nullptr)));
            } else if (msg == WM_LBUTTONUP) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::UP, MouseButton::LEFT, time(nullptr)));
            } else if (msg == WM_MBUTTONDOWN) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::DOWN, MouseButton::MIDDLE, time(nullptr)));
            } else if (msg == WM_MBUTTONUP) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::UP, MouseButton::MIDDLE, time(nullptr)));
            } else if (msg == WM_RBUTTONDOWN) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::DOWN, MouseButton::RIGHT, time(nullptr)));
            } else if (msg == WM_RBUTTONUP) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::UP, MouseButton::RIGHT, time(nullptr)));
            } else if (msg == WM_MOUSEMOVE) {
                if (windowData->prevMousePos.x == -1 && windowData->prevMousePos.y == -1)
                    windowData->prevMousePos = p;
                window.OnMouseMotionEvent(MouseMotionEventArgs(XMINT2(p.x, p.y), XMINT2(p.x - windowData->prevMousePos.x, p.y - windowData->prevMousePos.y), time(nullptr)));
                windowData->prevMousePos = p;
            } else if (msg == WM_MOUSEWHEEL) {
                window.OnMouseWheelEvent(MouseWheelEventArgs(XMINT2(p.x, p.y), MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(wParam), time(nullptr)));
            } else if (msg == WM_MOUSEHWHEEL) {
                window.OnMouseWheelEvent(MouseWheelEventArgs(XMINT2(p.x, p.y), MouseWheel::HORIZONTAL, GET_WHEEL_DELTA_WPARAM(wParam), time(nullptr)));
            }
            return 0;
        } else if (msg == WM_PAINT) {
            window.OnPaint();
            return 0;
        } else if (msg == WM_MOVE) {
            unsigned int x = LOWORD(lParam);
            unsigned int y = HIWORD(lParam);

            RECT rc = { 0,0,window.Size.x, window.Size.y };
            AdjustWindowRect(&rc, window.Class.Style, false);

            if (window.Position.x != x + rc.left && window.Position.y != y + rc.top) {
                window.setPosition(x + rc.left, y + rc.top);
                window.OnPositionChanged();
            }
            return 0;
        } else if (msg == WM_SIZE) {
            unsigned int width = LOWORD(lParam);
            unsigned int height = HIWORD(lParam);
            if (window.Size.x != width || window.Size.y != height) {
                window.setSize(width, height);
                window.OnSizeChanged();
            }
            return 0;
        } else if (msg == WM_NCACTIVATE) {
            if (window.Class == WindowClass::POPUP && wParam == FALSE) {
                PostMessage(window.Handle, WM_CLOSE, 0, 0);
                return 0;
            }
        } else if (msg == WM_DESTROY) {
            window.OnDestroy();
            delete windowData;
            return 0;
        }

        return DefWindowProc(handle, msg, wParam, lParam);
    }

    Window::Window(HWND handle, const WindowClass& type):windowClass(type), parameters(PointerArray<Parameter*>(1)) {
        this->handle = handle;
        if (functionQueue != nullptr)
            delete functionQueue;
        const unsigned int eventCode = RegisterWindowMessage(_T("GhurundEvent"));
        functionQueue = ghnew Ghurund::FunctionQueue(handle, eventCode);
    }

    Window::~Window() {
        delete functionQueue;
        functionQueue = nullptr;

        setVisible(false);

        if (handle)
            DeleteObject(handle);
    }

    void Window::setPosition(int x, int y) {
        if (position.x != x || position.y != y) {
            position = { x, y };

            SetWindowPos(handle, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }

    void Window::setSize(unsigned int w, unsigned int h) {
        if (size.x != w || size.y != h) {
            size = XMINT2(w, h);

            RECT rc, rcClient;
            GetWindowRect(handle, &rc);
            GetClientRect(handle, &rcClient);
            int xExtra = rc.right - rc.left - rcClient.right;
            int yExtra = rc.bottom - rc.top - rcClient.bottom;

            SetWindowPos(handle, 0, 0, 0, w + xExtra, h + yExtra, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }
}