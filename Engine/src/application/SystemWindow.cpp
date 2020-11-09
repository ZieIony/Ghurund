#include "Application.h"
#include "SystemWindow.h"
#include "WindowType.h"
#include "graphics/SwapChain.h"
#include "ui/RootView.h"

#include <time.h>

namespace Ghurund {
    LRESULT windowProc(HWND handle, UINT msg, WPARAM wParam, LPARAM lParam) {
        WindowData* windowData = (WindowData*)GetWindowLongPtr(handle, GWLP_USERDATA);
        if (!windowData)
            return DefWindowProc(handle, msg, wParam, lParam);

        SystemWindow& window = *windowData->window;
        Application* app = window.Application;

        if (msg == WM_KEYDOWN) {
            window.OnKeyEvent(KeyEventArgs(KeyAction::DOWN, (int)wParam, app->Timer.TimeMs));
            return 0;
        } else if (msg == WM_KEYUP) {
            window.OnKeyEvent(KeyEventArgs(KeyAction::UP, (int)wParam, app->Timer.TimeMs));
            return 0;
        } else if (msg == WM_CHAR) {
            window.OnKeyEvent(KeyEventArgs(KeyAction::CHAR, (int)wParam, app->Timer.TimeMs));
            return 0;
        } else if (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) {
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(window.Handle, &p);
            if (msg == WM_LBUTTONDOWN) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::DOWN, MouseButton::LEFT, app->Timer.TimeMs));
            } else if (msg == WM_LBUTTONUP) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::UP, MouseButton::LEFT, app->Timer.TimeMs));
            } else if (msg == WM_MBUTTONDOWN) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::DOWN, MouseButton::MIDDLE, app->Timer.TimeMs));
            } else if (msg == WM_MBUTTONUP) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::UP, MouseButton::MIDDLE, app->Timer.TimeMs));
            } else if (msg == WM_RBUTTONDOWN) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::DOWN, MouseButton::RIGHT, app->Timer.TimeMs));
            } else if (msg == WM_RBUTTONUP) {
                window.OnMouseButtonEvent(MouseButtonEventArgs(XMINT2(p.x, p.y), MouseAction::UP, MouseButton::RIGHT, app->Timer.TimeMs));
            } else if (msg == WM_MOUSEMOVE) {
                if (windowData->prevMousePos.x == -1 && windowData->prevMousePos.y == -1)
                    windowData->prevMousePos = p;
                window.OnMouseMotionEvent(MouseMotionEventArgs(XMINT2(p.x, p.y), XMINT2(p.x - windowData->prevMousePos.x, p.y - windowData->prevMousePos.y), app->Timer.TimeMs));
                windowData->prevMousePos = p;

                if (!windowData->mouseTracked) {
                    windowData->mouseTracked = true;

                    TRACKMOUSEEVENT mouseEvt;
                    ZeroMemory(&mouseEvt, sizeof(TRACKMOUSEEVENT));
                    mouseEvt.cbSize = sizeof(TRACKMOUSEEVENT);
                    mouseEvt.dwFlags = TME_LEAVE;
                    mouseEvt.hwndTrack = window.Handle;
                    TrackMouseEvent(&mouseEvt);
                }
            } else if (msg == WM_MOUSEWHEEL) {
                window.OnMouseWheelEvent(MouseWheelEventArgs(XMINT2(p.x, p.y), MouseWheel::VERTICAL, GET_WHEEL_DELTA_WPARAM(wParam), app->Timer.TimeMs));
            } else if (msg == WM_MOUSEHWHEEL) {
                window.OnMouseWheelEvent(MouseWheelEventArgs(XMINT2(p.x, p.y), MouseWheel::HORIZONTAL, GET_WHEEL_DELTA_WPARAM(wParam), app->Timer.TimeMs));
            }
            return 0;
        } else if (msg == WM_MOUSELEAVE) {
            windowData->mouseTracked = false;
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(window.Handle, &p);
            if (windowData->prevMousePos.x == -1 && windowData->prevMousePos.y == -1)
                windowData->prevMousePos = p;
            window.OnMouseMotionEvent(MouseMotionEventArgs(XMINT2(p.x, p.y), XMINT2(p.x - windowData->prevMousePos.x, p.y - windowData->prevMousePos.y), app->Timer.TimeMs));
            windowData->prevMousePos = p;
        //} else if (msg == WM_PAINT) {
          //  window.OnPaint();   // TODO: do it in the message loop
            return 0;
        } else if (msg == WM_MOVE) {
            unsigned int x = LOWORD(lParam);
            unsigned int y = HIWORD(lParam);

            RECT rc = { 0,0,window.Size.width, window.Size.height };
            AdjustWindowRect(&rc, window.Class.Style, false);

            if (window.Position.x != x + rc.left && window.Position.y != y + rc.top) {
                window.setPosition(x + rc.left, y + rc.top);
                window.OnPositionChanged();
            }
            return 0;
        } else if (msg == WM_SIZE) {
            unsigned int width = LOWORD(lParam);
            unsigned int height = HIWORD(lParam);
            if (window.Size.width != width || window.Size.height != height) {
                window.setSize(width, height);
                window.OnSizeChanged();
            }
            return 0;
        } else if (msg == WM_NCACTIVATE) {
            if (window.Class == WindowClass::POPUP && wParam == FALSE) {
                PostMessage(window.Handle, WM_CLOSE, 0, 0);
                return 0;
            }
        } else if (msg == WM_SETFOCUS || msg == WM_KILLFOCUS) {
            window.OnFocusedChanged();
        } else if (msg == WM_DESTROY) {
            window.OnDestroy();
            delete windowData;
            return 0;
        }

        return DefWindowProc(handle, msg, wParam, lParam);
    }

    SystemWindow::SystemWindow(HWND handle, const WindowClass& type):Window(nullptr), windowClass(type) {
        this->handle = handle;

        WindowData* wd = ghnew WindowData(this);
        SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)wd);
        OnCreated();
    }

    SystemWindow::~SystemWindow() {
        setVisible(false);

        if (rootView)
            rootView->release();
        if (handle)
            DeleteObject(handle);
    }

    void SystemWindow::setRootView(Ghurund::UI::RootView* rootView) {
        setPointer(this->rootView, rootView);

        if (rootView) {
            OnSizeChanged.remove(onSizeChangedHandler);
            onSizeChangedHandler = EventHandler<Ghurund::Window>([rootView](Ghurund::Window& window) {
                rootView->invalidate();
                return true;
            });
            OnSizeChanged.add(onSizeChangedHandler);

            OnKeyEvent.clear();
            OnKeyEvent.add([rootView](Ghurund::Window& window, const KeyEventArgs& args) {
                rootView->dispatchKeyEvent(args);
                return true;
            });

            OnMouseButtonEvent.clear();
            OnMouseButtonEvent.add([this, rootView](Ghurund::Window& window, const MouseButtonEventArgs& args) {
                if (rootView->dispatchMouseButtonEvent(args)) {
                    SetCapture(handle);
                } else {
                    ReleaseCapture();
                }
                return true;
            });

            OnMouseMotionEvent.clear();
            OnMouseMotionEvent.add([rootView](Ghurund::Window& window, const MouseMotionEventArgs& args) {
                rootView->dispatchMouseMotionEvent(args);
                return true;
            });

            OnMouseWheelEvent.clear();
            OnMouseWheelEvent.add([rootView](Ghurund::Window& window, const MouseWheelEventArgs& args) {
                rootView->dispatchMouseWheelEvent(args);
                return true;
            });

            OnUpdate.clear();
            OnUpdate.add([rootView](const Ghurund::Window& window, const Timer& timer) {
                rootView->update(timer);
                return true;
            });

            OnPaint.clear();
            OnPaint.add([rootView](const Ghurund::Window& window) {
                rootView->draw();
                return true;
            });
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

            SetWindowPos(handle, 0, 0, 0, w + xExtra, h + yExtra, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING | SWP_NOZORDER | SWP_NOACTIVATE);
        }
    }

    OverlappedWindow::OverlappedWindow()
        :SystemWindow(WindowClass::WINDOWED.create(), WindowClass::WINDOWED) {}

    FullscreenWindow::FullscreenWindow()
        : SystemWindow(WindowClass::FULLSCREEN.create(), WindowClass::FULLSCREEN) {}

    PopupWindow::PopupWindow()
        : SystemWindow(WindowClass::POPUP.create(), WindowClass::POPUP) {}
}