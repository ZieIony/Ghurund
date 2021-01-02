#include "Application.h"
#include "SystemWindow.h"
#include "WindowType.h"
#include "graphics/SwapChain.h"
#include "ui/RootView.h"

#include <time.h>
#include <shellapi.h>
#include <windowsx.h>

namespace Ghurund {
    LRESULT windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
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

    SystemWindow::SystemWindow(HWND handle, const WindowClass& type, Ghurund::Timer& timer):Window(nullptr), windowClass(type), timer(timer) {
        this->handle = handle;

        WindowData* windowData = ghnew WindowData(this);
        SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)windowData);
    }

    SystemWindow::~SystemWindow() {
        setVisible(false);
        DragDropEnabled = false;

        WindowData* windowData = (WindowData*)GetWindowLongPtr(handle, GWLP_USERDATA);
        delete windowData;
        SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)nullptr);

        if (rootView)
            rootView->release();
        if (handle)
            DestroyWindow(handle);
        delete swapChain;
    }

    void SystemWindow::setRootView(Ghurund::UI::RootView* rootView) {
        setPointer(this->rootView, rootView);

        if (rootView) {
            rootView->PreferredSize = { (float)Size.width, (float)Size.height };
            rootView->invalidate();
        }
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

            if (swapChain)
                swapChain->resize(Size.width, Size.height);
            if (rootView) {
                rootView->PreferredSize = { (float)Size.width, (float)Size.height };
                rootView->invalidate();
            }

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

    bool SystemWindow::onKeyEvent(const KeyEventArgs& args) {
        if (rootView)
            rootView->dispatchKeyEvent(args);
        return true;
    }

    bool SystemWindow::onMouseButtonEvent(const MouseButtonEventArgs& args) {
        if (rootView->dispatchMouseButtonEvent(args) && (IsLButtonDown() || IsMButtonDown() || IsRButtonDown())) {
            SetCapture(handle);
        } else {
            ReleaseCapture();
        }
        return true;
    }

    bool SystemWindow::onMouseMotionEvent(const MouseMotionEventArgs& args) {
        if (rootView)
            rootView->dispatchMouseMotionEvent(args);
        return true;
    }

    bool SystemWindow::onMouseWheelEvent(const MouseWheelEventArgs& args) {
        if (rootView)
            rootView->dispatchMouseWheelEvent(args);
        return true;
    }

    void SystemWindow::onUpdate(const uint64_t time) {
        input.dispatchEvents(time, *this);
        if (rootView) {
            rootView->onUpdate(time);
            rootView->measure((float)Size.width, (float)Size.height);
            rootView->layout(0, 0, (float)Size.width, (float)Size.height);
        }
    }

    void SystemWindow::onPaint() {
        if (rootView)
            rootView->draw();
    }

    OverlappedWindow::OverlappedWindow(Ghurund::Timer& timer)
        : SystemWindow(WindowClass::WINDOWED.create(), WindowClass::WINDOWED, timer) {}

    FullscreenWindow::FullscreenWindow(Ghurund::Timer& timer)
        : SystemWindow(WindowClass::FULLSCREEN.create(), WindowClass::FULLSCREEN, timer) {}

    PopupWindow::PopupWindow(Ghurund::Timer& timer)
        : SystemWindow(WindowClass::POPUP.create(), WindowClass::POPUP, timer) {}
}