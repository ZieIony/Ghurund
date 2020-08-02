#include "Window.h"
#include <input\Mouse.h>
#include <input\Keyboard.h>
#include <windowsx.h>
#include <time.h>

namespace Ghurund {
    LRESULT Window::messageProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
        Window& window = *(Window*)GetWindowLongPtr(handle, GWLP_USERDATA);

        if (msg == WM_KEYDOWN) {
            window.OnKeyEvent(window, KeyEventArgs(KeyAction::DOWN, (int)wParam, time(nullptr)));
            return 0;
        } else if (msg == WM_KEYUP) {
            window.OnKeyEvent(window, KeyEventArgs(KeyAction::UP, (int)wParam, time(nullptr)));
            return 0;
        } else if(msg >= WM_MOUSEFIRST) {
            handleMouseMessage(window, msg, wParam);
            return 0;
        } else if (msg == WM_SIZE) {
            XMINT2 prevSize = window.Size;
            unsigned int width = LOWORD(lParam);
            unsigned int height = HIWORD(lParam);
            window.setSize(width, height);
            if (prevSize.x != width || prevSize.y != height)
                window.OnSizeChanged(window);
            return 0;
        } else if (msg == WM_CREATE) {
            LPCREATESTRUCT createStruct = (LPCREATESTRUCT)lParam;
            Window* w = (Window*)createStruct->lpCreateParams;
            SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)w);
            w->OnCreated(*w);
            return 0;
        } else if (msg == WM_DESTROY) {
            window.OnDestroy(window);
            PostQuitMessage(0);
            return 0;
        } else if (msg == WM_PAINT) {
            window.OnPaint(window);
            return 0;
        }

        return DefWindowProc(handle, msg, wParam, lParam);
    }

    void Window::handleMouseMessage(Window& window, UINT msg, WPARAM wParam) {
        POINT p;
        GetCursorPos(&p);
        ScreenToClient(window.Handle, &p);
        if (msg == WM_LBUTTONDOWN) {
            window.OnMouseButtonEvent(window, MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::DOWN, MouseButton::LEFT, time(nullptr)));
        } else if (msg == WM_LBUTTONUP) {
            window.OnMouseButtonEvent(window, MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::UP, MouseButton::LEFT, time(nullptr)));
        } else if (msg == WM_MBUTTONDOWN) {
            window.OnMouseButtonEvent(window, MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::DOWN, MouseButton::MIDDLE, time(nullptr)));
        } else if (msg == WM_MBUTTONUP) {
            window.OnMouseButtonEvent(window, MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::UP, MouseButton::MIDDLE, time(nullptr)));
        } else if (msg == WM_RBUTTONDOWN) {
            window.OnMouseButtonEvent(window, MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::DOWN, MouseButton::RIGHT, time(nullptr)));
        } else if (msg == WM_RBUTTONUP) {
            window.OnMouseButtonEvent(window, MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::UP, MouseButton::RIGHT, time(nullptr)));
        } else if (msg == WM_MOUSEMOVE) {
            if (window.prevMousePos.x == -1 && window.prevMousePos.y == -1)
                window.prevMousePos = p;
            window.OnMouseMotionEvent(window, MouseMotionEventArgs(XMINT2(p.x, p.y), XMINT2(p.x - window.prevMousePos.x, p.y - window.prevMousePos.y), time(nullptr)));
            window.prevMousePos = p;
        } else if (msg == WM_MOUSEWHEEL) {
            window.OnMouseWheelEvent(window, MouseWheelEventArgs(XMINT2(p.x, p.y), MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(wParam), time(nullptr)));
        } else if (msg == WM_MOUSEHWHEEL) {
            window.OnMouseWheelEvent(window, MouseWheelEventArgs(XMINT2(p.x, p.y), MouseWheel::HORIZONTAL, GET_WHEEL_DELTA_WPARAM(wParam), time(nullptr)));
        }
    }

    void Window::init(HWND handle) {
        this->handle = handle;

        RECT rect;
        GetWindowRect(handle, &rect);
        size.x = rect.right - rect.left;
        size.y = rect.bottom - rect.top;

        updateParameters();
    }

    void Window::init(Settings& settings) {
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_CLASSDC;
        windowClass.lpfnWndProc = &messageProc;
        windowClass.cbClsExtra = 0L;
        windowClass.cbWndExtra = 0L;
        hInst = GetModuleHandle(0);
        windowClass.hInstance = hInst;
        windowClass.hIcon = 0;
        windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        windowClass.hbrBackground = 0;
        windowClass.lpszMenuName = 0;
        windowClass.lpszClassName = WINDOW_CLASS_NAME;
        windowClass.hIconSm = 0;
        RegisterClassEx(&windowClass);

        DWORD dwStyle = settings.windowed ? WS_TILEDWINDOW : (WS_POPUP | WS_EX_TOPMOST);
        RECT cr = {0, 0, (LONG)settings.width, (LONG)settings.height};
        AdjustWindowRect(&cr, dwStyle, false);
        handle = CreateWindow(WINDOW_CLASS_NAME, title, dwStyle, 0, 0, cr.right - cr.left, cr.bottom - cr.top, nullptr, nullptr, windowClass.hInstance, this);

        if (functionQueue != nullptr)
            delete functionQueue;
        const unsigned int eventCode = RegisterWindowMessage(_T("GhurundEvent"));
        functionQueue = ghnew Ghurund::FunctionQueue(handle, eventCode);
    }

    void Window::uninit() {
        delete functionQueue;
        functionQueue = nullptr;

        setVisible(false);

        UnregisterClass(WINDOW_CLASS_NAME, windowClass.hInstance);
        if (handle)
            DeleteObject(handle);
    }
}