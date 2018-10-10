#include "Window.h"

namespace Ghurund {
    const tchar *Window::WINDOW_CLASS_NAME = _T("Ghurund");

    void Window::init(HWND handle) {
        this->handle = handle;

        updateSize();
    }

    void Window::init(Settings &settings, WindowProc &windowProc) {
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_CLASSDC;
        windowClass.lpfnWndProc = &windowProc.messageHandler;
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

        DWORD dwStyle = settings.windowed ? WS_TILEDWINDOW : (WS_POPUP|WS_EX_TOPMOST);
        RECT cr = {0, 0, (LONG)settings.width, (LONG)settings.height};
        AdjustWindowRect(&cr, dwStyle, false);
        handle = CreateWindow(WINDOW_CLASS_NAME, title, dwStyle, 0, 0, cr.right-cr.left, cr.bottom-cr.top, nullptr, nullptr, windowClass.hInstance, &windowProc);

        updateSize();
    }

    void Window::uninit() {
        setVisible(false);

        UnregisterClass(WINDOW_CLASS_NAME, windowClass.hInstance);
        if(handle)
            DeleteObject(handle);
    }

    void Window::updateSize() {
        RECT rect;
        GetWindowRect(handle, &rect);
        width = rect.right-rect.left;
        height = rect.bottom-rect.top;
        viewport = D3D12_VIEWPORT{0.0f, 0.0f, static_cast<float>(width), static_cast<float>(height),0,1};
        scissorRect = D3D12_RECT{0, 0, static_cast<LONG>(width), static_cast<LONG>(height)};
    }

    void Window::setSize(unsigned int width, unsigned int height) {
        SetWindowPos(handle, HWND_TOPMOST, 0, 0, width, height, SWP_NOMOVE|SWP_NOOWNERZORDER|SWP_NOSENDCHANGING|SWP_NOZORDER);
        updateSize();
    }
}