#include "ghcpch.h"
#include "WindowProc.h"

#include "SystemWindow.h"
#include "core/Timer.h"

namespace Ghurund::Core {
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

            RECT rc = { 0,0,(LONG)window.size.Value.Width, (LONG)window.size.Value.Height };
            AdjustWindowRect(&rc, GetWindowLong(window.Handle, GWL_STYLE), false);

            window.position = IntPoint(x + rc.left, y + rc.top);
            return 0;
        } else if (msg == WM_SIZE) {
            unsigned int width = LOWORD(lParam);
            unsigned int height = HIWORD(lParam);
            window.size = IntSize(width, height);
            return 0;
        } else if (msg == WM_NCACTIVATE) {
            if (GetWindowLong(window.Handle, GWL_EXSTYLE) & WS_EX_NOACTIVATE && wParam == FALSE) {
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
}