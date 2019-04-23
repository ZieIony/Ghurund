#include "Window.h"

namespace Ghurund {
    const tchar* Window::WINDOW_CLASS_NAME = _T("Ghurund");
    const Ghurund::Type& Window::TYPE = Ghurund::Type([]() {return ghnew Window(); }, "Window");

    void Window::init(HWND handle) {
        this->handle = handle;

        updateSize();
    }

    void Window::init(Settings& settings, WindowProc& windowProc) {
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_CLASSDC;
        windowClass.lpfnWndProc = &windowProc.messageProc;
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
        handle = CreateWindow(WINDOW_CLASS_NAME, title, dwStyle, 0, 0, cr.right - cr.left, cr.bottom - cr.top, nullptr, nullptr, windowClass.hInstance, &windowProc);

        updateSize();
    }

    void Window::uninit() {
        setVisible(false);

        UnregisterClass(WINDOW_CLASS_NAME, windowClass.hInstance);
        if (handle)
            DeleteObject(handle);
    }

    void Window::updateSize() {
        RECT rect;
        GetWindowRect(handle, &rect);
        size.x = rect.right - rect.left;
        size.y = rect.bottom - rect.top;
        viewport = D3D12_VIEWPORT{0.0f, 0.0f, (float)size.x, (float)size.y,0,1};
        scissorRect = D3D12_RECT{0, 0, size.x, size.y};
    }
}